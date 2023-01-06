//
// Created by ibrahim on 1/5/23.
//

#include <vector>
#include "ClassicalMechanics.h"

ClassicalMechanics::ClassicalMechanics(Mesh *meshes, int numMeshes) {
    this->meshes = new Mesh[numMeshes];
    this->meshesPostTick = new Mesh[numMeshes];
    for (int i = 0; i < numMeshes; ++i) {
        meshes[i].setID(i);
        this-> meshes[i] = meshes[i];
        this-> meshesPostTick[i] = meshes[i];
    }
    this-> numMeshes = numMeshes;
    forces = std::vector<Vector3D>();
    pointOfContact = std::vector<Vector3D>();
    torques = std::vector<Vector3D>();
}

std::vector<int> ClassicalMechanics::meshesThatHaveCollided() const{
    std::vector<int> ids = std::vector<int>();
    for (int i = 0; i < numMeshes-1; ++i) {
        for (int j = 0; j < numMeshes - 1 - i; ++j) {
            if(meshesPostTick[i].collidedWith(meshesPostTick[j])){
                ids.push_back(i);
                ids.push_back(j);
            }
        }
    }
    return ids;

}

void ClassicalMechanics::stepForward(double timeStep) {
    // do physics now, do kinematics
    for (int i = 0; i < numMeshes; ++i) {
        meshesPostTick[i].applyForce(forces[i],timeStep,pointOfContact[i]);
        meshesPostTick[i].applyForce(forces[i],timeStep,pointOfContact[i]);
    }
    std::vector<int> collisionIds = meshesThatHaveCollided();
    if(!collisionIds.empty()){
        // do binary timeCheck here
        // do conservation laws
    }
    // update to old to new
    for (int i = 0; i < numMeshes; ++i) {
        meshes[i] = meshesPostTick[i];
    }
    forces.clear();
}

void ClassicalMechanics::tickLocalPost(double newTime) {

}
