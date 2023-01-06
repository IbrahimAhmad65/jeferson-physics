//
// Created by ibrahim on 12/26/22.
//

#ifndef PHYS2_MESH_H
#define PHYS2_MESH_H


#include "Vector3D.h"
#include "Triangle.h"

class Mesh {
public:
    explicit Mesh();

    Mesh(Triangle *p, double density, int numOfFaces, int id);

    Mesh(double mass, Triangle *p, int numOfFaces, int id);

    // actually two sided
    bool collidedWith(const Mesh &m) const;

    void translate(const Vector3D &v);

    [[nodiscard]] int getNumOfFaces() const;

    double getMass() const;

    double getDensity() const;

    void rotateRodriguesAboutCOM(const Vector3D &axis, double theta) const;

    void rotateRodriguesAboutGEOMCenter(const Vector3D &axis, double theta) const;

    void rotateEulerJAboutCom(double theta) const;

    void rotateEulerKAboutCom(double theta) const;

    void rotateEulerIAboutCom(double theta) const;

    [[nodiscard]] Mesh clone() const;

    void applyForce(Vector3D f, double time, const Vector3D &globalPos);

    [[nodiscard]] Vector3D getCOM() const;

    [[nodiscard]] double getVolume() const;

//    double computeMomentOfIntertia(const Vector3D& axis);
    // used until i stop being lazy. Ask mech for values lol
    void setMomentOfInertia(double moment);

    Vector3D getGeomCenter();

    void setID(int id);
private:
    int id{};
    Vector3D *boundingBox{};
    Triangle *faces{};
    Vector3D velocity;
    Vector3D angularVelocityRodrigues;
    int numOfFaces{};
    double density{};
    double mass{};
    double momentOfInertia{};
    Vector3D axisOfMOI;
    Vector3D com;
    double volume{};

    double rOfBounds{};

    Vector3D geomCenter;
};


#endif //PHYS2_MESH_H
