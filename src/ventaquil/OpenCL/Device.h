#ifndef OPENCLPI_DEVICE_H
#define OPENCLPI_DEVICE_H

#include <CL/cl.h>

namespace ventaquil {
    namespace OpenCL {
        class Device {
            protected:
                cl_device_id id;

            public:
                Device(cl_device_id id);

                cl_device_id getId(void);

                char *getName(void);
        };
    }
}

#endif //OPENCLPI_DEVICE_H
