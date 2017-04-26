#include "Helper.h"

namespace ventaquil {
    namespace OpenCL {
        cl_device_id *Helper::getDevicesIds(cl_platform_id platform_id, cl_device_type type, cl_uint max) {
            cl_uint number = getDevicesNumber(platform_id, type);

            number = ((number > max) && (max != 0)) ? max : number;

            cl_device_id *devices = new cl_device_id[number];

            clGetDeviceIDs(platform_id, type, number, devices, NULL);

            return devices;
        }

        cl_uint Helper::getDevicesNumber(cl_platform_id platform_id, cl_device_type type) {
            cl_uint number;

            clGetDeviceIDs(platform_id, type, 0, NULL, &number);

            return number;
        }

        cl_platform_id *Helper::getPlatformsIds(cl_uint max) {
            cl_uint number = getPlatformsNumber();

            number = ((number > max) && (max != 0)) ? max : number;

            cl_platform_id *platforms = new cl_platform_id[number];

            clGetPlatformIDs(number, platforms, NULL);

            return platforms;
        }

        cl_uint Helper::getPlatformsNumber(void) {
            cl_uint number;

            clGetPlatformIDs(0, NULL, &number);

            return number;
        }
    }
}
