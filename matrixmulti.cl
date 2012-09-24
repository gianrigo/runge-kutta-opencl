typedef struct{
 float x;
 float y;
 float z;
}teste;


__kernel void matrixmulti(__global float* v0, __global int *count_v0, __global float *h, __global int *n_x,__global int *n_y,__global int *n_z, __global const teste* field, __global float *points, __global float* n_points, __global int* max_points)
{
    unsigned int row = get_global_id(0);
    unsigned int column = get_global_id(1);
    unsigned int deep = get_global_id(2);
    unsigned int i, j;
    row *= (*n_x);
    n_points[row+column+deep] = 0;
    for( i = 0; i < (*n_x); i++ ) {
      for( j = 0; j < (*n_y); j++ ) 
        n_points[row+column+deep] += v0[row+i+j]*(field[column+i*(*n_x)+j*(*n_y)].x)*(field[column+i*(*n_x)+j*(*n_y)].y)*(field[column+i*(*n_x)+j*(*n_y)].z);
    }
    points[row+column+deep] = (field[column+i*(*n_x)+j*(*n_y)].x)*(field[column+i*(*n_x)+j*(*n_y)].y)*(field[column+i*(*n_x)+j*(*n_y)].z);
}
