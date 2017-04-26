#include <cstdlib>
#include <ventaquil/OpenCL.h>
#include <iostream>

int main(void) {
    cl_uint platforms_number = ventaquil::OpenCL::getPlatformsNumber();

    std::cout << "Detected " << platforms_number << " platform" << (platforms_number != 1 ? "s" : NULL) << std::endl;

    ventaquil::OpenCL::getPlatformsIds();

    return EXIT_SUCCESS;
}
