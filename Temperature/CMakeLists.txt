cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(DTH C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(DTH
	DTH.c
	)

pico_enable_stdio_usb(DTH 1)
pico_enable_stdio_uart(DTH 0)

#create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(DTH)

#Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(DTH pico_stdlib)
