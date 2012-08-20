#include <stdio.h>
#include "opcl.h"

int main() {
  int **M;
  int i, j, size;

  size = 3;

  /* Initializing the Matrix. */  
  M = (int**) malloc(size*sizeof(int*));
  for(i=0; i < size; i++)
    M[i] = (int*) malloc(size*sizeof(int));  

  opencl_init((char*)"matrixmulti", M,size);

  /* Validating the results. */
  for( i = 0; i < size; i++ ){
    for( j = 0; j< size; j++ ){
      printf("%d  ", M[i][j]);
    }
    printf("\n");
  }

  for(i=0; i < size; i++)
    free(M[i]);
  free(M);

  return 0;
}
