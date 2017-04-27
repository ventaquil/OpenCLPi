#include "Kernel.h"

namespace ventaquil {
    namespace OpenCL {
        Kernel::Kernel(char *filename, char *kernel_name, cl_context context, cl_device_id device_id) {
            std::ifstream filestream(filename, std::ios::in | std::ios::binary);

            if (!filestream) {
                // @TODO exception
            }

            std::string content((std::istreambuf_iterator<char>(filestream)), std::istreambuf_iterator<char>());

            size_t filesize = content.size() + 1;

            char *filecontent = new char[filesize];
            copy(content.begin(), content.end(), filecontent);
            filecontent[filesize - 1] = '\0'; // End of string

            program = createProgram(context, filecontent, filesize);

            buildProgram(program, device_id);

            kernel = createKernel(program, kernel_name);

            delete[] filecontent;
        }

        Kernel::Kernel(std::string filename, char *kernel_name, cl_context context, cl_device_id device_id) : Kernel(
                (char *) filename.c_str(), kernel_name, context, device_id) {}

        Kernel::~Kernel(void) {
            clReleaseProgram(program);
            clReleaseKernel(kernel);
        }

        void Kernel::buildProgram(cl_program program, cl_device_id device_id) {
            clBuildProgram(program, 1, &device_id, NULL, NULL, NULL); // @TODO err code
        }

        cl_kernel Kernel::createKernel(cl_program program, char *kernel_name) {
            cl_kernel kernel = clCreateKernel(program, kernel_name, NULL); // @TODO err code

            return kernel;
        }

        cl_program Kernel::createProgram(cl_context context, char *filecontent, size_t filesize, cl_uint count) {
            cl_program program = clCreateProgramWithSource(context, count, (const char **) &filecontent,
                                                           (const size_t *) &filesize, NULL); // @TODO err code

            return program;
        }

        cl_kernel Kernel::getKernel(void) {
            return kernel;
        }

        cl_program Kernel::getProgram(void) {
            return program;
        }

        Kernel *Kernel::setArgument(cl_uint index, size_t size, void *value) {
            clSetKernelArg(getKernel(), index, size, value); // @TODO err code

            return this;
        }
    }
}
