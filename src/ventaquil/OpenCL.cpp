#include "OpenCL.h"

namespace ventaquil {
    cl_platform_id *OpenCL::getPlatformsIds(cl_uint max) {
        cl_uint number = getPlatformsNumber();

        number = number > max ? max : number;

        cl_platform_id *platforms = new cl_platform_id[number];

        clGetPlatformIDs(number, platforms, NULL);

        return platforms;
    }

    cl_uint OpenCL::getPlatformsNumber(void) {
        cl_uint number;

        clGetPlatformIDs(0, NULL, &number);

        return number;
    }
}
