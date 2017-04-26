#include "Device.h"

namespace ventaquil {
    namespace OpenCL {
        Device::Device(cl_device_id id) : id(id) {}

        cl_device_id Device::getId(void) {
            return id;
        }

        char *Device::getName(void) {
            size_t length;

            clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &length);

            char *name = new char[length];

            clGetDeviceInfo(id, CL_DEVICE_NAME, length, name, NULL);

            return name;
        }
    }
}
