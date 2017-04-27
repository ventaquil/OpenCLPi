#ifndef OPENCLPI_DEVICE_H
#define OPENCLPI_DEVICE_H

#include <CL/cl.h>
#include "Context.h"

namespace ventaquil {
    namespace OpenCL {
        class Device {
            private:
                cl_device_id id;

            public:
                Device(cl_device_id id);

                static Context createContext(cl_context_properties *properties, cl_uint devices_number,
                                             cl_device_id *devices,
                                             void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *),
                                             void *user_data);

                Context createContext(cl_context_properties *properties,
                                      void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *),
                                      void *user_data);

                cl_device_id getId(void);

                static cl_device_id *
                getIds(cl_platform_id platform_id, cl_device_type type = CL_DEVICE_TYPE_ALL, cl_uint max = 0);

                cl_uint getMaxClockFrequency(void);

                cl_uint getMaxComputeUnits(void);

                char *getName(void);

                static cl_uint getNumber(cl_platform_id platform_id, cl_device_type type = CL_DEVICE_TYPE_ALL);
        };
    }
}

#endif //OPENCLPI_DEVICE_H
