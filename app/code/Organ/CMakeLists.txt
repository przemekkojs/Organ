cmake_minimum_required(VERSION 3.14)
project(OrganProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Python_EXECUTABLE "C:\\Users\\przem\\AppData\\Local\\Programs\\Python\\Python312\\python.exe")

add_subdirectory(lib/pybind11)

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

    h/keyboard.h
    h/MIDI_controller.h
    h/section.h
    h/voice.h
    h/organ.h
    h/app.h
    h/voice_group.h
    h/combinations.h
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
)

target_link_libraries(organ PRIVATE rtmidi)

message("Python module output dir: ${CMAKE_CURRENT_BINARY_DIR}")

set_target_properties(organ PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
)
