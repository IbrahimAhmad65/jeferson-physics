//
// Created by ibrahim on 12/26/22.
//

#ifndef PHYS2_POLYGON_H
#define PHYS2_POLYGON_H


#include <array>
#include "Vector3D.h"

class Polygon {
public:
    Polygon(Vector3D* vector3D, int order);
    Polygon(int order);
    bool intersects(Polygon p);
    void translate(Vector3D v);
    int getOrder() const;
    void rotateRodrigues(Vector3D axis, double theta);
    Vector3D* getPointList();
    void rotateEulerJ(double theta);

    void rotateEulerK(double theta);

    void rotateEulerI(double theta);
private:
    int order;

    Vector3D* pointPointer;
};


#endif //PHYS2_POLYGON_H
