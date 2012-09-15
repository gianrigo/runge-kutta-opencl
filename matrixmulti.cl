__kernel void matrixmulti(__global float* v0, __global int *count_v0, __global double *h, __global int *n_x,__global int *n_y,__global int *n_z, __global float* field, __global float *points, __global float* n_points, __global int* max_points)
{
    unsigned int row = get_global_id(0);
    unsigned int column = get_global_id(1);
    unsigned i;
    row *= (*max_points);
    n_points[row+column] = 0;
    for( i = 0; i < (*max_points); i++ ) {
      n_points[row+column] += v0[row+i]*field[column+i*(*max_points)];
    }
}
