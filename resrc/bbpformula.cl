__kernel void bbpformula_step(const unsigned int s, const unsigned int m, const __global int *A, __global float *R)
{
    unsigned int identifier = get_global_id(0);

    float result = 0;

    for (unsigned int i = 1; i <= m; ++i) {
        result += ((float) A[i - 1]) / pow((m * identifier) + i, s);
    }

    R[identifier] = result;
}