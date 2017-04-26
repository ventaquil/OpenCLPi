#ifndef OPENCLPI_OPENCL_H
#define OPENCLPI_OPENCL_H

#include <CL/cl.h>

namespace ventaquil {
    class OpenCL {
        public:
            static cl_platform_id *getPlatformsIds(cl_uint max = 0);

            static cl_uint getPlatformsNumber(void);
    };
}

#endif //OPENCLPI_OPENCL_H
