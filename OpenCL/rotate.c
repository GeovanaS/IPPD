//g++ -std=c++0x -o rotate rotate.c -lOpenCL
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
    // Create the two input vectors
    int i;
    const int LIST_SIZE = 256*256;
    int *ip = NULL;
    for(i=0;i<LIST_SIZE;i++){
        ip[i] = i;
    }
    int *op = NULL;
    for(i=0;i<LIST_SIZE;i++){
        op[i] = i;
    }
    /*int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    for(i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
    }

    int *B = (int*)malloc(sizeof(int)*LIST_SIZE);
    for(i = 0; i < LIST_SIZE; i++) {
        B[i] = i;
    }
    */
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("image_rotate.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    //Discover platforms
    cl::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    //Create a context
    cl::context_properties cps[3] = {CL_CONTEXT_PLATFORM,(cl_context_properties)(platforms[0]) (),0};

    cl::Context context(CL_DEVICE_TYPE_ALL,cps);

    cl::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();


    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1, 
            &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem d_ip = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            W*H*sizeof(int), NULL, &ret);
    cl_mem d_op = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            W*H * sizeof(int), NULL, &ret);

    /*cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);

    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);
    */
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, d_ip, CL_TRUE, 0,
            W*H*sizeof(float), ip, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "image_rotate", &ret);

    // Set the arguments of the kernel
    /*ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    */
    // Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Process in groups of 64
   /* ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
   */
    // Read the memory buffer C on the device to the local variable C
    //int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
    /*ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), C, 0, NULL, NULL);
    */
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    
    program_kernel.setArg(0,d_op);
    program_kernel.setArg(1,d_ip);
    program_kernel.setArg(2,W);
    program_kernel.setArg(3,H);
    program_kernel.setArg(4,cos_theta);
    program_kernel.setArg(5,sin_theta);

    cl::NDRange globalws(W,H);
    cl::NDRange localws(16,16);

    ret = clEnqueueNDRangeKernel(program_kernel, kernel, 2, NULL, 
            &globalws, &localws, 0, NULL, NULL);

    ret = clEnqueueReadBuffer(command_queue, d_op, CL_TRUE, 0, 
            W*H * sizeof(float), op, 0, NULL, NULL);
    
    // Display the result to the screen
    for(i = 0; i < LIST_SIZE; i++)
        printf("%d\n",ip[i]);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(d_ip);
    ret = clReleaseMemObject(d_op);
    //ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(ip);
    return 0;
}
