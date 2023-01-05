#include <cmath>
#include <iostream>
#include "Triangle.h"


bool onLine(line l1, Point p) {
    // Check whether p is on the line or not
    if (p.pos.getI() <= std::max(l1.p1.pos.getI(), l1.p2.pos.getI())
        && p.pos.getI() <= std::min(l1.p1.pos.getJ(), l1.p2.pos.getJ())
        && (p.pos.getJ() <= std::max(l1.p1.pos.getJ(), l1.p2.pos.getJ())
            && p.pos.getJ() <= std::min(l1.p1.pos.getJ(), l1.p2.pos.getJ())))
        return true;

    return false;
}

int direction(Point a, Point b, Point c) {
    double val = ((b.pos.getJ() - a.pos.getJ()) * (c.pos.getI() - b.pos.getI())
                    - (b.pos.getI() - a.pos.getI()) * (c.pos.getJ() - b.pos.getJ()));

    if (val == 0)

        // Colinear
        return 0;

    else if (val < 0)

        // Anti-clockwise direction
        return 2;

    // Clockwise direction
    return 1;
}

bool isIntersect(line l1, line l2) {
    // Four direction for two lines and points of other line
    int dir1 = direction(l1.p1, l1.p2, l2.p1);
    int dir2 = direction(l1.p1, l1.p2, l2.p2);
    int dir3 = direction(l2.p1, l2.p2, l1.p1);
    int dir4 = direction(l2.p1, l2.p2, l1.p2);

    // When intersecting
    if (dir1 != dir2 && dir3 != dir4)
        return true;

    // When p2 of line2 are on the line1
    if (dir1 == 0 && onLine(l1, l2.p1))
        return true;

    // When p1 of line2 are on the line1
    if (dir2 == 0 && onLine(l1, l2.p2))
        return true;

    // When p2 of line1 are on the line2
    if (dir3 == 0 && onLine(l2, l1.p1))
        return true;

    // When p1 of line1 are on the line2
    if (dir4 == 0 && onLine(l2, l1.p2))
        return true;

    return false;
}

bool checkInside(Point poly[], int n, Point p) {

    // When polygon has less than 3 edge, it is not polygon
    if (n < 3)
        return false;

    // Create a point at infinity, y is same as point p
    line exline = {p, Vector3D(9999, p.pos.getJ(),0)};
    int count = 0;
    int i = 0;
    do {

        // Forming a line from two consecutive points of
        // poly
        line side = {poly[i], poly[(i + 1) % n]};
        if (isIntersect(side, exline)) {

            // If side is intersects exline
            if (direction(side.p1, p, side.p2) == 0)
                return onLine(side, p);
            count++;
        }
        i = (i + 1) % n;
    } while (i != 0);

    // When count is odd
    return count & 1;
}

Triangle::Triangle(Vector3D *vector3D) {
    this->pointPointer = vector3D;
    this->center = Vector3D();
    for (int i = 0; i < order; ++i) {
        center += pointPointer[i];
    }
    center /= order;
}

Triangle::Triangle(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2) {
    pointPointer = new Vector3D[3];
    pointPointer[0] = p0.clone();
    pointPointer[1] = p1.clone();
    pointPointer[2] = p2.clone();

    this->center = Vector3D();
    for (int i = 0; i < order; ++i) {
        center += pointPointer[i];
    }
    center /= order;
}

// takes this long for both sided check 0.000036453508 for triangle
bool Triangle::intersects(const Triangle &p) {
    Vector3D p0 = pointPointer[0].clone();
    Vector3D p1 = pointPointer[1].clone();
    Vector3D p2 = pointPointer[2].clone();
    p1.add(p0.clone().scale(-1));
    p2.add(p0.clone().scale(-1));
    Vector3D pCrossP = p1.cross(p2);
    Vector3D themp0 = p.pointPointer[0].clone();
    Vector3D themp1 = p.pointPointer[1].clone();
    Vector3D themp2 = p.pointPointer[2].clone();
    themp1.add(themp0.clone().scale(-1));
    themp2.add(themp0.clone().scale(-1));
    Vector3D themNormal = themp1.cross(themp2);
    Triangle newP = p.clone();
    if((themNormal.cross(pCrossP).getMagnitude()) < .001){
        return false;
    }
    if(std::abs(themNormal.dot(pCrossP)) < .001){
        newP.rotateEulerJ(.001);
        newP.rotateEulerI(.001);
        newP.rotateEulerJ(.001);
        themp0 = newP.pointPointer[0].clone();
        themp1 = newP.pointPointer[1].clone();
        themp2 = newP.pointPointer[2].clone();
        themp1.add(themp0.clone().scale(-1));
        themp2.add(themp0.clone().scale(-1));
        themNormal = themp1.cross(themp2);
    }



    auto *intersectionPoints = new Vector3D[newP.getOrder() - 1];
    for (int i = 0; i < newP.getOrder() - 1; ++i) {
        Vector3D la = newP.pointPointer[0].clone();
        Vector3D lab = la.clone() - newP.pointPointer[i + 1];

        Vector3D minusLab = lab.clone().scale(-1);
        double denom = minusLab.dot(pCrossP);
        double t = pCrossP.clone().dot(la - p0) / denom;
        if (denom > 0) {
            intersectionPoints[i] = la + lab * t;
        } else {
            double nan = 0.0 / 0.0;
            intersectionPoints[i] = Vector3D(nan, nan, nan);
        }
    }
    Triangle usClone = clone();
    p0 = pointPointer[0].clone();
    p1 = pointPointer[1].clone();
    p2 = pointPointer[2].clone();
    p1.add(p0.clone().scale(-1));
    p2.add(p0.clone().scale(-1));
    Vector3D normal = p1.cross(p2);


    Vector3D k = Vector3D(0, 0, 1);
    normal.copy(normal.cross(k));
    usClone.rotateRodrigues(normal, -normal.getAngleBetween(k));
    auto* polygon = new Point[newP.order];
    for (int i = 0; i < newP.getOrder(); ++i) {
        polygon[i] = Point{newP.pointPointer[i].clone()};
    }
    auto* polygon2 = new Point[newP.order];
    for (int i = 0; i < newP.getOrder(); ++i) {
        polygon2[i] = Point{usClone.pointPointer[i].clone()};
    }
    for (int i = 0; i < newP.getOrder(); ++i) {
        Vector3D v = intersectionPoints[i];
        if(!(std::isnan(v.getI()) || std::isnan(v.getJ()) || std::isnan(v.getK()))){
            v.rotateAboutAxisRodrigues(normal, -normal.getAngleBetween(k));
            Point point = {v};
            if(checkInside(polygon,newP.getOrder(),point) && checkInside(polygon2,newP.getOrder(),point) ){
                return true;
            }
        }
    }
    return false;


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

void Triangle::translate(const Vector3D &v) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].add(v);
    }
}

int Triangle::getOrder() const {
    return order;
}

void Triangle::rotateRodrigues(const Vector3D &axis, double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutAxisRodrigues(axis, theta);
    }
}

void Triangle::rotateEulerI(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutIEuler(theta);
    }
}

void Triangle::rotateEulerJ(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutJEuler(theta);
    }
}

void Triangle::rotateEulerK(double theta) {
    for (int i = 0; i < order; ++i) {
        pointPointer[i].rotateAboutKEuler(theta);
    }
}

Vector3D *Triangle::getPointList() {
    return pointPointer;
}

Triangle Triangle::clone() const {
    auto *newPointer = new Vector3D[order];
    for (int i = 0; i < order; ++i) {
        newPointer[i] = pointPointer[i].clone();
    }
    return Triangle(newPointer);
}

Triangle::Triangle() = default;

std::string Triangle::toString() const {
    std::string out = "";
    for (int i = 0; i < 3; ++i) {
    out += pointPointer[i].toString();
    out += ", ";
    }
    return out;
}
