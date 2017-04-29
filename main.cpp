#include <cstdlib>
#include <ventaquil/OpenCL/Device.h>
#include <ventaquil/OpenCL/Platform.h>
#include <ventaquil/OpenCL/Queue.h>
#include <exception>
#include <iostream>

int main(void) {
    try {
        cl_uint platforms_number = ventaquil::OpenCL::Platform::getNumber();

        std::cout << "Detected " << platforms_number << " platform" << (platforms_number != 1 ? "s" : "") << std::endl;

        cl_platform_id *platforms = ventaquil::OpenCL::Platform::getIds();

        for (cl_uint i = 0; i < platforms_number; ++i) {
            ventaquil::OpenCL::Platform platform(platforms[i]);

            char *platform_name = platform.getName();

            cl_uint devices_number = platform.getDevicesNumber();

            std::cout << "  Platform " << (i + 1) << "-th - " << platform_name << " (" << devices_number << " device"
                      << (devices_number != 1 ? "s" : "") << ")" << std::endl;

            cl_device_id *devices = platform.getDevicesIds();

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

        std::cout << std::endl;

        {
            ventaquil::OpenCL::Device device = ventaquil::OpenCL::Device::getBestDevice();

            char *device_name = device.getName();

            std::cout << "Best device: " << device_name << std::endl;

            delete[] device_name;

            {
                ventaquil::OpenCL::Context context = device.createContext(NULL, NULL, NULL);

                {
                    ventaquil::OpenCL::Queue queue(context.getContext(), device.getId(),
                                                   CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE);
                }
            }
        }

        return EXIT_SUCCESS;
    } catch (std::exception exception) {
        std::cerr << exception.what() << std::endl;

        return EXIT_FAILURE;
    }
}
