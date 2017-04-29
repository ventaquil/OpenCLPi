#include "Kernel.h"
#include <sstream>

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
            {
                cl_int error_code = clReleaseProgram(program);

                test(error_code, "Release program fail");
            }

            {
                cl_int error_code = clReleaseKernel(kernel);

                test(error_code, "Release kernel fail");
            }
        }

        void Kernel::buildProgram(cl_program program, cl_device_id device_id) {
            cl_int error_code = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

            test(error_code, "Build program fail");
        }

        cl_kernel Kernel::createKernel(cl_program program, char *kernel_name) {
            cl_int error_code;

            cl_kernel kernel = clCreateKernel(program, kernel_name, &error_code);

            test(error_code, "Create kernel fail");

            return kernel;
        }

        cl_program Kernel::createProgram(cl_context context, char *filecontent, size_t filesize, cl_uint count) {
            cl_int error_code;

            cl_program program = clCreateProgramWithSource(context, count, (const char **) &filecontent,
                                                           (const size_t *) &filesize, &error_code);

            test(error_code, "Create program with source fail");

            return program;
        }

        cl_kernel Kernel::getKernel(void) {
            return kernel;
        }

        cl_program Kernel::getProgram(void) {
            return program;
        }

        Kernel *Kernel::setArgument(cl_uint index, size_t size, void *value) {
            cl_int error_code = clSetKernelArg(getKernel(), index, size, value);

            std::stringstream stringstream;

            stringstream << "Set kernel argument " << index << " fail";

            test(error_code, stringstream.str());

            return this;
        }
    }
}
