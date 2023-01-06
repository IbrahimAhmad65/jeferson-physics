//
// Created by ibrahim on 1/5/23.
//

#ifndef PHYS2_CLASSICALMECHANICS_H
#define PHYS2_CLASSICALMECHANICS_H


#include "Mesh.h"

class ClassicalMechanics {
public:
    ClassicalMechanics(Mesh* meshes, int numMeshes);
    void stepForward(double timeStep);
private:
    void tickLocalPost(double newTime);
    long currentTime = 0e0;
    [[nodiscard]] std::vector<int> meshesThatHaveCollided() const;
    Mesh* meshes;
    Mesh* meshesPostTick;
    std::vector<Vector3D> forces;
    std::vector<Vector3D> torques;
    std::vector<Vector3D> pointOfContact;
    int numMeshes;

};


#endif //PHYS2_CLASSICALMECHANICS_H
