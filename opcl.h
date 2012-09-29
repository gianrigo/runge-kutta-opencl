#include "../opencl10/CL/opencl.h"
#ifdef cl_khr_fp64
  #define TYPE double
  #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
  #define TYPE double
  #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
  #define TYPE float
#endif

typedef struct vec{
  TYPE x;
  TYPE y;
  TYPE z;
} vector;

typedef vector *vector_field;

void opencl_init(char*, vector*, int, TYPE, int, int, int, vector_field field, vector*, int*, int);
