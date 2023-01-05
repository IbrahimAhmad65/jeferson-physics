//
// Created by ibrahim on 12/26/22.
//

#ifndef PHYS2_TRIANGLE_H
#define PHYS2_TRIANGLE_H


#include <array>
#include "Vector3D.h"

class Triangle {
public:

    Triangle(Vector3D p1, Vector3D p2, Vector3D p3);

    // Only here to do arr initialization dot ever use himo in future
    Triangle();

    bool intersects(const Triangle &p);

    void translate(const Vector3D &v);

    // Rotates about origin not geometric COM
    void rotateRodrigues(const Vector3D &axis, double theta);

    [[nodiscard]] Vector3D *getPointList() const;

    void rotateEulerJ(double theta);

    void rotateEulerK(double theta);

    void rotateEulerI(double theta);

    [[nodiscard]] Triangle clone() const;

    [[nodiscard]] std::string toString() const;

private:
    int order = 3;
    Vector3D center;

    Vector3D p1;
    Vector3D p2;
    Vector3D p3;

};


struct Point {
    Vector3D pos;
};

struct line {
    Point p1, p2;
};


#endif //PHYS2_TRIANGLE_H
