#include "Device.h"
#include "Platform.h"

namespace ventaquil {
    namespace OpenCL {
        Device::Device(cl_device_id id) : id(id) {}

        Context Device::createContext(cl_context_properties *properties, cl_uint devices_number, cl_device_id *devices,
                                      void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *),
                                      void *user_data) {
            return Context(properties, devices_number, devices, callback, user_data);
        }

        Context Device::createContext(cl_context_properties *properties,
                                      void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *),
                                      void *user_data) {
            cl_device_id device_id = getId();

            return createContext(properties, 1, &device_id, callback, user_data);
        }

        cl_device_id Device::getBestDeviceId(cl_device_type type) {
            cl_device_id best_device_id;

            cl_platform_id *platforms = Platform::getIds();

            for (cl_uint i = 0, max = 0, platforms_number = Platform::getNumber(); i < platforms_number; ++i) {
                Platform platform(platforms[i]);

                cl_uint devices_number = platform.getDevicesNumber(type);

                if (devices_number > 0) {
                    cl_device_id *devices = platform.getDevicesIds(type);

                    for (cl_uint j = 0; j < devices_number; ++j) {
                        Device device(devices[j]);

                        cl_uint value = device.getMaxComputeUnits() * device.getMaxClockFrequency();

                        if (value > max) {
                            max = value;

                            best_device_id = device.getId();
                        }
                    }

                    delete[] devices;
                }
            }

            delete[] platforms;

            return best_device_id;
        }

        Device Device::getBestDevice(cl_device_type type) {
            return Device(getBestDeviceId(type));
        }

        cl_device_id Device::getId(void) {
            return id;
        }

        cl_device_id *Device::getIds(cl_platform_id platform_id, cl_device_type type, cl_uint max) {
            cl_uint number = getNumber(platform_id, type);

            number = ((number > max) && (max != 0)) ? max : number;

            cl_device_id *devices = new cl_device_id[number];

            {
                cl_int error_code = clGetDeviceIDs(platform_id, type, number, devices, NULL);

                test(error_code, "Get devices' ids fail");
            }

            return devices;
        }

        cl_uint Device::getMaxClockFrequency(void) {
            cl_uint max_clock_frequency;

            {
                cl_int error_code = clGetDeviceInfo(getId(), CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_frequency),
                                                    &max_clock_frequency, NULL);

                test(error_code, "Get device's max cock frequency fail");
            }

            return max_clock_frequency;
        }

        cl_uint Device::getMaxComputeUnits(void) {
            cl_uint max_compute_units;

            {
                cl_int error_code = clGetDeviceInfo(getId(), CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units),
                                                    &max_compute_units, NULL);

                test(error_code, "Get device's max compute units fail");
            }

            return max_compute_units;
        }

        char *Device::getName(void) {
            size_t length;

            {
                cl_int error_code = clGetDeviceInfo(getId(), CL_DEVICE_NAME, 0, NULL, &length);

                test(error_code, "Get device's name size fail");
            }

            char *name = new char[length];

            {
                cl_int error_code = clGetDeviceInfo(getId(), CL_DEVICE_NAME, length, name, NULL);

                test(error_code, "Get device's name fail");
            }

            return name;
        }

        cl_uint Device::getNumber(cl_platform_id platform_id, cl_device_type type) {
            cl_uint number;

            {
                cl_int error_code = clGetDeviceIDs(platform_id, type, 0, NULL, &number);

                if (error_code != CL_DEVICE_NOT_FOUND) { // If devices are not found then do not throw exception
                    test(error_code, "Get devices number fail");
                } else {
                    number = 0;
                }
            }

            return number;
        }
    }
}
