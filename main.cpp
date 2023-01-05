#include <iostream>
#include <xmmintrin.h>
#include <sys/time.h>
#include "Math/Vector3D.h"
#include "Math/Triangle.h"
#include "Tests/VectorPerformanceTest.h"
#include "Math/WaveFrontOBJReader.h"


int main() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//    VectorPerformanceTest v = VectorPerformanceTest();
//    v.test();
    struct timeval start, end;

    gettimeofday(&start, NULL);
    bool a;
    bool b;
    for (int i = 0; i < 1; ++i) {
//        Vector3D polygonA[] = {Vector3D(-1, 1, -1), Vector3D(1, 1, -1), Vector3D(1, 1, 1)};
//        Vector3D polygonB[] = {Vector3D(-.9, 1+.1, -1+.1), Vector3D(1+.5, 1+.1, -1+.1), Vector3D(1+.5, 1+.1, 1+.1)};
        Vector3D polygonA[] = {Vector3D(1, 0, 1), Vector3D(2, 0, 2), Vector3D(-1, 0, 2), Vector3D(-3, 0, 2)};
        Vector3D polygonB[] = {Vector3D(1, 0, 1.5), Vector3D(2, 5, 2), Vector3D(-1, -1, 2)};
//        Triangle usClone = Triangle({4.100000,1.100000,1.100000}, {2.100000,-0.900000,1.100000}, {4.100000,-0.900000,1.100000});
//        Triangle them = Triangle({-1.000000,1.000000,1.000000}, {-1.000000,-1.000000,-1.000000}, {-1.000000,-1.000000,1.000000});
        Triangle usClone = Triangle(polygonA[0],polygonA[1],polygonA[2]);
        Triangle them = Triangle(polygonB[0],polygonB[1],polygonB[2]);
        a = usClone.intersects(them);
        b = them.intersects(usClone);
    }
//    bool a;
//    bool b;
//    for (int i = 0; i < 3000000; ++i) {
//        Vector3D polygonA[] = {Vector3D(1, 0, 1), Vector3D(2, 0, 2), Vector3D(-1, 0, 2), Vector3D(-3, 0, 2)};
//        Vector3D polygonB[] = {Vector3D(1, 0, 1.5), Vector3D(2, 5, 2), Vector3D(-1, -1, 2)};
//        auto usClone = Triangle(polygonA);
//        auto them = Triangle(polygonB);
//        a = usClone.intersects(them);
//        b = them.intersects(usClone);
//    }


//    WaveFrontOBJReader objReader = WaveFrontOBJReader();
//    Mesh m = objReader.read("/home/ibrahim/tricube.obj");
//    Mesh mD = objReader.read("/home/ibrahim/tricube.obj");
//    mD.translate({3.1,.1,.1});
//    std::cout << m.collidedWith(mD) << std::endl;



    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6; // in seconds

    printf("time program took %f seconds to execute: ", time_taken);
    std::cout << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}
