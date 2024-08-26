cmake_minimum_required(VERSION 3.22)

# split up cmake into easier-to-parse snippets
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# set some sane CMake specific defaults
include(defaults)
# set some platform specific hacks/fixes (Linux/macOS/Windows)
include(platform-specific)

# JUCE & dependencies
add_subdirectory(libs/JUCE)
add_subdirectory(libs/clap-juce-extensions)
add_subdirectory(libs/chowdsp_utils)
add_subdirectory(libs/chowdsp_wdf)
add_subdirectory(libs/chunkware-simple-dynamics)

# metadata
set(COMPANY_NAME "grawlinson")
set(PROJECT_NAME "JS-808-Ultra")
set(PLUGIN_ID "com.${COMPANY_NAME}.${PROJECT_NAME}")
project(${PROJECT_NAME}
  VERSION 1.0.1
  LANGUAGES CXX
)

# setup JUCE
juce_add_plugin(${PROJECT_NAME}
  COMPANY_NAME ${COMPANY_NAME}
  COMPANY_WEBSITE "https://github.com/JamesStubbsEng/TS-808-Ultra"
  BUNDLE_ID ${PLUGIN_ID}
  DESCRIPTION "Digital model of the Ibanez Tube Screamer 808"
  PLUGIN_MANUFACTURER_CODE GRAW
  PLUGIN_CODE J808
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

# setup CLAP plugin
clap_juce_extensions_plugin(TARGET ${PROJECT_NAME}
  CLAP_ID ${PLUGIN_ID}
  CLAP_FEATURES "audio-effect"
)

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
    chowdsp::chowdsp_dsp_utils
    chowdsp_wdf
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
  PUBLIC
    juce::juce_recommended_warning_flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0
)
