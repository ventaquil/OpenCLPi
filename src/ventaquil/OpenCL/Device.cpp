#include "Device.h"

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

        cl_device_id Device::getId(void) {
            return id;
        }

        cl_device_id *Device::getIds(cl_platform_id platform_id, cl_device_type type, cl_uint max) {
            cl_uint number = getNumber(platform_id, type);

            number = ((number > max) && (max != 0)) ? max : number;

            cl_device_id *devices = new cl_device_id[number];

            clGetDeviceIDs(platform_id, type, number, devices, NULL);

            return devices;
        }

        cl_uint Device::getMaxClockFrequency(void) {
            cl_uint max_clock_frequency;

            clGetDeviceInfo(getId(), CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_frequency), &max_clock_frequency,
                            NULL);

            return max_clock_frequency;
        }

        cl_uint Device::getMaxComputeUnits(void) {
            cl_uint max_compute_units;

            clGetDeviceInfo(getId(), CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units), &max_compute_units, NULL);

            return max_compute_units;
        }

        char *Device::getName(void) {
            size_t length;

            clGetDeviceInfo(getId(), CL_DEVICE_NAME, 0, NULL, &length);

            char *name = new char[length];

            clGetDeviceInfo(getId(), CL_DEVICE_NAME, length, name, NULL);

            return name;
        }

        cl_uint Device::getNumber(cl_platform_id platform_id, cl_device_type type) {
            cl_uint number;

            clGetDeviceIDs(platform_id, type, 0, NULL, &number);

            return number;
        }
    }
}
