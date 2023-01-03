
#include <cmath>
#include "Vector3D.h"
#include <sys/time.h>
#include <xmmintrin.h>
#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include <string.h>

Vector3D::Vector3D(double i, double j, double k) {
    this->i = i;
    this->j = j;
    this->k = k;
}

Vector3D::Vector3D(const Vector3D &v) {
    i = v.getI();
    j = v.getJ();
    k = v.getK();
}

Vector3D::Vector3D() {
    this->i = 0;
    this->j = 0;
    this->k = 0;
}

double Vector3D::dot(Vector3D v) const {
    return i * v.getI() + j * v.getJ() + k * v.getK();
}

Vector3D Vector3D::cross(const Vector3D v) const {
    double in = getJ() * v.getK() - getK() * v.getJ();
    double jn = getK() * v.getI() - getI() * v.getK();
    double kn = getI() * v.getJ() - getJ() * v.getI();

    return {in, jn, kn};
}

double Vector3D::getI() const {
    return i;
}

double Vector3D::getJ() const {
    return j;
}

double Vector3D::getK() const {
    return k;
}


Vector3D Vector3D::scale(double scalar) {
    this->i *= scalar;
    this->j *= scalar;
    this->k *= scalar;
    updateLocal();
    return clone();
}

Vector3D Vector3D::rotateAboutIEuler(double theta) {
    j = j * std::cos(theta) - k * std::sin(theta);
    k = j * std::sin(theta) + k * std::cos(theta);
    updateLocal();
    return clone();

}


Vector3D Vector3D::rotateAboutJEuler(double theta) {
    i = i * std::cos(theta) + k * std::sin(theta);
    k = -i * std::sin(theta) + k * std::cos(theta);
    updateLocal();
    return clone();

}

Vector3D Vector3D::rotateAboutKEuler(double theta) {
    i = i * std::cos(theta) - j * std::sin(theta);
    j = i * std::sin(theta) + j * std::cos(theta);
    updateLocal();
    return clone();

}

Vector3D Vector3D::rotateAboutAxisRodrigues(Vector3D axis, double theta) {
    Vector3D copyV = clone();
    Vector3D normalizedAxis = axis.clone();
    normalizedAxis.scale(axis.getInverseRootMagActual());
    Vector3D p1 = copyV.clone();
    p1.scale(cos(theta));
    Vector3D p2 = normalizedAxis.cross(*this);
    p2.scale(sin(theta));
    normalizedAxis.scale(normalizedAxis.dot(*this) * (1 - cos(theta)));
    p1.add(p2);
    p1.add(normalizedAxis);
    copy(p1);
    updateLocal();
    return clone();

}

Vector3D Vector3D::clone() const {
    return {i, j, k};
}

void Vector3D::copy(Vector3D v) {
    i = v.getI();
    j = v.getJ();
    k = v.getK();
    v.forceUpdateLocal();
    mag = v.mag;
    magInverse = v.magInverse;
    magSquare = v.magSquare;
}

Vector3D Vector3D::add(const Vector3D &rightSide) {
    this->i += rightSide.getI();
    this->j += rightSide.getJ();
    this->k += rightSide.getK();
    return clone();
}

double Vector3D::getMagnitudeActual() const {
    return sqrt(i * i + j * j + k * k);
}

double Vector3D::getMagnitude() {
    if (!updateMagsOnChange) {
        mag = getMagnitudeActual();
    }
    return mag;
}

double Vector3D::getMagnitudeSquared() {
    if (!updateMagsOnChange) {
        magSquare = getMagSquaredActual();
    }
    return magSquare;
}

double Vector3D::getMagnitudeInverse() {
    if (!updateMagsOnChange) {
        magInverse = getInverseRootMagActual();
    }
    return magInverse;
}

double Vector3D::getMagSquaredActual() const {
    return (i * i + j * j + k * k);
}

double Vector3D::getInverseRootMagActual() const {
    return 1.0 / getMagnitudeActual();
//    double number = getMagSquaredActual();
//    long i;
//    float x2, y;
//    const float threehalfs = 1.5F;
//
//    x2 = number * 0.5F;
//    y = number;
//    i = *(long *) &y;
//    i = 0x5f3759df - (i >> 1);
//    y = *(float *) &i;
//    y = y * (threehalfs - (x2 * y * y));
//
//    return y;



}

void Vector3D::updateLocal() {
    if (updateMagsOnChange) {
        mag = getMagnitudeActual();
        magInverse = getInverseRootMagActual();
        magSquare = getMagSquaredActual();
    }
}

void Vector3D::forceUpdateLocal() {
    mag = getMagnitudeActual();
    magInverse = getInverseRootMagActual();
    magSquare = getMagSquaredActual();
}

Vector3D Vector3D::operator+(Vector3D v) const {
    double a = i + v.i;
    double b = j + v.j;
    double c = k + v.k;
    return {a, b, c};
}

Vector3D Vector3D::operator-(Vector3D v) const {
    double a = i - v.i;
    double b = j - v.j;
    double c = k - v.k;
    return {a, b, c};
}

double Vector3D::getAngleBetween(Vector3D v) {
//    std::cout<< v.getMagnitudeInverse() << " jeremiah says hi "<<std::endl;
    return acos(dot(v) * v.getMagnitudeInverse() * getMagnitudeInverse());
}

double Vector3D::operator*(Vector3D v) const {
    return dot(v);
}

Vector3D Vector3D::operator*(double v) const {
    return {i * v, j * v, k * v};
}

void Vector3D::operator+=(Vector3D v) {
    add(v);
}

void Vector3D::operator-=(Vector3D v) {
    add(v.clone().scale(-1));
}

void Vector3D::operator*=(double v) {
    scale(v);
}

void Vector3D::operator/=(double v) {
    scale(1.0 / v);

}

Vector3D Vector3D::operator/(double v) const {
    double div = 1.0 / v;
    return {i * div, j * div, k * div};
}

std::string Vector3D::toString() const {
    return "(" + std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(k) + ")";
}

bool Vector3D::operator==(Vector3D v) {
    return i == v.i && j == v.j && k == v.k;
}


double performanceExec() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    struct timeval start, end;

    gettimeofday(&start, NULL);

    Vector3D v = Vector3D(2, 3, 2);
    v.updateMagsOnChange = true;
    v.scale(5);
    v.getMagnitude();
    v.scale(12);
    v.scale(5);
    v.getMagnitudeInverse();
    v.scale(1 / 5.0);
    v.scale(1 / 12.0);
    v.scale(1 / 5.0);
    v.rotateAboutAxisRodrigues(Vector3D(2, 3, 0), 3.14);
    std::cout << v.getI() << " " << v.getJ() << " " << v.getK() << std::endl;

    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6; // in seconds

    printf("time program took %f seconds to execute: ", time_taken);
    return time_taken;
}
