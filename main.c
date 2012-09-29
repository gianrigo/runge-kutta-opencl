#include <stdio.h>
#include "rk.h"

int main(){
  vector *v0, *points; 
  TYPE h;
  int *n_points;
  vector_field field;
  int i,  count_v0, n_x, n_y, n_z, max_points;

  n_x = n_y = n_z = 3;
  count_v0 = 27;
  h = 0.01;
  max_points = 27;

  /* Initializing the Matrix. */  
  v0 = (vector*) malloc(count_v0*sizeof(vector));
  field = (vector_field) malloc(n_x*n_y*n_y*sizeof(vector));
  points = (vector*) malloc(max_points*sizeof(vector));
  n_points = (int*) malloc(max_points*sizeof(int));

  for( i = 0; i < max_points; i++ ){
        v0[i].x = i;
        v0[i].y = i;
        v0[i].z = i;
        field[i].x = 2;
        field[i].y = 2;
        field[i].z = 2;
        points[i].x = 3;
        points[i].y = 3;
        points[i].z = 3;
  }

  rk2(v0, count_v0, h, n_x, n_y, n_z,field, points, n_points, max_points);

  /* Validating the results. */
  for( i = 0; i < max_points; i++ ){
    if( i % 3 == 0)
      printf("\n");      
    printf("%d  ", n_points[i]);
  }
  
  printf("\n");
  for( i = 0; i < max_points; i++ ){
    if( i % 3 == 0)
      printf("\n");      
    printf("(%f, %f, %f) ", points[i].x, points[i].y, points[i].z);
  }
  printf("\n"); 
  free(v0);
  free(field);
  free(points);
  free(n_points);

  return 0;
}
