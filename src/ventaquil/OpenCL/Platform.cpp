#include "Platform.h"
#include "Helper.h"

namespace ventaquil {
    namespace OpenCL {
        Platform::Platform(cl_platform_id id) : id(id) {}

        cl_device_id* Platform::getDevicesIds(cl_device_type type, cl_uint max) {
            return Helper::getDevicesIds(id, type, max);
        }

        cl_uint Platform::getDevicesNumber(cl_device_type type) {
            return Helper::getDevicesNumber(id, type);
        }

        cl_platform_id Platform::getId(void) {
            return id;
        }

        char *Platform::getName(void) {
            size_t length;

            clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, NULL, &length);

            char *name = new char[length];

            clGetPlatformInfo(id, CL_PLATFORM_NAME, length, name, NULL);

            return name;
        }
    }
}
