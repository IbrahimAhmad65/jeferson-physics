//
// Created by ibrahim on 12/24/22.
//

#ifndef PHYS2_VECTOR3D_H
#define PHYS2_VECTOR3D_H


#include <ostream>

class Vector3D {
public:
    Vector3D operator+(Vector3D v) const;

    Vector3D operator-(Vector3D v) const;

    double operator*(Vector3D v) const;

    Vector3D operator*(double v) const;

    Vector3D operator/(double v) const;

    void operator+=(Vector3D v);

    void operator-=(Vector3D v);

    void operator*=(double v);
    bool operator==(Vector3D v);


    void operator/=(double v);

    [[nodiscard]] std::string toString() const;
    bool updateMagsOnChange = false;

    Vector3D(double i, double j, double k);

    Vector3D(Vector3D const &v);

    Vector3D();

    [[nodiscard]] double dot(Vector3D) const;

    [[nodiscard]] Vector3D cross(Vector3D) const;

    [[nodiscard]] double getI() const;

    [[nodiscard]] double getJ() const;

    [[nodiscard]] double getK() const;

    Vector3D scale(double scalar);

    Vector3D rotateAboutIEuler(double theta);

    Vector3D rotateAboutJEuler(double theta);

    Vector3D rotateAboutKEuler(double theta);

    Vector3D rotateAboutAxisRodrigues(Vector3D axis, double theta);

    [[nodiscard]] Vector3D clone() const;

    Vector3D add(const Vector3D &rightSide);

    void copy(Vector3D v);

    double getMagnitude();

    double getMagnitudeInverse();

    double getMagnitudeSquared();

    double getAngleBetween(Vector3D v);

    Vector3D setIJK(double i, double j, double k );

private:
    [[nodiscard]] double getMagnitudeActual() const;

    [[nodiscard]] double getMagSquaredActual() const;

    [[nodiscard]] double getInverseRootMagActual() const;

    double i, j, k;
    double mag = getMagnitudeActual();
    double magInverse = getInverseRootMagActual();
    double magSquare = getMagSquaredActual();

    void forceUpdateLocal();

    void updateLocal();
};


#endif //PHYS2_VECTOR3D_H
