__kernel void matrixmulti(__global float *v0, int count_v0, double h, int n_x, int n_y, int n_z, __global float *field, __global float *points, __global int *n_points, int max_points)
{
    unsigned int row = get_global_id(0);
    unsigned int column = get_global_id(1);
    unsigned i;
    row *= (*size);
    n_points[row+column] = 0;
    for( i = 0; i < (*n_x); i++ ) {
      n_points[row+column] += points[row+i]*field[column+i*(*n_x)];
    }
}
