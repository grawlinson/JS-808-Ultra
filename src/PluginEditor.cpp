/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TS808UltraAudioProcessorEditor::TS808UltraAudioProcessorEditor (TS808UltraAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : juce::AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    driveSlider.setSliderStyle(juce::Slider::Rotary);
    driveSlider.setScrollWheelEnabled(false);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveLabel.setText("Drive", juce::NotificationType::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, false);
    addAndMakeVisible(driveSlider);
    driveSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "drive", driveSlider));

    toneSlider.setSliderStyle(juce::Slider::Rotary);
    toneSlider.setScrollWheelEnabled(false);
    toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    toneSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    toneLabel.setText("Tone", juce::NotificationType::dontSendNotification);
    toneLabel.attachToComponent(&toneSlider, false);
    addAndMakeVisible(toneSlider);
    toneSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "tone", toneSlider));

    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setScrollWheelEnabled(false);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(mixSlider);
    mixSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mix", mixSlider));

    filterSlider.setSliderStyle(juce::Slider::Rotary);
    filterSlider.setScrollWheelEnabled(false);
    filterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    filterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterLabel.setText("Direct Filter", juce::NotificationType::dontSendNotification);
    filterLabel.attachToComponent(&filterSlider, false);
    addAndMakeVisible(filterSlider);
    filterSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filter", filterSlider));

    drySquashSlider.setSliderStyle(juce::Slider::Rotary);
    drySquashSlider.setScrollWheelEnabled(false);
    drySquashSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    drySquashSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    drySquashLabel.setText("Direct Squash", juce::NotificationType::dontSendNotification);
    drySquashLabel.attachToComponent(&drySquashSlider, false);
    addAndMakeVisible(drySquashSlider);
    drySquashSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "drySquash", drySquashSlider));

    outputGainSlider.setSliderStyle(juce::Slider::Rotary);
    outputGainSlider.setScrollWheelEnabled(false);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    outputGainLabel.setText("Output Gain", juce::NotificationType::dontSendNotification);
    outputGainLabel.attachToComponent(&outputGainSlider, false);
    addAndMakeVisible(outputGainSlider);
    outputGainSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "outputGain", outputGainSlider));

    inputGainSlider.setSliderStyle(juce::Slider::Rotary);
    inputGainSlider.setScrollWheelEnabled(false);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    inputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    inputGainLabel.setText("Input Gain", juce::NotificationType::dontSendNotification);
    inputGainLabel.attachToComponent(&inputGainSlider, false);
    addAndMakeVisible(inputGainSlider);
    inputGainSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "inputGain", inputGainSlider));

    setSize (600, 450);
}

TS808UltraAudioProcessorEditor::~TS808UltraAudioProcessorEditor()
{
}

//==============================================================================
void TS808UltraAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void TS808UltraAudioProcessorEditor::resized()
{
    auto area = getBounds().reduced(20);
    auto sliderWidth = area.getWidth() / 4;
    auto sliderHeight = area.getHeight() / 2;

    auto topRow = area.removeFromTop(sliderHeight);

    inputGainSlider.setBounds(topRow.removeFromLeft(sliderWidth).reduced(30));
    driveSlider.setBounds(topRow.removeFromLeft(sliderWidth).reduced(30));
    toneSlider.setBounds(topRow.removeFromLeft(sliderWidth).reduced(30));
    mixSlider.setBounds(topRow.removeFromLeft(sliderWidth).reduced(30));

    area.removeFromLeft(sliderWidth / 2);
    filterSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(30));
    drySquashSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(30));
    outputGainSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(30));
}
