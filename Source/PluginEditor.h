/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
struct ResponseCurveComponent : juce::Component,
    juce::AudioProcessorParameter::Listener,
    juce::Timer
{
    ResponseCurveComponent(SimpleEQAudioProcessor&);
    ~ResponseCurveComponent();

    void parameterValueChanged(int parameterIndex, float newValue) override;

    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override { }

    void timerCallback() override;

    void paint(juce::Graphics& g) override;


private:
    SimpleEQAudioProcessor& audioProcessor;


    juce::Atomic<bool> parametersChanged{ false };

    MonoChain monoChain;

};




//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //void parameterValueChanged(int parameterIndex, float newValue) override;

    //void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override { }

    //void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;


    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;


    //juce::Slider peakFreqSlider,
    //    peakGainSlider, peakQualitySlider,
    //    lowCutFreqSlider, highCutFreqSlider;

    //juce::ComboBox lowCutSlopeComboBox, highCutSlopeComboBox;

    //juce::Label peakFreqLabel,
    //    peakGainLabel, peakQualityLabel,
    //    lowCutFreqLabel, highCutFreqLabel,
    //    lowCutSlopeLabel, highCutSlopLabel;

    //SliderAttachment peakFreqAttachment,
    //    peakGainAttachment, peakQualityAttachment,
    //    lowCutFreqAttachment, highCutFreqAttachment;

    //ComboBoxAttachment lowCutSlopeAttachment, highCutSlopAttachment;

    //std::vector<juce::Component*> getComps();

    //void setLabelText();

    juce::GenericAudioProcessorEditor GenericAudioProcessorEditor;

    ResponseCurveComponent responesCurve;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
