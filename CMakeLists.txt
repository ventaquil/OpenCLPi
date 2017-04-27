cmake_minimum_required(VERSION 3.7)
project(OpenCLPi)

set(SOURCE_FILES main.cpp
    src/ventaquil/OpenCL/Catcher.cpp
    src/ventaquil/OpenCL/Context.cpp
    src/ventaquil/OpenCL/Device.cpp
    src/ventaquil/OpenCL/Kernel.cpp
    src/ventaquil/OpenCL/Platform.cpp
    src/ventaquil/OpenCL/Queue.cpp

    src/ventaquil/OpenCLPi/BBPFormula.cpp
)

find_package(OpenCL REQUIRED)

include_directories(src)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main OpenCL::OpenCL)

configure_file(resrc/bbp-formula.cl resrc/bbp-formula.cl @ONLY)
