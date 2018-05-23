__kernel void mmul(
        __global const float *dataIn0, __global const float *dataIn1, __global int *aSize, __global float *result)
{
    int gid = get_global_id(0);
    result = 0;
    for(int i = 0; i < *aSize; i++)
    {
        result[gid] += dataIn0[i] * dataIn1[i];
    }
}
