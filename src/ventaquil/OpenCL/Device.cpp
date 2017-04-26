#include "Device.h"

namespace ventaquil {
    namespace OpenCL {
        Device::Device(cl_device_id id) : id(id) {}

        cl_device_id Device::getId(void) {
            return id;
        }

        cl_uint Device::getMaxClockFrequency(void) {
            cl_uint max_clock_frequency;

            clGetDeviceInfo(getId(), CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_frequency), &max_clock_frequency, NULL);

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
    }
}
