/*
  ==============================================================================

    ClippingStage.h
    Created: 7 Jan 2022 4:22:18pm
    Author:  James Stubbs

  ==============================================================================
*/

#pragma once

#include <chowdsp_dsp/chowdsp_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "ClipWDFa.h"
#include "ClipWDFb.h"
#include "ClipWDFc.h"

class ClippingStage
{
public:
    ClippingStage();
    void setDrive (float drive);
    void reset();
    void prepare (float sampleRate);
    float processSample (float) noexcept;

private:
    float audioTaperPotSim (float in);
    float fs = 44100.0f;

    ClipWDFa clipWDFa;
    ClipWDFb clipWDFb;
    ClipWDFc clipWDFc;

    const float rPot = 500000.0f;

    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> p1Smoothed;

    juce::dsp::Oversampling<float> oversampling { 2, 1, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClippingStage)
};
