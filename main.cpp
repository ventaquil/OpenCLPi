#include <cstdlib>
#include <iostream>
#include <ventaquil/OpenCLPi/BBPFormula.h>

int main(void) {
    try {
        BBPFormula();

        return EXIT_SUCCESS;
    } catch (std::exception exception) {
        std::cerr << exception.what() << std::endl;

        return EXIT_FAILURE;
    }
}
