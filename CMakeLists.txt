cmake_minimum_required(VERSION 3.7)
project(OpenCLPi)

set(SOURCE_FILES main.cpp
    src/ventaquil/OpenCL/Device.cpp
    src/ventaquil/OpenCL/Helper.cpp
    src/ventaquil/OpenCL/Platform.cpp
)

find_package(OpenCL REQUIRED)

include_directories(src)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main OpenCL::OpenCL)
