#include <stdio.h>
#include "opcl.h"

int main(){
  TYPE *v0, h, *field, *points, *n_points;
  int i, j, count_v0, n_x, n_y, n_z, max_points;

  n_x = n_y = n_z = 3;
  count_v0 = 9;
  h = 0.01;
  max_points = 9;

  /* Initializing the Matrix. */  
  v0 = (TYPE*) malloc(count_v0*sizeof(TYPE));
  field = (TYPE*) malloc(n_x*n_y*sizeof(TYPE));
  points = (TYPE*) malloc(max_points*sizeof(TYPE));
  n_points = (TYPE*) malloc(max_points*sizeof(TYPE));

  for( i = 0; i < 3; i++ ){
    for( j = 0; j < 3; j++ ){
      v0[i*3+j] = i+j;
      field[i*3+j] = 2;
      points[i*3+j] = 3;
    }
  }

  opencl_init((char*)"matrixmulti", v0, count_v0, h, n_x, n_y, n_z,field, points, n_points, max_points);

  /* Validating the results. */
  for( i = 0; i < 3; i++ ){
    for( j = 0; j< 3; j++ ){
      printf("%f  ", n_points[i*3+j]);
    }
    printf("\n");
  }
  
  printf("\n");
  for( i = 0; i < 3; i++ ){
    for( j = 0; j< 3; j++ ){
      printf("%f  ", points[i*3+j]);
    }
    printf("\n");
  }

  free(v0);
  free(field);
  free(points);
  free(n_points);

  return 0;
}
