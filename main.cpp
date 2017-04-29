#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ventaquil/OpenCLPi/BBPFormula.h>

int main(void) {
    try {
        cl_uint k;

        std::cout << "k: ";
        std::cin >> k;

        ++k;

        // Constants for Pi
        const cl_uint s = 1, b = 16, m = 8;
        const cl_int A[8] = {4, 0, 0, -2, -1, -1, 0, 0};

        double pi = BBPFormula(s, b, m, (cl_int *) A, k);

        std::cout << "Pi " << std::setprecision(k) << pi << std::endl;

        return EXIT_SUCCESS;
    } catch (std::exception exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}
