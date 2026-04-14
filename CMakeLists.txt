# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location (note this can come from
# environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension
# to work ==
if(WIN32)
  set(USERHOME $ENV{USERPROFILE})
else()
  set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
  include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD
    pico
    CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(set_servos C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(set_servos set_servos.cpp HiwonderServo.cpp i2c_helpers.cpp)

pico_set_program_name(set_servos "set_servos")
pico_set_program_version(set_servos "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(set_servos 1)
pico_enable_stdio_usb(set_servos 1)

# Add the standard library to the build
target_link_libraries(set_servos pico_stdlib)

# Add the standard include files to the build
target_include_directories(set_servos PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(set_servos hardware_timer hardware_clocks)

pico_add_extra_outputs(set_servos)

# get data servo
add_executable(get_data_servo get_data_servo.cpp HiwonderServo.cpp
                              i2c_helpers.cpp)

pico_set_program_name(get_data_servo "get_data_servo")
pico_set_program_version(get_data_servo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(get_data_servo 1)
pico_enable_stdio_usb(get_data_servo 1)

# Add the standard library to the build
target_link_libraries(get_data_servo pico_stdlib)

# Add the standard include files to the build
target_include_directories(get_data_servo PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(get_data_servo hardware_timer hardware_clocks)

pico_add_extra_outputs(get_data_servo)

# set all servos
add_executable(set_all_servos set_all_servos.cpp HiwonderServo.cpp
                              i2c_helpers.cpp)

pico_set_program_name(set_all_servos "set_all_servos")
pico_set_program_version(set_all_servos "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(set_all_servos 1)
pico_enable_stdio_usb(set_all_servos 1)

# Add the standard library to the build
target_link_libraries(set_all_servos pico_stdlib)

# Add the standard include files to the build
target_include_directories(set_all_servos PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(set_all_servos hardware_timer hardware_clocks)

pico_add_extra_outputs(set_all_servos)
