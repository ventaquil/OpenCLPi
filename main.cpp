#include <cstdlib>
#include <ventaquil/OpenCL/Helper.h>
#include <ventaquil/OpenCL/Platform.h>
#include <iostream>

int main(void) {
    cl_uint platforms_number = ventaquil::OpenCL::Helper::getPlatformsNumber();

    std::cout << "Detected " << platforms_number << " platform" << (platforms_number != 1 ? "s" : "") << std::endl;

    cl_platform_id *platforms = ventaquil::OpenCL::Helper::getPlatformsIds();

    for (cl_uint i = 0; i < platforms_number; ++i) {
        ventaquil::OpenCL::Platform platform(platforms[i]);

        char *name = platform.getName();

        std::cout << " Platform " << (i + 1) << "-th - " << name << std::endl;
        cl_uint devices_number = ventaquil::OpenCL::Helper::getDevicesNumber(platforms[i]);

        std::cout << "  " << devices_number << " device" << (devices_number != 1 ? "s" : "") << std::endl;

        ventaquil::OpenCL::Helper::getDevicesIds(platforms[i]);

        delete [] name;
    }

    return EXIT_SUCCESS;
}
