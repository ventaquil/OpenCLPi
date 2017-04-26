#include "Helper.h"
#include "Platform.h"
#include "Device.h"

namespace ventaquil {
    namespace OpenCL {
        cl_device_id Helper::getBestDevice(cl_device_type type) {
            cl_device_id device_id;
            cl_uint max = 0;
            bool set = false;

            cl_uint platforms_number = getPlatformsNumber();
            cl_platform_id *platforms = getPlatformsIds();

            for (cl_uint i = 0; i < platforms_number; ++i) {
                Platform platform(platforms[i]);

                cl_uint devices_number = platform.getDevicesNumber(type);
                cl_device_id *devices = platform.getDevicesIds(type);

                for (cl_uint j = 0; j < devices_number; ++j) {
                    Device device(devices[j]);

                    // @TODO How?
                    cl_uint value = (device.getMaxComputeUnits() + device.getMaxClockFrequency()) / 2;

                    if (value > max) {
                        max = value;

                        device_id = device.getId();

                        set = true;
                    }
                }

                delete[] devices;
            }

            delete[] platforms;

            if (set) {
                return device_id;
            }

            if (type != CL_DEVICE_TYPE_ALL) {
                return getBestDevice(CL_DEVICE_TYPE_ALL);
            }

            // @TODO exception
        }

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
