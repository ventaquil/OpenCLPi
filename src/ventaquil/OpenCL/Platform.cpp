#include "Platform.h"
#include "Device.h"

namespace ventaquil {
    namespace OpenCL {
        Platform::Platform(cl_platform_id id) : id(id) {}

        cl_device_id* Platform::getDevicesIds(cl_device_type type, cl_uint max) {
            return Device::getIds(getId(), type, max);
        }

        cl_uint Platform::getDevicesNumber(cl_device_type type) {
            return Device::getNumber(getId(), type);
        }

        cl_platform_id Platform::getId(void) {
            return id;
        }

        cl_platform_id *Platform::getIds(cl_uint max) {
            cl_uint number = getNumber();

            number = ((number > max) && (max != 0)) ? max : number;

            cl_platform_id *platforms = new cl_platform_id[number];

            clGetPlatformIDs(number, platforms, NULL);

            return platforms;
        }

        char *Platform::getName(void) {
            size_t length;

            clGetPlatformInfo(getId(), CL_PLATFORM_NAME, 0, NULL, &length);

            char *name = new char[length];

            clGetPlatformInfo(getId(), CL_PLATFORM_NAME, length, name, NULL);

            return name;
        }

        cl_uint Platform::getNumber(void) {
            cl_uint number;

            clGetPlatformIDs(0, NULL, &number);

            return number;
        }
    }
}
