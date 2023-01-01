//
// Created by ibrahim on 12/24/22.
//

#ifndef PHYS2_RIGIDBODY_H
#define PHYS2_RIGIDBODY_H


#include "Math/Vector2D.h"
#include "Math/Vector3D.h"

class RigidBody {
public:
    Vector3D getPos();
    Vector3D getAngle();
    Vector3D getVelocity();
    Vector3D applyForce(Vector3D force, double t, Vector3D distanceFromCM);
private:
    Vector3D pos;
    Vector3D angle;
    Vector3D vel;
    double m;
    double I;
};


#endif //PHYS2_RIGIDBODY_H
