#ifndef OPENCLPI_CONTEXT_H
#define OPENCLPI_CONTEXT_H

#include <CL/cl.h>
#include "Catcher.h"

namespace ventaquil {
    namespace OpenCL {
        class Context : protected Catcher {
            private:
                cl_context context;

            public:
                Context(cl_context_properties *properties, cl_uint devices_number, cl_device_id *devices,
                        void (CL_CALLBACK *callback)(const char *, const void *, size_t, void *), void *user_data);

                ~Context(void);

                cl_context getContext(void);
        };
    }
}

#endif //OPENCLPI_CONTEXT_H
