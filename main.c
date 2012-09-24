#include <stdio.h>
#include "opcl.h"

int main(){
  TYPE *v0, h, *points, *n_points;
  teste *field;
  int i, j, k, count_v0, n_x, n_y, n_z, max_points;

  n_x = n_y = n_z = 3;
  count_v0 = 27;
  h = 0.01;
  max_points = 27;

  /* Initializing the Matrix. */  
  v0 = (TYPE*) malloc(count_v0*sizeof(TYPE));
  field = (teste*) malloc(n_x*n_y*n_y*sizeof(teste));
  points = (TYPE*) malloc(max_points*sizeof(TYPE));
  n_points = (TYPE*) malloc(max_points*sizeof(TYPE));

  for( i = 0; i < 27; i++ ){
        v0[i] = i;
        field[i].x = 2;
        field[i].y = 2;
        field[i].z = 2;
        points[i] = 3;
  }

 for( i = 0; i < 3; i++ ){
    for( j = 0; j < 3; j++ ){
      for( k = 0; k < 3; k++ ){
    if( k % 3 == 0)
      printf("\n");      
    printf("%f  ", v0[i*3*3+j*3+k]);
  }
}
}


  opencl_init((char*)"matrixmulti", v0, count_v0, h, n_x, n_y, n_z,field, points, n_points, max_points);

  /* Validating the results. */
  for( i = 0; i < 27; i++ ){
    if( i % 3 == 0)
      printf("\n");      
    printf("%f  ", n_points[i]);
  }
  
  printf("\n");
  for( i = 0; i < 27; i++ ){
    if( i % 3 == 0)
      printf("\n");      
    printf("%f  ", points[i]);
  }

  free(v0);
  free(field);
  free(points);
  free(n_points);

  return 0;
}
