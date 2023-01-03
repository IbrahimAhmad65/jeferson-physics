#include <iostream>
#include <xmmintrin.h>
#include <sys/time.h>
#include "Math/Vector3D.h"
#include "Math/Polygon.h"
#include "Tests/VectorPerformanceTest.h"


int main() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//    VectorPerformanceTest v = VectorPerformanceTest();
//    v.test();
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    struct timeval start, end;

    gettimeofday(&start, NULL);
    bool a;
    bool b;
    for (int i = 0; i < 3000000; ++i) {
        Vector3D polygonA[] = {Vector3D(1, 0, 1), Vector3D(2, 0, 2), Vector3D(-1, 0, 2), Vector3D(-3, 0, 2)};
        Vector3D polygonB[] = {Vector3D(1, 0, 1.5), Vector3D(2, 5, 2), Vector3D(-1, -1, 2)};
        Polygon usClone = Polygon(polygonA, 4);
        Polygon them = Polygon(polygonB, 3);
        a = usClone.intersects(them);
        b = them.intersects(usClone);
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
