/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_data_structures/juce_data_structures.h>

#include "dsp/ClippingStage.h"
#include "dsp/DryComp.h"
#include "dsp/DryLPF.h"
#include "dsp/ToneStage.h"

//==============================================================================
/**
*/
class TS808UltraAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    TS808UltraAudioProcessor();
    ~TS808UltraAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameters;

    std::atomic<float>* inputGainParameter = nullptr;
    std::atomic<float>* driveParameter = nullptr;
    std::atomic<float>* toneParameter = nullptr;
    std::atomic<float>* mixParameter = nullptr;
    std::atomic<float>* filterParameter = nullptr;
    std::atomic<float>* drySquashParameter = nullptr;
    std::atomic<float>* outputGainParameter = nullptr;

    juce::dsp::DryWetMixer<float> dryWetMixer;

    ClippingStage clippingStage[2];
    ToneStage toneStage[2];
    DryLPF dryLPF;
    DryComp dryComp;

    size_t oversampleFactor = 1;
    juce::dsp::Oversampling<float> oversampling { 2, oversampleFactor, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR };

    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain;

    juce::AudioBuffer<float> parallelBuffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TS808UltraAudioProcessor)
};
