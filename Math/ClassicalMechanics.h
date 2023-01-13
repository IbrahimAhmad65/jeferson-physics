//
// Created by ibrahim on 1/5/23.
//

#ifndef PHYS2_CLASSICALMECHANICS_H
#define PHYS2_CLASSICALMECHANICS_H


#include "Mesh.h"
struct IDVectorCouple{
    std::vector<Vector3D> intersectionPoint;
    int interSectionPointSize;
    int id;
};
class ClassicalMechanics {
public:
    ClassicalMechanics(Mesh* meshes, int numMeshes);
    void stepForward(double timeStep);
private:
    void resetPostTickMeshes();
    long currentTime = 0e0;
    [[nodiscard]] std::vector<IDVectorCouple> meshesThatHaveCollided() const;
    Mesh* meshes;
    Mesh* meshesPostTick;
//    std::vector<Vector3D> forces;
    std::vector<Vector3D> torques;
    int numMeshes;
    long lastTimeStep = -1;
    long localTimeStep = -1;
    void stepForward(long timeStep);

    void tickLocalPost(long timeStep);
};


#endif //PHYS2_CLASSICALMECHANICS_H
