//
// Created by ibrahim on 12/26/22.
//

#ifndef PHYS2_TRIANGLE_H
#define PHYS2_TRIANGLE_H


#include <array>
#include "Vector3D.h"

class Triangle {
public:
    explicit Triangle(Vector3D* vector3D);
    Triangle();
    Triangle(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3);

    Vector3D intersects(const Triangle& p);
    void translate(const Vector3D& v);
    [[nodiscard]] int getOrder() const;
    void rotateRodrigues(const Vector3D& axis, double theta);
    Vector3D* getPointList();
    void rotateEulerJ(double theta);

    void rotateEulerK(double theta);

    [[nodiscard]] std::string toString() const;

    void rotateEulerI(double theta);
    [[nodiscard]] Triangle clone() const;
private:
    int order = 3;

    Vector3D center;

    Vector3D* pointPointer{};
};


struct Point {
    Vector3D pos;
};

struct line {
    Point p1, p2;
};


#endif //PHYS2_TRIANGLE_H
