#include "Queue.h"

namespace ventaquil {
    namespace OpenCL {
        Queue::Queue(cl_context context, cl_device_id device_id, cl_command_queue_properties properties) {
            cl_int error_code;

            queue = clCreateCommandQueue(context, device_id, properties, &error_code);

            test(error_code, "Create command queue fail");
        }

        Queue::~Queue(void) {
            cl_int error_code = clReleaseCommandQueue(queue);

            test(error_code, "Release command queue fail");
        }

        cl_command_queue Queue::getQueue(void) {
            return queue;
        }
    }
}
