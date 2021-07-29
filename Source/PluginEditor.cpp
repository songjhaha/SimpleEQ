/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    peakFreqAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider),
    peakGainAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider),
    peakQualityAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider),
    lowCutFreqAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
    highCutFreqAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
    lowCutSlopeAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeComboBox),
    highCutSlopAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlopeComboBox),
    GenericAudioProcessorEditor(audioProcessor)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.


    setLabelText();

    addAndMakeVisible(GenericAudioProcessorEditor);
    //for (auto* comp : getComps())
    //{
    //    addAndMakeVisible(comp);
    //}

    
    setSize (400, 400);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    auto topArean = bounds.removeFromTop(bounds.getHeight() * 0.25);
    //auto LableArean = bounds.removeFromLeft(bounds.getWidth() * 0.25);
    //auto SliderArean = bounds;

    //peakFreqLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 7.0));
    //peakGainLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 6.0));
    //peakQualityLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 5.0));
    //lowCutFreqLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 4.0));
    //highCutFreqLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 3.0));
    //lowCutSlopeLabel.setBounds(LableArean.removeFromTop(LableArean.getHeight() / 2.0));
    //highCutSlopLabel.setBounds(LableArean);

    //peakFreqSlider.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 7.0));
    //peakGainSlider.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 6.0));
    //peakQualitySlider.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 5.0));
    //lowCutFreqSlider.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 4.0));
    //highCutFreqSlider.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 3.0));
    //lowCutSlopeComboBox.setBounds(SliderArean.removeFromTop(SliderArean.getHeight() / 2.0));
    //highCutSlopeComboBox.setBounds(SliderArean);
    //GenericAudioProcessorEditor.setBounds(bounds);
    //GenericAudioProcessorEditor.setCentreRelative(0.5f, 0.625f);
    GenericAudioProcessorEditor.setBounds(bounds.getWidth()*0.05, topArean.getHeight(), bounds.getWidth(), bounds.getHeight());
}

std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps()
{
    return
    {
        &peakFreqSlider,
        &peakGainSlider,
        &peakQualitySlider,
        &lowCutFreqSlider,
        &highCutFreqSlider,
        &lowCutSlopeComboBox,
        &highCutSlopeComboBox,
        &peakFreqLabel,
        &peakGainLabel, 
        &peakQualityLabel,
        &lowCutFreqLabel, 
        &highCutFreqLabel,
        &lowCutSlopeLabel, 
        &highCutSlopLabel
    };
}

void SimpleEQAudioProcessorEditor::setLabelText()
{
    peakFreqLabel.setText("Peak Freq", juce::dontSendNotification);
    peakGainLabel.setText("Peak Gain", juce::dontSendNotification);
    peakQualityLabel.setText("Peak Quality", juce::dontSendNotification);
    lowCutFreqLabel.setText("LowCut Freq", juce::dontSendNotification);
    highCutFreqLabel.setText("HighCut Freq", juce::dontSendNotification);
    lowCutSlopeLabel.setText("LowCut Slope", juce::dontSendNotification);
    highCutSlopLabel.setText("HighCut Slope", juce::dontSendNotification);
}