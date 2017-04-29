#ifndef OPENCLPI_KERNEL_H
#define OPENCLPI_KERNEL_H

#include <CL/cl.h>
#include "Catcher.h"
#include <string>
#include <fstream>

namespace ventaquil {
    namespace OpenCL {
        class Kernel : protected Catcher {
            private:
                cl_kernel kernel;

                cl_program program;

            protected:
                void buildProgram(cl_program program, cl_device_id device_id);

                cl_program createProgram(cl_context context, char *filecontent, size_t filesize, cl_uint count = 1);

                cl_kernel createKernel(cl_program program, char *kernel_name);

            public:
                Kernel(char *filename, char *kernel_name, cl_context context, cl_device_id device_id);

                Kernel(std::string filename, char *kernel_name, cl_context context, cl_device_id device_id);

                ~Kernel(void);

                cl_kernel getKernel(void);

                cl_program getProgram(void);

                Kernel *setArgument(cl_uint index, size_t size, void *value);
        };
    }
}

#endif //OPENCLPI_KERNEL_H
