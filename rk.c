#include "rk.h"

void rk2(vector *v0, int count_v0, TYPE h, int n_x, int n_y, int n_z, vector_field field, vector *points, int *n_points, int max_points){
  opencl_init((char*)"rk2_kernel", v0, count_v0, h, n_x, n_y, n_z,field, points, n_points, max_points);
}

/*void rk4(vector *v0, int count_v0, double h, int n_x, int n_y, int n_z, vector_field field, vector ***points, int **n_points TYPE* v0, int count_v0, TYPE h, int n_x,int n_y,int n_z, teste *field, TYPE *points, TYPE* n_points, int max_points){
  opencl_init((char*)"rk4_kernel""matrixmulti", v0, count_v0, h, n_x, n_y, n_z,field, points, n_points, max_points);
}
*/
