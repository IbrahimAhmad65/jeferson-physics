//
// Created by ibrahim on 12/26/22.
//

#include <iostream>
#include "Mesh.h"

// better one lol
Mesh::Mesh(Triangle *p, double density, int numOfFaces, int id) {
    double totalVolume = 0, currentVolume;
    double xCenter = 0, yCenter = 0, zCenter = 0, maxX, maxY, maxZ, minX, minY, minZ;
    boundingBox = new Vector3D[8];
    Vector3D max = Vector3D(-2e307, -2e307, -2e307);
    Vector3D min = Vector3D(2e307, 2e307, 2e307);
    this->faces = new Triangle[numOfFaces];
    for (int i = 0; i < numOfFaces; ++i) {
        this->faces[i] = p[i].clone();
    }
    velocityOfLastTick =  Vector3D();

    for (int i = 0; i < numOfFaces; i++) {
        // can be optimized with point duplicate deletion about 3x faster
        maxX = std::max(max.getI(), faces[i].getPointList()[0].getI());
        maxX = std::max(maxX, faces[i].getPointList()[1].getI());
        maxX = std::max(maxX, faces[i].getPointList()[2].getI());

        maxY = std::max(max.getJ(), faces[i].getPointList()[0].getJ());
        maxY = std::max(maxY, faces[i].getPointList()[1].getJ());
        maxY = std::max(maxY, faces[i].getPointList()[2].getJ());

        maxZ = std::max(max.getK(), faces[i].getPointList()[0].getK());
        maxZ = std::max(maxZ, faces[i].getPointList()[1].getK());
        maxZ = std::max(maxZ, faces[i].getPointList()[2].getK());

        minX = std::min(min.getI(), faces[i].getPointList()[0].getI());
        minX = std::min(minX, faces[i].getPointList()[1].getI());
        minX = std::min(minX, faces[i].getPointList()[2].getI());

        minY = std::min(min.getJ(), faces[i].getPointList()[0].getJ());
        minY = std::min(minY, faces[i].getPointList()[1].getJ());
        minY = std::min(minY, faces[i].getPointList()[2].getJ());

        minZ = std::min(min.getK(), faces[i].getPointList()[0].getK());
        minZ = std::min(minZ, faces[i].getPointList()[1].getK());
        minZ = std::min(minZ, faces[i].getPointList()[2].getK());
        max.setIJK(maxX, maxY, maxZ);
        min.setIJK(minX, minY, minZ);
        totalVolume += currentVolume =
                (faces[i].getPointList()[0].getI() * faces[i].getPointList()[1].getJ() *
                 faces[i].getPointList()[2].getK() -
                 faces[i].getPointList()[0].getI() * faces[i].getPointList()[2].getJ() *
                 faces[i].getPointList()[1].getK() -
                 faces[i].getPointList()[1].getI() * faces[i].getPointList()[0].getJ() *
                 faces[i].getPointList()[2].getK() +
                 faces[i].getPointList()[1].getI() * faces[i].getPointList()[2].getJ() *
                 faces[i].getPointList()[0].getK() +
                 faces[i].getPointList()[2].getI() * faces[i].getPointList()[0].getJ() *
                 faces[i].getPointList()[1].getK() -
                 faces[i].getPointList()[2].getI() * faces[i].getPointList()[1].getJ() *
                 faces[i].getPointList()[0].getK()) / 6;
        xCenter +=
                ((p[i].getPointList()[0].getI() + p[i].getPointList()[1].getI() + p[i].getPointList()[2].getI()) / 4) *
                currentVolume;
        yCenter +=
                ((p[i].getPointList()[0].getJ() + p[i].getPointList()[1].getJ() + p[i].getPointList()[2].getJ()) / 4) *
                currentVolume;
        zCenter +=
                ((p[i].getPointList()[0].getK() + p[i].getPointList()[1].getK() + p[i].getPointList()[2].getK()) / 4) *
                currentVolume;
    }

    boundingBox[0] = min;
    boundingBox[1] = {maxX, minY, minZ};
    boundingBox[2] = {maxX, maxY, minZ};
    boundingBox[3] = {minX, maxY, minZ};
    boundingBox[4] = {minX, minY, maxZ};
    boundingBox[5] = {maxX, minY, maxZ};
    boundingBox[6] = max;
    boundingBox[7] = {minX, maxY, maxZ};

    this->volume = totalVolume;
    this->velocity = Vector3D();
    this->angularVelocityRodrigues = Vector3D();
    this->numOfFaces = numOfFaces;
    this->density = density;
    this->mass = totalVolume * density;
    this->momentOfInertia = 1;
    this->axisOfMOI = Vector3D();
    this->com = {xCenter / volume, yCenter / volume, zCenter / volume};
    rOfBounds = (max - min).getMagnitude() * .5;
    geomCenter = (max + min) * .5;
}

Mesh::Mesh(double mass, Triangle *p, int numOfFaces, int id) {
    double totalVolume = 0, currentVolume;
    double xCenter = 0, yCenter = 0, zCenter = 0, maxX, maxY, maxZ, minX, minY, minZ;
    boundingBox = new Vector3D[8];
    Vector3D max = Vector3D(-2e307, -2e307, -2e307);
    Vector3D min = Vector3D(2e307, 2e307, 2e307);
    this->faces = new Triangle[numOfFaces];
    for (int i = 0; i < numOfFaces; ++i) {
        this->faces[i] = p[i].clone();
    }
    for (int i = 0; i < numOfFaces; i++) {
        // can be optimized with point duplicate deletion about 3x faster
        maxX = std::max(max.getI(), p[i].getPointList()[0].getI());
        maxX = std::max(maxX, p[i].getPointList()[1].getI());
        maxX = std::max(maxX, p[i].getPointList()[2].getI());

        maxY = std::max(max.getJ(), p[i].getPointList()[0].getJ());
        maxY = std::max(maxY, p[i].getPointList()[1].getJ());
        maxY = std::max(maxY, p[i].getPointList()[2].getJ());

        maxZ = std::max(max.getK(), p[i].getPointList()[0].getK());
        maxZ = std::max(maxZ, p[i].getPointList()[1].getK());
        maxZ = std::max(maxZ, p[i].getPointList()[2].getK());

        minX = std::min(min.getI(), p[i].getPointList()[0].getI());
        minX = std::min(minX, p[i].getPointList()[1].getI());
        minX = std::min(minX, p[i].getPointList()[2].getI());

        minY = std::min(min.getJ(), p[i].getPointList()[0].getJ());
        minY = std::min(minY, p[i].getPointList()[1].getJ());
        minY = std::min(minY, p[i].getPointList()[2].getJ());

        minZ = std::min(min.getK(), p[i].getPointList()[0].getK());
        minZ = std::min(minZ, p[i].getPointList()[1].getK());
        minZ = std::min(minZ, p[i].getPointList()[2].getK());
        max.setIJK(maxX, maxY, maxZ);
        min.setIJK(minX, minY, minZ);
        totalVolume += currentVolume =
                (p[i].getPointList()[0].getI() * p[i].getPointList()[1].getJ() * p[i].getPointList()[2].getK() -
                 p[i].getPointList()[0].getI() * p[i].getPointList()[2].getJ() * p[i].getPointList()[1].getK() -
                 p[i].getPointList()[1].getI() * p[i].getPointList()[0].getJ() * p[i].getPointList()[2].getK() +
                 p[i].getPointList()[1].getI() * p[i].getPointList()[2].getJ() * p[i].getPointList()[0].getK() +
                 p[i].getPointList()[2].getI() * p[i].getPointList()[0].getJ() * p[i].getPointList()[1].getK() -
                 p[i].getPointList()[2].getI() * p[i].getPointList()[1].getJ() * p[i].getPointList()[0].getK()) / 6;
        xCenter +=
                ((p[i].getPointList()[0].getI() + p[i].getPointList()[1].getI() + p[i].getPointList()[2].getI()) / 4) *
                currentVolume;
        yCenter +=
                ((p[i].getPointList()[0].getJ() + p[i].getPointList()[1].getJ() + p[i].getPointList()[2].getJ()) / 4) *
                currentVolume;
        zCenter +=
                ((p[i].getPointList()[0].getK() + p[i].getPointList()[1].getK() + p[i].getPointList()[2].getK()) / 4) *
                currentVolume;
    }

    boundingBox[0] = min;
    boundingBox[1] = {maxX, minY, minZ};
    boundingBox[2] = {maxX, maxY, minZ};
    boundingBox[3] = {minX, maxY, minZ};
    boundingBox[4] = {minX, minY, maxZ};
    boundingBox[5] = {maxX, minY, maxZ};
    boundingBox[6] = max;
    boundingBox[7] = {minX, maxY, maxZ};

    this->volume = totalVolume;
    this->velocity = Vector3D();
    this->angularVelocityRodrigues = Vector3D();
    this->numOfFaces = numOfFaces;
    this->density = totalVolume / mass;
    this->mass = mass;
    this->momentOfInertia = 1;
    this->axisOfMOI = Vector3D();
    this->com = {xCenter / volume, yCenter / volume, zCenter / volume};
    rOfBounds = (max - min).getMagnitude() * .5;
    geomCenter = (max + min) * .5;
}

std::vector<Vector3D> Mesh::collidedWith(const Mesh &m) const {
    std::vector<Vector3D> out = std::vector<Vector3D>();

    if ((geomCenter - m.geomCenter).getMagnitude() < rOfBounds + m.rOfBounds) {

        for (int i = 0; i < numOfFaces; ++i) {
            for (int j = 0; j < m.getNumOfFaces(); ++j) {
                Vector3D mj = m.faces[j].intersects(faces[i]);
                Vector3D jm  = faces[i].intersects(m.faces[j]);
                if(mj.isValid()){
                    out.push_back(mj);
                } else if(jm.isValid()){
                    out.push_back(jm);
                }
            }
        }
    }

    return out;
}

void Mesh::translate(const Vector3D &v) {
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(v);
    }
    com += v;
    geomCenter += v;
}

int Mesh::getNumOfFaces() const {
    return numOfFaces;
}

double Mesh::getMass() const {
    return mass;
}

double Mesh::getDensity() const {
    return density;
}

void Mesh::rotateRodriguesAboutCOM(const Vector3D &axis, double theta) const {
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(com * -1);
        faces[i].rotateRodrigues(axis, theta);
        faces[i].translate(com);
    }
    for (int i = 0; i < 8; ++i) {
        boundingBox[i] -= (com);
        boundingBox[i].rotateAboutAxisRodrigues(axis, theta);
        boundingBox[i] += (com);
    }
}

void Mesh::rotateEulerIAboutCom(double theta) const {
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(com * -1);
        faces[i].rotateEulerI(theta);
        faces[i].translate(com);
    }
}

void Mesh::rotateEulerJAboutCom(double theta) const {
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(com * -1);
        faces[i].rotateEulerJ(theta);
        faces[i].translate(com);
    }
}

void Mesh::rotateEulerKAboutCom(double theta) const {
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(com * -1);
        faces[i].rotateEulerK(theta);
        faces[i].translate(com);
    }
}

Mesh Mesh::clone() const {
    auto *newPointer = new Triangle[numOfFaces];
    for (int i = 0; i < numOfFaces; ++i) {
        newPointer[i] = faces[i].clone();
    }
    return {mass, newPointer, numOfFaces, id};
}

void Mesh::applyForce(const Vector3D f, long time, const Vector3D &globalPos) {
    Vector3D torque = (globalPos - com).cross(f);
    angularVelocityRodrigues += (torque / momentOfInertia * time);
    velocity += f * time;
}

Vector3D Mesh::getCOM() const {
    return com;
}

double Mesh::getVolume() const {
    return volume;
}

void Mesh::setMomentOfInertia(double moment) {
    momentOfInertia = moment;
}

void Mesh::rotateRodriguesAboutGEOMCenter(const Vector3D &axis, double theta) const {
    Vector3D zeroMinusSix = boundingBox[0] - boundingBox[6];
    Vector3D sixMinusZero = boundingBox[6] - boundingBox[0];
    for (int i = 0; i < numOfFaces; ++i) {
        faces[i].translate(zeroMinusSix);
        faces[i].rotateRodrigues(axis, theta);
        faces[i].translate(sixMinusZero);
    }
    for (int i = 0; i < 8; ++i) {
        boundingBox[i] += (zeroMinusSix);
        boundingBox[i].rotateAboutAxisRodrigues(axis, theta);
        boundingBox[i] += (sixMinusZero);
    }
}

Vector3D Mesh::getGeomCenter() {
    return geomCenter;
}

void Mesh::setID(const int id) {
    this->id = id;
}

void Mesh::applyTorque(const Vector3D &torque, long time) {
    angularVelocityRodrigues += (torque / momentOfInertia * time);
}

Vector3D Mesh::getVelocity() {
    return velocity;
}

Vector3D Mesh::getAngularVelocityRodrigues() {
    return angularVelocityRodrigues;
}

void Mesh::setAngularVelocityRodrigues(const Vector3D &v) {
    angularVelocityRodrigues = v.clone();
}

void Mesh::setVelocity(const Vector3D &v) {
    velocity = v.clone();
}

void Mesh::updatePhysics(long time) {
    velocityOfLastTick = velocity.clone();
    translate(velocity * time);
    rotateRodriguesAboutCOM(angularVelocityRodrigues, angularVelocityRodrigues.getMagnitude());
}

Vector3D Mesh::getVelocityOfLastTick() {
    return velocityOfLastTick;
}

Mesh::Mesh() = default;
