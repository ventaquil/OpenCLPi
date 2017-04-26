#include <cstdlib>
#include <ventaquil/OpenCL/Device.h>
#include <ventaquil/OpenCL/Helper.h>
#include <ventaquil/OpenCL/Platform.h>
#include <iostream>

int main(void) {
    cl_uint platforms_number = ventaquil::OpenCL::Helper::getPlatformsNumber();

    std::cout << "Detected " << platforms_number << " platform" << (platforms_number != 1 ? "s" : "") << std::endl;

    cl_platform_id *platforms = ventaquil::OpenCL::Helper::getPlatformsIds();

    for (cl_uint i = 0; i < platforms_number; ++i) {
        ventaquil::OpenCL::Platform platform(platforms[i]);

        char *platform_name = platform.getName();

        cl_uint devices_number = ventaquil::OpenCL::Helper::getDevicesNumber(platforms[i]);

        std::cout << "  Platform " << (i + 1) << "-th - " << platform_name << " (" << devices_number << " device"
                  << (devices_number != 1 ? "s" : "") << ")" << std::endl;

        cl_device_id *devices = ventaquil::OpenCL::Helper::getDevicesIds(platforms[i]);

        for (cl_uint j = 0; j < devices_number; ++j) {
            ventaquil::OpenCL::Device device(devices[j]);

            char *device_name = device.getName();

            std::cout << "    Device " << (j + 1) << "-th - " << device_name << std::endl;

            delete[] device_name;
        }

        delete[] devices;

        delete[] platform_name;
    }

    delete[] platforms;

    return EXIT_SUCCESS;
}
