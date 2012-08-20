#include <stdio.h>
#include "opcl.h"

#define TYPE float

int main(){
  TYPE **M;
  int i, j, size;

  size = 3;

  /* Initializing the Matrix. */  
  M = (TYPE**) malloc(size*sizeof(TYPE*));
  for(i=0; i < size; i++)
    M[i] = (TYPE*) malloc(size*sizeof(TYPE));  

  opencl_init((char*)"matrixmulti", M,size);

  /* Validating the results. */
  for( i = 0; i < size; i++ ){
    for( j = 0; j< size; j++ ){
      printf("%f  ", M[i][j]);
    }
    printf("\n");
  }

  for(i=0; i < size; i++)
    free(M[i]);
  free(M);

  return 0;
}
