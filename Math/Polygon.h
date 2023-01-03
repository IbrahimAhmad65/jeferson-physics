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
    bool intersects(const Polygon& p);
    void translate(const Vector3D& v);
    [[nodiscard]] int getOrder() const;
    void rotateRodrigues(const Vector3D& axis, double theta);
    Vector3D* getPointList();
    void rotateEulerJ(double theta);

    void rotateEulerK(double theta);

    void rotateEulerI(double theta);

    [[nodiscard]] Polygon clone() const;
private:
    int order;
    Vector3D center;

    Vector3D* pointPointer;
};


struct Point {
    Vector3D pos;
};

struct line {
    Point p1, p2;
};


#endif //PHYS2_POLYGON_H
