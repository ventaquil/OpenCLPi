#ifndef OPENCLPI_QUEUE_H
#define OPENCLPI_QUEUE_H

#include <Cl/cl.h>

namespace ventaquil {
    namespace OpenCL {
        class Queue {
            private:
                cl_command_queue queue;

            public:
                Queue(cl_context context, cl_device_id device_id, cl_command_queue_properties properties);

                ~Queue(void);

                cl_command_queue getQueue(void);
        };
    }
}

#endif //OPENCLPI_QUEUE_H
