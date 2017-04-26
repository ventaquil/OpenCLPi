#include <cstdlib>
#include <ventaquil/OpenCL.h>
#include <iostream>

int main(void) {
    cl_uint platforms_number = ventaquil::OpenCL::getPlatformsNumber();

    std::cout << "Detected " << platforms_number << " platform" << (platforms_number != 1 ? "s" : "") << std::endl;

    cl_platform_id *platforms = ventaquil::OpenCL::getPlatformsIds();

    for (cl_uint i = 0; i < platforms_number; ++i) {
        std::cout << " Platform " << (i + 1) << "-th" << std::endl;
        cl_uint devices_number = ventaquil::OpenCL::getDevicesNumber(platforms[i]);

        std::cout << "  " << devices_number << " device" << (devices_number != 1 ? "s" : "") << std::endl;

        ventaquil::OpenCL::getDevicesIds(platforms[i]);
    }

    return EXIT_SUCCESS;
}
