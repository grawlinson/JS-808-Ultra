cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND UNIX AND NOT APPLE AND NOT SKIP_PIE_CHANGE)
  message(STATUS "Setting -no-pie on EXE flags; use SKIP_PIE_CHANGE=TRUE to avoid" )
  set(CMAKE_EXE_LINKER_FLAGS "-no-pie")
endif()

project(JS-808-Ultra VERSION 1.0.1 LANGUAGES CXX)

add_subdirectory(libs/JUCE)
add_subdirectory(libs/clap-juce-extensions)
add_subdirectory(libs/chowdsp_utils)
add_subdirectory(libs/chunkware-simple-dynamics)

juce_add_plugin(${PROJECT_NAME}
  COMPANY_NAME "JamesStubbsEng"
  COMPANY_WEBSITE "https://github.com/JamesStubbsEng/TS-808-Ultra"
  BUNDLE_ID "com.JamesStubbsEng.TS-808-Ultra"
  DESCRIPTION "Digital model of the Ibanez Tube Screamer 808"
  PLUGIN_MANUFACTURER_CODE JSTE
  PLUGIN_CODE T808
  FORMATS Standalone VST3 AU AUv3 LV2
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE
  VST3_CATEGORIES Fx
  AU_MAIN_TYPE kAudioUnitType_Effect
)

clap_juce_extensions_plugin(TARGET ${PROJECT_NAME}
  CLAP_ID "com.JamesStubbsEng.TS-808-Ultra"
  CLAP_FEATURES "audio-effect"
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    src/dsp/ClippingStage.cpp
    src/dsp/ClippingStage.h
    src/dsp/ClipWDFa.h
    src/dsp/ClipWDFb.h
    src/dsp/ClipWDFc.h
    src/dsp/DryComp.cpp
    src/dsp/DryComp.h
    src/dsp/DryLPF.cpp
    src/dsp/DryLPF.h
    src/dsp/ToneStage.cpp
    src/dsp/ToneStage.h
    src/PluginEditor.cpp
    src/PluginEditor.h
    src/PluginProcessor.cpp
    src/PluginProcessor.h
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ChunkwareSimpleDynamics
    juce_audio_basics
    juce_audio_devices
    juce_audio_formats
    juce_audio_plugin_client
    juce_audio_processors
    juce_audio_utils
    juce_core
    juce_data_structures
    juce_events
    juce_graphics
    juce_gui_basics
    juce_gui_extra
    juce_dsp
    chowdsp_dsp
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0
  JUCE_DISPLAY_SPLASH_SCREEN=0
  JUCE_REPORT_APP_USAGE=0
)
