#ifndef OPENCLPI_PLATFORM_H
#define OPENCLPI_PLATFORM_H

#include <CL/cl.h>

namespace ventaquil {
    namespace OpenCL {
        class Platform {
            protected:
                cl_platform_id id;

            public:
                Platform(cl_platform_id id);

                cl_platform_id getId(void);

                char *getName(void);
        };
    }
}

#endif //OPENCLPI_PLATFORM_H
