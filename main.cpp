#include <iostream>
#include <xmmintrin.h>
#include <sys/time.h>
#include "Math/Vector3D.h"
#include "Math/Triangle.h"
#include "Tests/VectorPerformanceTest.h"
#include "Math/WaveFrontOBJReader.h"


int main() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

    bool a = false;
    bool b = false;
    struct timeval start, end;
    WaveFrontOBJReader objReader = WaveFrontOBJReader();
    Mesh m = objReader.read("/home/ibrahim/tricube.obj");
    Mesh mD = objReader.read("/home/ibrahim/tricube.obj");
    gettimeofday(&start, NULL);

    //{2.100000,1.100000,1.100000}, {2.100000,-0.900000,-0.900000}, {2.100000,-0.900000,1.10000})
    //{-1.000000,1.000000,1.000000}, {-1.000000,-1.000000,-1.000000}, {-1.000000,-1.000000,1.000000}
//    for (int i = 0; i < 1; ++i) {
//        Vector3D polygonA[] = {{2.100000,1.100000,1.100000}, {2.100000,1.100000,-0.900000}, {2.100000,-0.900000,-0.900000}};
//        Vector3D polygonB[] = {{1.000000,1.000000,1.000000}, {-1.000000,1.000000,1.000000}, {-1.000000,-1.000000,1.000000}};
//        Triangle usClone = Triangle(polygonA[0],polygonA[1],polygonA[2]);
//        Triangle them = Triangle(polygonB[0],polygonB[1],polygonB[2]);
//        a = usClone.intersects(them);
//        b = them.intersects(usClone);
//    }



    for (int i = 0; i < 3000000; ++i) {
        mD.translate({2.1,.1,.1});
        a = m.collidedWith(mD) ;
    }



    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6; // in seconds

    printf("time program took %f seconds to execute: ", time_taken);
    std::cout << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}
