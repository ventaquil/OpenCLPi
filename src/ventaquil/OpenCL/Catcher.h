#ifndef OPENCLPI_CATCHER_H
#define OPENCLPI_CATCHER_H

#include <CL/cl.h>
#include <string>

namespace ventaquil {
    namespace OpenCL {
        class Catcher {
            public:
                static void test(cl_int code, char *message);

                static void test(cl_int code, const char *message);

                static void test(cl_int code, std::string message);
        };
    }
}

#endif //OPENCLPI_CATCHER_H
