//
// Created by ibrahim on 12/24/22.
//

#include "RigidBody.h"
#include "Math/Vector2D.h"

Vector3D RigidBody::getPos() {
    return {1,1,1};
}

Vector3D RigidBody::getAngle() {
    return Vector3D();
}

Vector3D RigidBody::getVelocity() {
    return Vector3D();
}

Vector3D RigidBody::applyForce(Vector3D force, double t, Vector3D distanceFromCM) {
    return Vector3D();
}

