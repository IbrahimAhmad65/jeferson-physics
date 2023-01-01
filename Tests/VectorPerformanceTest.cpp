//
// Created by ibrahim on 12/30/22.
//

#include "VectorPerformanceTest.h"
#include <iostream>
#include <xmmintrin.h>
#include <sys/time.h>
#include "../Math/Vector3D.h"
bool VectorPerformanceTest::test() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    struct timeval start, end;

    gettimeofday(&start, NULL);
    for (int i = 0; i < 100000; ++i) {
        Vector3D v = Vector3D(random(),random(),random());
        v.updateMagsOnChange = false;
        v.scale(random());
        v.getMagnitude();
        v.scale(random());
        v.scale(random());
        v.getMagnitudeInverse();
        v.scale(random());
        v.scale(random());
        v.scale(random());
        v.rotateAboutAxisRodrigues(Vector3D(random(),random(),random()),random());
    }

    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6; // in seconds

    printf("time program took %f seconds to execute: ", time_taken);
    return time_taken < 1;
}
