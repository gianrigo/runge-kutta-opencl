__kernel void matrixmulti(__global float* a, __global float* b, __global float* c, __global int* size)
{
    unsigned int row = get_global_id(0);
    unsigned int column = get_global_id(1);
    unsigned i;
    row *= (*size);
    c[row+column] = 0;
    for( i = 0; i < (*size); i++ ) {
      c[row+column] += a[row+i]*b[column+i*(*size)];
    }
}
