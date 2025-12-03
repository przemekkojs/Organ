cmake_minimum_required(VERSION 3.8)

project("Organ")

add_executable(Organ main.cpp "h/voice.h" "h/section.h" "h/MIDI_controller.h" "h/keyboard.h" "cpp/keyboard.cpp" "cpp/MIDI_controller.cpp" "cpp/section.cpp" "cpp/voice.cpp" "h/organ.h" "cpp/organ.cpp" "cpp/app.cpp" "h/app.h" "h/voice_group.h" "cpp/voice_group.cpp" "cpp/combinations.cpp" "h/combinations.h" "bindings/bind_app.cpp" "bindings/bind_combinations.cpp" "bindings/bind_keyboard.cpp" "bindings/bind_MIDI_controller.cpp" "bindings/bind_organ.cpp" "bindings/bind_section.cpp" "bindings/bind_voice.cpp" "bindings/bind_voice_group.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Organ PROPERTY CXX_STANDARD 20)
endif()

add_library(rtmidi "lib/RtMidi.cpp" "h/voice.h" "h/section.h" "h/MIDI_controller.h" "h/keyboard.h" "cpp/keyboard.cpp" "cpp/MIDI_controller.cpp" "cpp/section.cpp" "cpp/voice.cpp" "h/organ.h" "cpp/organ.cpp" "cpp/app.cpp" "h/app.h" "h/voice_group.h" "cpp/voice_group.cpp" "cpp/combinations.cpp" "h/combinations.h" "bindings/bind_app.cpp" "bindings/bind_combinations.cpp" "bindings/bind_keyboard.cpp" "bindings/bind_MIDI_controller.cpp" "bindings/bind_organ.cpp" "bindings/bind_section.cpp" "bindings/bind_voice.cpp" "bindings/bind_voice_group.cpp")
add_subdirectory(extern/pybind11)

target_include_directories(rtmidi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(rtmidi PUBLIC __WINDOWS_MM__)
target_link_libraries(rtmidi PUBLIC winmm)
target_link_libraries(Organ PRIVATE rtmidi)
