//void rk2(vector *v0, int count_v0, double h, int n_x, int n_y, int n_z, vector_field field, vector ***points, int **n_points);
//void rk4(vector *v0, int count_v0, double h, int n_x, int n_y, int n_z, vector_field field, vector ***points, int **n_points);
#include "opcl.h"
void rk2(TYPE* v0, int count_v0, TYPE h, int n_x,int n_y,int n_z, teste *field, TYPE *points, TYPE* n_points, int max_points);
void rk4(TYPE* v0, int count_v0, TYPE h, int n_x,int n_y,int n_z, teste *field, TYPE *points, TYPE* n_points, int max_points);
