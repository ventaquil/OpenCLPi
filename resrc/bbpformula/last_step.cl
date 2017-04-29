__kernel void bbpformula_last_step(const unsigned int b, __global float *R)
{
    unsigned int identifier = get_global_id(0);

    R[identifier] *= (1.0 / pow(b, identifier));
}
