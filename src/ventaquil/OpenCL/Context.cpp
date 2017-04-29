#include "Context.h"

namespace ventaquil {
    namespace OpenCL {
        Context::Context(cl_context_properties *properties, cl_uint devices_number, cl_device_id *devices,
                         void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *), void *user_data) {
            cl_int error_code;

            context = clCreateContext(properties, devices_number, devices, callback, user_data, &error_code);

            test(error_code, "Create context fail");
        }

        Context::~Context(void) {
            cl_int error_code = clReleaseContext(context);

            test(error_code, "Release context fail");
        }

        cl_context Context::getContext(void) {
            return context;
        }
    }
}
