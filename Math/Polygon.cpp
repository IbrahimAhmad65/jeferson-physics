//

#include "Polygon.h"
#include "NewMatrix.h"

//
// Created by ibrahim on 12/26/22.
Polygon::Polygon(int order) {
    this->order = order;
    this->pointPointer = new Vector3D[order];
}

Polygon::Polygon(Vector3D *vector3D, int order) {
    this->order = order;
    this->pointPointer = vector3D;
}


bool Polygon::intersects(Polygon p) {
    Vector3D p0 = pointPointer[0].clone();
    Vector3D p1 = pointPointer[1].clone();
    Vector3D p2 = pointPointer[2].clone();
    p1.add(p0.clone().scale(-1));
    p2.add(p0.clone().scale(-1));
    Vector3D pCrossP = p1.cross(p2);
    for (int i = 0; i < p.getOrder() - 1; ++i) {
        Vector3D la = p.pointPointer[0].clone();
        Vector3D lab = la.clone() - p.pointPointer[i + 1];

        Vector3D minusLab = lab.clone().scale(-1);
        double denom = minusLab.dot(pCrossP);
        double t = pCrossP.clone().dot(la - p0) / denom;
        double u = (p2.cross(minusLab)).dot(la - p0) / denom;
        double v = minusLab.cross(p1).dot(la - p0) / denom;
        Vector3D intersectionPoint = la + lab*t;


        double c = t +u +v;
    }



    //broooooooooooooooooooooooh
//    double arrForThem[] = {p.pointPointer[0].getI(), p.pointPointer[0].getJ(), p.pointPointer[0].getK(),
//                           p.pointPointer[1].getI(), p.pointPointer[1].getJ(), p.pointPointer[1].getK(),
//                           p.pointPointer[2].getI(), p.pointPointer[2].getJ(), p.pointPointer[2].getK()};
//    double arrForUs[] = {p.pointPointer[0].getI(), p.pointPointer[0].getJ(), p.pointPointer[0].getK(),
//                         p.pointPointer[1].getI(), p.pointPointer[1].getJ(), p.pointPointer[1].getK(),
//                         p.pointPointer[2].getI(), p.pointPointer[2].getJ(), p.pointPointer[2].getK()};
//    NewMatrix themMatrix = NewMatrix(arrForThem, 3, 3);
//    NewMatrix usMatrix = NewMatrix(arrForUs, 3, 3);
//    double j[] = {1, 1, 1};
//    themMatrix.solve(j);
//    double k[] = {1, 1, 1};
//    usMatrix.solve(k);
//    Vector3D themCoefficients = Vector3D(j[0],j[1],j[2]);
//    Vector3D usCoefficients = Vector3D(k[0],k[1],k[2]);



//    // ij rotation
//    // zero first
//    p.translate(pointPointer[0].clone().scale(-1));
//    translate(pointPointer[0].clone().scale(-1));
//
//    double angleBetweenFirst = pointPointer[0].getAngleBetween(Vector3D(1,0,0));
//    p.rotateEulerI(-angleBetweenFirst);
//    rotateEulerI(-angleBetweenFirst);
//    angleBetweenFirst = pointPointer[0].getAngleBetween(Vector3D(0,1,0));
//    p.rotateEulerI(-angleBetweenFirst);
//    rotateEulerI(-angleBetweenFirst);
//    bool both = false;
//    int temp = 0;
//    if(p.pointPointer[0].getK() < 0){
//        temp--;
//    }else if (p.pointPointer[0].getK() > 0){
//        temp ++;
//    }
//    for (int i = 1; i < p.order; ++i) {
//        if(temp != 0){
//            if(temp > 0){
//                both = p.pointPointer[i].getK() < 0;
//            } else{
//                both = p.pointPointer[i].getK() > 0;
//            }
//        }
//        if(both){
//            break;
//        }
//    }
//    if(!both){
//        //all away chack if all greater then all other
//        Vector3D minI = Vector3D(2e307,2e307,0);
//        Vector3D minJ = Vector3D(2e307,2e307,0);
//        Vector3D maxI = Vector3D(0,0,0);
//        Vector3D maxJ = Vector3D(0,0,0);
//        for (int i = 0; i < order; ++i) {
//            if(maxI.getI() < pointPointer[i].getI()){
//                maxI = pointPointer[i].clone();
//            }
//            if(maxJ.getJ() < pointPointer[i].getJ()){
//                maxJ = pointPointer[i].clone();
//            }
//            if(minI.getI() > pointPointer[i].getI()){
//                minI = pointPointer[i].clone();
//            }
//            if(minJ.getJ() > pointPointer[i].getJ()){
//                minJ = pointPointer[i].clone();
//            }
//        }
//        for (int i = 0; i < p.order; ++i) {
//            both = (p.pointPointer[i].getJ() > maxJ.getJ() && p.pointPointer[i].getI() > maxI.getI()) || (p.pointPointer[i].getJ() < minJ.getJ() && p.pointPointer[i].getI() < minI.getI());
//            if(both){
//                break;
//            }
//        }
//    }
//    // both is true if min/max rules are broken
//




    return false;
}

void Polygon::translate(Vector3D v) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].add(v);
    }
}

int Polygon::getOrder() const {
    return order;
}

void Polygon::rotateRodrigues(Vector3D axis, double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutAxisRodrigues(axis, theta);
    }
}

void Polygon::rotateEulerI(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutIEuler(theta);
    }
}

void Polygon::rotateEulerJ(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutJEuler(theta);
    }
}

void Polygon::rotateEulerK(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutKEuler(theta);
    }
}

Vector3D *Polygon::getPointList() {
    return pointPointer;
}

