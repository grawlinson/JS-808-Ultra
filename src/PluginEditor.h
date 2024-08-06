/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_data_structures/juce_data_structures.h>

#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TS808UltraAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    TS808UltraAudioProcessorEditor (TS808UltraAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~TS808UltraAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TS808UltraAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider inputGainSlider;
    juce::Slider driveSlider;
    juce::Slider toneSlider;
    juce::Slider mixSlider;
    juce::Slider filterSlider;
    juce::Slider drySquashSlider;
    juce::Slider outputGainSlider;

    juce::Label inputGainLabel;
    juce::Label driveLabel;
    juce::Label toneLabel;
    juce::Label mixLabel;
    juce::Label filterLabel;
    juce::Label drySquashLabel;
    juce::Label outputGainLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySquashSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TS808UltraAudioProcessorEditor)
};
