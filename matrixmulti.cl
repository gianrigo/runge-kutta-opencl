__kernel void matrixmulti(__global float *v0,__global int *count_v0,__global double *h,__global int *n_x,__global int *n_y,__global int *n_z, __global float *field, __global float *points, __global int *n_points, __global int *max_points)
{
    unsigned int row = get_global_id(0);
    unsigned int column = get_global_id(1);
    unsigned i;
    row *= (*n_x);
    n_points[row+column] = 0;
    for( i = 0; i < (*n_y); i++ ) {
      n_points[row+column] += points[row+i]*field[column+i*(*n_z)];
    }
}
