#include "Queue.h"

namespace ventaquil {
    namespace OpenCL {
        Queue::Queue(cl_context context, cl_device_id device_id, cl_command_queue_properties properties) {
            queue = clCreateCommandQueue(context, device_id, properties, NULL); // @TODO error!
        }

        Queue::~Queue(void) {
            clReleaseCommandQueue(queue);
        }

        cl_command_queue Queue::getQueue(void) {
            return queue;
        }
    }
}
