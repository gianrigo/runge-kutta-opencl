#include <stdio.h>
#include "opcl.h"

int main() {
  int **M, i, j;

  /* Initializing the Matrix. */  
  M = (int**) malloc(5*sizeof(int));
  for(i=0; i < 3; i++)
    M[i] = (int*) malloc(3*sizeof(int));  

  /*printf("Before\n");
  printf("\nSize %lu\n",sizeof(M[2])/sizeof(int));*/

  opencl_init(M);

/*  printf("After\n");
  printf("\nSize %lu\n",sizeof(M)/sizeof(int));*/

  /* Validating the results. */
  for( i = 0; i < 3; i++ ){
    for( j = 0; j< 3; j++ ){
      printf("%d  ", M[i][j]);
    }
    printf("\n");
  }

  for(i=0; i < 3; i++)
    free(M[i]);
  free(M);


  return 0;
}
