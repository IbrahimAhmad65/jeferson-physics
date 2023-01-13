//
// Created by ibrahim on 1/5/23.
//

#include <vector>
#include "ClassicalMechanics.h"

#define depthForCollisionSearch 8

ClassicalMechanics::ClassicalMechanics(Mesh *meshes, int numMeshes) {
    this->meshes = new Mesh[numMeshes];
    this->meshesPostTick = new Mesh[numMeshes];
    for (int i = 0; i < numMeshes; ++i) {
        meshes[i].setID(i);
        this->meshes[i] = meshes[i];
        this->meshesPostTick[i] = meshes[i];
    }
    this->numMeshes = numMeshes;
//    forces = std::vector<Vector3D>();
    torques = std::vector<Vector3D>();
}

std::vector<IDVectorCouple> ClassicalMechanics::meshesThatHaveCollided() const {
    std::vector<IDVectorCouple> ids = std::vector<IDVectorCouple>();
    for (int i = 0; i < numMeshes - 1; ++i) {
        for (int j = 0; j < numMeshes - 1 - i; ++j) {
            std::vector<Vector3D> collisionPoints = meshesPostTick[i].collidedWith(meshesPostTick[j]);
            if (!collisionPoints.empty()) {
                ids.push_back({collisionPoints, static_cast<int>(collisionPoints.size()), i});
                ids.push_back({collisionPoints, static_cast<int>(collisionPoints.size()), j});
            }
        }
    }
    return ids;

}

void ClassicalMechanics::stepForward(long timeStep) {
    // do physics now, do kinematics
    tickLocalPost(timeStep);
    lastTimeStep = localTimeStep;
    localTimeStep = timeStep;
    std::vector<IDVectorCouple> collisionIds = meshesThatHaveCollided();
    if (!collisionIds.empty()) {
        // do binary timeCheck here
        // do conservation laws
        int loopMax = depthForCollisionSearch - 1;
        long timeStepForFinalCollision = -1;
        std::vector<IDVectorCouple> oldCollisionPos;

        for (int i = loopMax; i >= 1; --i) {
            resetPostTickMeshes();
            tickLocalPost(localTimeStep);
            collisionIds = meshesThatHaveCollided();
            localTimeStep = timeStep * (i / depthForCollisionSearch);
            if (collisionIds.empty()) {
                timeStepForFinalCollision = timeStep * ((i - 1) / depthForCollisionSearch);
                break;
            }
            oldCollisionPos.clear();
            for (int j = 0; j < collisionIds.size(); ++j) {
                oldCollisionPos.push_back(collisionIds[i]);
            }
        }
        resetPostTickMeshes();
        tickLocalPost(timeStepForFinalCollision);
        // apply conservation laws in this for loop
        for (int i = 0; i < oldCollisionPos.size(); i += 2) {
            Mesh mesh1 = meshesPostTick[i];
            Mesh mesh2 = meshesPostTick[i + 1];
            std::vector<Vector3D> pointsOfCollision = oldCollisionPos[i].intersectionPoint;
            Vector3D avgInterSectionPoint = Vector3D();
            for (int j = 0; j < pointsOfCollision.size(); ++j) {
                avgInterSectionPoint += pointsOfCollision[i];
            }
            avgInterSectionPoint /= (double) pointsOfCollision.size();
            // Found avg point of intersection, now lets do conservation of linear and angular momentum / energy
            // flatten to 2D
            double m1 = mesh1.getMass();
            double m2 = mesh2.getMass();
            Vector3D v1 = mesh1.getVelocity();
            Vector3D v2 = mesh2.getVelocity();
            Vector3D x1 = mesh1.getCOM().clone();
            Vector3D x2 = mesh2.getCOM().clone();
            Vector3D v2Prime = v2 - (x2-x1)*(2*m1)/(m1+m2) * ((v2-v1)*(x2-x1)) / (x2-x1).getMagnitudeSquared();
            Vector3D v1Prime = v1 - (x1-x2)*(2*m2)/(m2+m1) * ((v1-v2)*(x1-x2)) / (x1-x2).getMagnitudeSquared();
            mesh1.setVelocity(v1Prime);
            mesh2.setVelocity(v2Prime);


        }


    }
    currentTime += localTimeStep;
    // update too old to new
    for (int i = 0; i < numMeshes; ++i) {
        meshes[i] = meshesPostTick[i].clone();
    }
//    forces.clear();
    torques.clear();
}

void ClassicalMechanics::tickLocalPost(long timeStep) {
    for (int i = 0; i < numMeshes; ++i) {
        // IDK if forces are actually useful lol, maybe friction?
//        meshesPostTick[i].applyForce(forces[i], timeStep, pointOfContact[i]);
        meshesPostTick[i].applyTorque(torques[i], timeStep);
        // check if more accurate to do before or after
        meshesPostTick[i].updatePhysics(timeStep);
    }
}

void ClassicalMechanics::resetPostTickMeshes() {
    for (int i = 0; i < numMeshes; ++i) {
        meshesPostTick[i] = meshes[i].clone();
    }
}
