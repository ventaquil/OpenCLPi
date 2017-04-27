#ifndef OPENCLPI_PLATFORM_H
#define OPENCLPI_PLATFORM_H

#include <CL/cl.h>

namespace ventaquil {
    namespace OpenCL {
        class Platform {
            private:
                cl_platform_id id;

            public:
                Platform(cl_platform_id id);

                cl_device_id *getDevicesIds(cl_device_type type = CL_DEVICE_TYPE_ALL, cl_uint max = 0);

                cl_uint getDevicesNumber(cl_device_type type = CL_DEVICE_TYPE_ALL);

                cl_platform_id getId(void);

                static cl_platform_id *getIds(cl_uint max = 0);

                char *getName(void);

                static cl_uint getNumber(void);
        };
    }
}

#endif //OPENCLPI_PLATFORM_H
