# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)






set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


project(blink C CXX ASM)
pico_sdk_init()

message("running makefsdata python script")

execute_process(COMMAND 
    py makefsdata.py 
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

# Initialise the Raspberry Pi Pico SDK

#pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(blink
    main.c
    led.c
    infraRed.c
    servo.c
    flameSensor.c
    buzzer.c
    
    )

# pull in common dependencies

pico_enable_stdio_uart(blink 0)
pico_enable_stdio_usb(blink 1)

target_link_libraries(blink pico_stdlib hardware_adc hardware_pwm hardware_timer pico_cyw43_arch_lwip_threadsafe_background pico_lwip_http) 

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

target_include_directories(blink PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)

# add url via pico_set_program_url
