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

typedef struct{
 float x;
 float y;
 float z;
}teste;



void opencl_init(char*, TYPE*, int, TYPE, int, int, int, teste*, TYPE*, TYPE*, int);
