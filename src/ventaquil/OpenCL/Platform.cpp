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

            {
                cl_int error_code = clGetPlatformIDs(number, platforms, NULL);

                test(error_code, "Get platforms' ids fail");
            }

            return platforms;
        }

        char *Platform::getName(void) {
            size_t length;

            {
                cl_int error_code = clGetPlatformInfo(getId(), CL_PLATFORM_NAME, 0, NULL, &length);

                test(error_code, "Get platform's name size fail");
            }

            char *name = new char[length];

            {
                cl_int error_code = clGetPlatformInfo(getId(), CL_PLATFORM_NAME, length, name, NULL);

                test(error_code, "Get platform's name fail");
            }

            return name;
        }

        cl_uint Platform::getNumber(void) {
            cl_uint number;

            {
                cl_int error_code = clGetPlatformIDs(0, NULL, &number);

                test(error_code, "Get platforms number fail");
            }

            return number;
        }
    }
}
