//
// Created by ibrahim on 12/24/22.
//

#include "Vector2D.h"
#include <cmath>
Vector2D::Vector2D(double x, double y)  {
    this->x = x;
    this->y = y;
}
Vector2D::Vector2D()  {
    this->x = 0;
    this->y = 0;
}
double Vector2D::getX() {
    return this->x;
}

double Vector2D::getY() {
    return this->y;
}

void Vector2D::setX(double x) {
    this->x = x;
}

void Vector2D::setY(double y) {
    this->y = y;
}

void Vector2D::setXY(double x, double y) {
    setX(x);
    setY(y);
}

void Vector2D::setTheta(double theta) {
    double mag = std::sqrt(x*x + y*y);
    x = mag * std::cos(theta);
    y = mag * std::sin(theta);

}

void Vector2D::setMagnitude(double mag) {
    double currentMag = std::sqrt(x*x + y*y);
    double scale = mag / currentMag;
    this-> x = x*scale;
    this-> y = y*scale;
}

void Vector2D::setPolar(double theta, double mag) {
    x = mag * std::cos(theta);
    y = mag * std::sin(theta);
}

Vector2D Vector2D::scale(double scalar) {
    this->x = x*scalar;
    this->y = y*scalar;
    return clone();
}

Vector2D Vector2D::clone() const  {
    return {this->x,this->y};
}


