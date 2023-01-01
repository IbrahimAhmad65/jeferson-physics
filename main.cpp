#include <iostream>
#include <xmmintrin.h>
#include <sys/time.h>
#include "Math/Vector3D.h"
#include "Tests/VectorPerformanceTest.h"
#include "Math/Matrix.h"
#include "Math/NewMatrix.h"

int main() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    VectorPerformanceTest v = VectorPerformanceTest();
    v.test();
    double data[] = {1,2,-2,-3};
    NewMatrix m = NewMatrix(data,2,2);
    double j[] = {1,1};
    std::cout<< m.solve(j)[0] << " " << m.solve(j)[1] <<" " << std::endl;

    return 0;
}
