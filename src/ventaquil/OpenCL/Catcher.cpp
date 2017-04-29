#include "Catcher.h"
#include <exception>
#include <iostream>

namespace ventaquil {
    namespace OpenCL {
        void Catcher::test(cl_int code, char *message) {
            test(code, std::string(message));
        }

        void Catcher::test(cl_int code, const char *message) {
            test(code, (char *) message);
        }

        void Catcher::test(cl_int code, std::string message) {
            if (code != CL_SUCCESS) {
                std::cerr << message << " [code " << code << "]" << std::endl;

                throw new std::exception;
            }
        }
    }
}
