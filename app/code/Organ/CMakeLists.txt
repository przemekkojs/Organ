cmake_minimum_required(VERSION 3.8)

project("Organ")

add_executable(Organ main.cpp "h/voice.h" "h/section.h" "h/MIDI_controller.h" "h/keyboard.h" "cpp/keyboard.cpp" "cpp/MIDI_controller.cpp" "cpp/section.cpp" "cpp/voice.cpp" "h/organ.h" "cpp/organ.cpp" "cpp/app.cpp" "h/app.h" "h/voice_group.h" "cpp/voice_group.cpp" "cpp/combinations.cpp" "h/combinations.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Organ PROPERTY CXX_STANDARD 20)
endif()

# Biblioteka RtMidi
add_library(rtmidi "lib/RtMidi.cpp" "h/voice.h" "h/section.h" "h/MIDI_controller.h" "h/keyboard.h" "cpp/keyboard.cpp" "cpp/MIDI_controller.cpp" "cpp/section.cpp" "cpp/voice.cpp" "h/organ.h" "cpp/organ.cpp" "cpp/app.cpp" "h/app.h" "h/voice_group.h" "cpp/voice_group.cpp" "cpp/combinations.cpp" "h/combinations.h")

target_include_directories(rtmidi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ❗ NIEZBĘDNE – aktywuje backend WinMM
target_compile_definitions(rtmidi PUBLIC __WINDOWS_MM__)

# Linkowanie Windows Multimedia API
target_link_libraries(rtmidi PUBLIC winmm)

# Łączenie biblioteki z Twoim projektem
target_link_libraries(Organ PRIVATE rtmidi)
