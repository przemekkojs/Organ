cmake_minimum_required(VERSION 3.14)
project(OrganProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PYBIND11_PYTHON_VERSION 3.12)
set(Python3_ROOT_DIR "C:/Users/przem/AppData/Local/Programs/Python/Python312")
set(Python3_EXECUTABLE "C:/Users/przem/AppData/Local/Programs/Python/Python312/python.exe")
find_package(Python3 EXACT 3.12 REQUIRED COMPONENTS Interpreter Development)

message("Python includes: ${Python3_INCLUDE_DIRS}")
message("Python libs:     ${Python3_LIBRARIES}")
message("Python exe:      ${Python3_EXECUTABLE}")

add_subdirectory(lib/pybind11)
find_package(pybind11 CONFIG REQUIRED)

add_library(rtmidi
    lib/RtMidi.cpp

    cpp/keyboard.cpp
    cpp/MIDI_controller.cpp
    cpp/section.cpp
    cpp/voice.cpp
    cpp/organ.cpp
    cpp/app.cpp
    cpp/voice_group.cpp
    cpp/combinations.cpp
    cpp/piston_system.cpp
)

target_include_directories(rtmidi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(rtmidi PUBLIC __WINDOWS_MM__)
target_link_libraries(rtmidi PUBLIC winmm)

pybind11_add_module(organ
    bindings/bindings.cpp
    bindings/bind_app.cpp
    bindings/bind_combinations.cpp
    bindings/bind_keyboard.cpp
    bindings/bind_MIDI_controller.cpp
    bindings/bind_organ.cpp
    bindings/bind_section.cpp
    bindings/bind_voice.cpp
    bindings/bind_voice_group.cpp
    bindings/bind_piston_system.cpp
    bindings/bind_piston.cpp
)

target_link_libraries(organ PRIVATE rtmidi Python3::Python)

message("Python module output dir: ${CMAKE_CURRENT_BINARY_DIR}")

set_target_properties(organ PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
)

add_custom_command(TARGET organ POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env
        PYTHONPATH=${CMAKE_SOURCE_DIR}/python
        ${Python3_EXECUTABLE} -m pybind11_stubgen organ
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python
)