#include "BBPFormula.h"
#include <string>
#include <ventaquil/OpenCL/Device.h>
#include <ventaquil/OpenCL/Kernel.h>
#include <ventaquil/OpenCL/Queue.h>

float BBPFormula(cl_uint s, cl_uint b, cl_uint m, cl_int *A, cl_uint k) {
    float value = 0.0;

    ventaquil::OpenCL::Device device = ventaquil::OpenCL::Device::getBestDevice();

    ventaquil::OpenCL::Context context = device.createContext(NULL, NULL, NULL);

    ventaquil::OpenCL::Queue queue(context.getContext(), device.getId(), 0);

    {
        cl_mem memA, memR;

        {
            cl_int error_code;

            memA = clCreateBuffer(context.getContext(), CL_MEM_READ_ONLY, m * sizeof(cl_int), NULL, &error_code);

            ventaquil::OpenCL::Catcher::test(error_code, "Create buffer for A fail");
        }

        {
            cl_int error_code;

            memR = clCreateBuffer(context.getContext(), CL_MEM_WRITE_ONLY, k * sizeof(float), NULL, &error_code);

            ventaquil::OpenCL::Catcher::test(error_code, "Create buffer for R fail");
        }

        float *R = new float[k];

        for (cl_uint i = 0; i < k; ++i) {
            R[i] = 0.0;
        }

        {
            cl_int error_code = clEnqueueWriteBuffer(queue.getQueue(), memA, CL_TRUE, 0, m * sizeof(cl_int), A, 0, NULL,
                                                     NULL);

            ventaquil::OpenCL::Catcher::test(error_code, "Write buffer for A fail");
        }

        {
            size_t globalWorkSize = k;

            size_t localWorkSize = globalWorkSize;

            char filename[] = "resrc/bbpformula/first_step.cl", kernel_name[] = "bbpformula_first_step";

            ventaquil::OpenCL::Kernel kernel(filename, kernel_name, context.getContext(),
                                             device.getId());

            kernel.setArgument(0, sizeof(s), &s)->setArgument(1, sizeof(m), &m)
                    ->setArgument(2, sizeof(memA), &memA)->setArgument(3, sizeof(memR), &memR);

            {
                cl_int error_code = clEnqueueNDRangeKernel(queue.getQueue(), kernel.getKernel(), 1, NULL,
                                                           &globalWorkSize, &localWorkSize, 0, NULL, NULL);

                ventaquil::OpenCL::Catcher::test(error_code, "Run kernel fail");
            }

            clFinish(queue.getQueue());

            {
                cl_int error_code = clEnqueueReadBuffer(queue.getQueue(), memR, CL_TRUE, 0, k * sizeof(float), R, 0,
                                                        NULL, NULL);

                ventaquil::OpenCL::Catcher::test(error_code, "Read buffer for R fail");
            }
        }

        clReleaseMemObject(memA);

        clReleaseMemObject(memR);

        {
            cl_int error_code;

            memR = clCreateBuffer(context.getContext(), CL_MEM_READ_WRITE, k * sizeof(float), NULL, &error_code);

            ventaquil::OpenCL::Catcher::test(error_code, "Create buffer for R fail");
        }

        {
            cl_int error_code = clEnqueueWriteBuffer(queue.getQueue(), memR, CL_TRUE, 0, k * sizeof(float), R, 0, NULL,
                                                     NULL);

            ventaquil::OpenCL::Catcher::test(error_code, "Write buffer for R fail");
        }

        {
            size_t globalWorkSize = k;

            size_t localWorkSize = globalWorkSize;

            char filename[] = "resrc/bbpformula/last_step.cl", kernel_name[] = "bbpformula_last_step";

            ventaquil::OpenCL::Kernel kernel(filename, kernel_name, context.getContext(),
                                             device.getId());

            kernel.setArgument(0, sizeof(b), &b)->setArgument(1, sizeof(memR), &memR);

            {
                cl_int error_code = clEnqueueNDRangeKernel(queue.getQueue(), kernel.getKernel(), 1, NULL,
                                                           &globalWorkSize, &localWorkSize, 0, NULL, NULL);

                ventaquil::OpenCL::Catcher::test(error_code, "Run kernel fail");
            }

            clFinish(queue.getQueue());

            {
                cl_int error_code = clEnqueueReadBuffer(queue.getQueue(), memR, CL_TRUE, 0, k * sizeof(float), R, 0,
                                                        NULL, NULL);

                ventaquil::OpenCL::Catcher::test(error_code, "Read buffer for R fail");
            }
        }

        clReleaseMemObject(memR);

        for (cl_uint i = 0; i < k; ++i) {
            value += R[i];
        }

        delete[] R;
    }

    return value;
}
