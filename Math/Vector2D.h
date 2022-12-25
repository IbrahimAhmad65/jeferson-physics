//
// Created by ibrahim on 12/24/22.
//

#ifndef PHYS2_VECTOR2D_H
#define PHYS2_VECTOR2D_H


class Vector2D {
public:
    Vector2D(double x, double y);
    Vector2D();
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    void setXY(double x,double y);
    void setTheta(double theta);
    void setMagnitude(double mag);
    void setPolar(double theta, double mag);
    Vector2D scale(double scalar);
    [[nodiscard]] Vector2D clone() const ;
protected:
    double x;
    double y;
};


#endif //PHYS2_VECTOR2D_H
