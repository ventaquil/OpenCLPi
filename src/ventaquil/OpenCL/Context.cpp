#include "Context.h"

namespace ventaquil {
    namespace OpenCL {
        Context::Context(cl_context_properties *properties, cl_uint devices_number, cl_device_id *devices,
                         void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *), void *user_data) {
            context = clCreateContext(properties, devices_number, devices, callback, user_data, NULL); // @TODO err code
        }

        Context::~Context(void) {
            clReleaseContext(context);
        }

        cl_context Context::getContext(void) {
            return context;
        }
    }
}
