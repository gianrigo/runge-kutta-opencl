#include <stdio.h>
#include "opcl.h"

/* Objetos do Open CL */
cl_platform_id platform;
cl_context context;
cl_device_id* devices;
cl_command_queue queue;
cl_kernel kernel;
cl_program program;
cl_event event;
cl_mem opclMatrixA, opclMatrixB, opclMatrixC;

/* Informações sobre os devices */
unsigned int devices_found;
unsigned int device_used = 0;

unsigned int opencl_create_platform(unsigned int num_platforms){
  int num_platforms_found;
  
  clGetPlatformIDs( 0, NULL, (cl_uint*)&num_platforms_found);
  if ( clGetPlatformIDs( num_platforms, &platform, (cl_uint*)&num_platforms_found ) != CL_SUCCESS ){
    printf("\nERROR: Failed to create plataform.\n");
    exit(-1);
  }
  return num_platforms_found;
}

unsigned int opencl_get_devices_id(cl_device_type device_type) {
  
  clGetDeviceIDs(platform, device_type, 0, NULL, &devices_found);
  devices = (cl_device_id*) malloc(devices_found*(sizeof(cl_device_id)));
  
  if(clGetDeviceIDs( platform, device_type, devices_found, devices, NULL) != CL_SUCCESS){
    printf("\nERROR: Failed to get devices id's.\n");
    exit(-1);
  }
  return devices_found;
}

void opencl_create_context(){
  if( (context = clCreateContext( 0, 1, devices, NULL, NULL, NULL )) == NULL ){
    printf("\nERROR: Failed to create context.\n");
    exit(-1);
  }
}

void opencl_create_queue(){
  if((queue = clCreateCommandQueue(context, devices[device_used], 0, NULL)) == NULL ){
    printf("\nERROR: Failed to create queue.\n");
    exit(-1);
  }
}

/* Funções auxiliares para a criação do program */
char* load_program_from_source(char* program_path, int *size) {
  char* program_string;
  FILE* prog;

  prog = fopen(program_path, "r");
  fseek(prog, 0, SEEK_END);
  *size = ftell(prog);
  fseek(prog, 0, SEEK_SET);

  program_string = (char*) malloc((*size+1)*sizeof(char));
  *size = fread(program_string, 1, *size, prog);
  fclose(prog);
  program_string[*size] = '\0';

  return program_string;
}

void opencl_build_program(){
  int err;
  char *build_log;
  size_t ret_val_size;
                
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if ( err != CL_SUCCESS ) {
    printf("\nERROR: Failed to build program.\n");
    clGetProgramBuildInfo(program, devices[device_used], CL_PROGRAM_BUILD_LOG, 0, NULL, &ret_val_size);

    build_log = (char*) malloc((ret_val_size+1)*sizeof(char));
    clGetProgramBuildInfo(program, devices[device_used], CL_PROGRAM_BUILD_LOG, ret_val_size, build_log, NULL);
    build_log[ret_val_size] = '\0';
    printf("BUILD LOG: \n %s\n", build_log);
    exit(-1);
  }
}
/* Fim das funções auxiliares para a criação do program */

void opencl_create_program(char* program_path){
  char* program_source;
  int size;
  size_t prog_size;
  cl_int err;
  
  program_source = load_program_from_source(program_path, &size);
  prog_size = (size_t)size;
  program = clCreateProgramWithSource(context, 1, (const char**)&program_source, &prog_size, &err);
  if ( err != CL_SUCCESS ){
    printf("\nERROR: Failed to create program.\n");
    exit(-1);
  }
  opencl_build_program();
}

void opencl_create_kernel(char* kernel_name){
  cl_int err;

  kernel = clCreateKernel( program, kernel_name, &err);
  if ( kernel == NULL ){
    printf("\nERROR: Failed to create kernel %s.\n",kernel_name);
    exit(-1);
  }
}

/********************** ALTERAR ************************/
void prepare_kernel(int tam){
  TYPE MatrixA[3][3], MatrixB[3][3];
  int i, j, size;
  cl_mem matrix_size;

  for ( i = 0; i < 3; i++ ) {
    for ( j = 0; j < 3; j++ ) {
      MatrixA[i][j] = i+j;
      MatrixB[i][j] = 2;
    }
  }
  size = 3;

  /* Criação dos buffers que o OpenCL vai usar. */
  opclMatrixA = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(TYPE)*tam*tam, MatrixA, NULL);
  opclMatrixB = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(TYPE)*tam*tam, MatrixB, NULL);
  opclMatrixC = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(TYPE)*tam*tam, NULL, NULL);
  matrix_size = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), (&size), NULL);

  clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&opclMatrixA);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&opclMatrixB);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&opclMatrixC);
  clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&matrix_size);

  clFinish(queue);
}

void opencl_run_kernel(TYPE **Matriz, int size) {
  size_t work_dim[2] = { 3, 3 };
  TYPE Mc[3][3];
  int i, j;
  
  prepare_kernel(size);
  clEnqueueNDRangeKernel(queue, kernel, 2, NULL, work_dim, NULL, 0, NULL, &event);
  clReleaseEvent(event);
  clFinish(queue);
  if( clEnqueueReadBuffer(queue, opclMatrixC, CL_TRUE, 0, sizeof(TYPE)*size*size, &Mc, 0, NULL, &event) == CL_INVALID_VALUE )
    printf("\nERROR: Failed to read buffer.\n");
  clReleaseEvent(event);

  for( i = 0; i < size; i++ )
    for( j = 0; j< size; j++ )
      Matriz[i][j] = Mc[i][j];
}

void opencl_init(char* kernel_name, TYPE **minhaMatriz, int size){
  unsigned int num_platforms, num_devices;

  printf("Starting OpenCL platform...");
  num_platforms =  opencl_create_platform(2); 
  printf(" Num Platforms = %d OK.\n", num_platforms);
   
  printf("Searching for devices...");
  num_devices = opencl_get_devices_id(CL_DEVICE_TYPE_GPU);
  printf(" Num devices = %d OK.\n", num_devices);

  printf("Creating context...");
  opencl_create_context();
  printf(" OK.\n");
    
  printf("Creating queue...");
  opencl_create_queue();
  printf(" OK.\n");
  
  printf("Creating program...");
  opencl_create_program((char*)"matrixmulti.cl");
  printf(" OK.\n");

  printf("Creating kernel...");
  opencl_create_kernel(kernel_name);
  printf(" OK.\n");

  printf("Running the kernel...");
  opencl_run_kernel(minhaMatriz,size);
  printf(" OK.\n");
}





