#include "BBPFormula.h"

double BBPFormula(cl_uint s, cl_uint b, cl_uint m, cl_int *A, cl_uint k) {
    double value = 0;

    for (cl_uint i = 0; i < k; ++i) {
        double t = 0;

        for (cl_uint j = 1; j <= m; ++j) {
            cl_uint pow_base = (m * i + j), pow_value = 1;

            for (cl_uint pow_i = 0; pow_i < s; ++pow_i) {
                pow_value *= pow_base;
            }

            t += A[j - 1] / ((double) pow_value);
        }

        cl_uint pow_base = b, pow_value = 1;

        for (cl_uint pow_i = 0; pow_i < i; ++pow_i) {
            pow_value *= pow_base;
        }

        value += (1.0 / pow_value) * t;
    }

    return value;
}
