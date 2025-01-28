# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

<<<<<<< HEAD
project(tarefaTecladoLeds C CXX ASM)
=======
project(main_led C CXX ASM)
>>>>>>> Tarefa3Moises

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

<<<<<<< HEAD
set(SOURCE_EXE tarefaTecladoLeds.c animacao_0.c animacaoBrasil.c)

# Add executable. Default name is the project name, version 0.1
add_executable(tarefaTecladoLeds ${SOURCE_EXE})

pico_set_program_name(tarefaTecladoLeds "tarefaTecladoLeds")
pico_set_program_version(tarefaTecladoLeds "0.1")

# Generate PIO header
pico_generate_pio_header(tarefaTecladoLeds ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(tarefaTecladoLeds 0)
pico_enable_stdio_usb(tarefaTecladoLeds 1)

# Add the standard library to the build
target_link_libraries(tarefaTecladoLeds
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(tarefaTecladoLeds PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(tarefaTecladoLeds
        hardware_pio
        hardware_timer
        hardware_clocks
        pico_cyw43_arch_none
        )

pico_add_extra_outputs(tarefaTecladoLeds)
=======
# Add executable. Default name is the project name, version 0.1

add_executable(main_led main_led.c love_leds_funcao_moises.c)

pico_set_program_name(main_led "main_led")
pico_set_program_version(main_led "0.1")

# Generate PIO header
pico_generate_pio_header(main_led ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(main_led 0)
pico_enable_stdio_usb(main_led 0)

# Add the standard library to the build
target_link_libraries(main_led
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(main_led PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(main_led 
    hardware_pio
    hardware_clocks
    hardware_pwm
    pico_multicore
        )

pico_add_extra_outputs(main_led)
>>>>>>> Tarefa3Moises

