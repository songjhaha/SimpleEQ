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
    //peakFreqAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider),
    //peakGainAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider),
    //peakQualityAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider),
    //lowCutFreqAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
    //highCutFreqAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
    //lowCutSlopeAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeComboBox),
    //highCutSlopAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlopeComboBox),
    GenericAudioProcessorEditor(audioProcessor)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.


    //setLabelText();

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
    using namespace juce;
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll(Colours::black);

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    auto bounds = getLocalBounds();
    auto topArean = bounds.removeFromTop(bounds.getHeight() * 0.25);

    auto w = topArean.getWidth();

    auto& lowcut = monoChain.get<ChainPositions::LowCut>();
    auto& peak = monoChain.get<ChainPositions::Peak>();
    auto& highcut = monoChain.get<ChainPositions::HighCut>();

    auto sampleRate = audioProcessor.getSampleRate();

    std::vector<double> mags;

    mags.resize(w);

    for (int i = 0; i < w; ++i)
    {
        double mag = 1.0f;
        auto freq = mapToLog10(double(i) / double(w), 20.0, 20000.0);

        if (!monoChain.isBypassed<ChainPositions::Peak>())
            mag *= peak.coefficients->getMagnitudeForFrequency(freq, sampleRate);

        if (!lowcut.isBypassed<0>())
            mag *= lowcut.get<0>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!lowcut.isBypassed<1>())
            mag *= lowcut.get<1>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!lowcut.isBypassed<2>())
            mag *= lowcut.get<2>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!lowcut.isBypassed<3>())
            mag *= lowcut.get<3>().coefficients->getMagnitudeForFrequency(freq, sampleRate);

        if (!highcut.isBypassed<0>())
            mag *= highcut.get<0>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!highcut.isBypassed<1>())
            mag *= highcut.get<1>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!highcut.isBypassed<2>())
            mag *= highcut.get<2>().coefficients->getMagnitudeForFrequency(freq, sampleRate);
        if (!highcut.isBypassed<3>())
            mag *= highcut.get<3>().coefficients->getMagnitudeForFrequency(freq, sampleRate);

        mags[i] = Decibels::gainToDecibels(mag);

        Path responseCurve;
        const double outputMin = topArean.getBottom();
        const double outputMax = topArean.getY();
        auto map = [outputMin, outputMax](double input)
        {
            return jmap(input, -24.0, 24.0, outputMin, outputMax);
        };

        responseCurve.startNewSubPath(topArean.getX(), map(mags.front()));

        for (size_t i = 1; i < mags.size(); ++i)
        {
            responseCurve.lineTo(topArean.getX() + i, map(mags[i]));
        }

        g.setColour(Colours::orange);
        g.drawRoundedRectangle(topArean.toFloat(), 4.0f, 1.0f);

        g.setColour(Colours::white);
        g.strokePath(responseCurve, PathStrokeType(2.0f));
    }
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

//std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps()
//{
//    return
//    {
//        &peakFreqSlider,
//        &peakGainSlider,
//        &peakQualitySlider,
//        &lowCutFreqSlider,
//        &highCutFreqSlider,
//        &lowCutSlopeComboBox,
//        &highCutSlopeComboBox,
//        &peakFreqLabel,
//        &peakGainLabel, 
//        &peakQualityLabel,
//        &lowCutFreqLabel, 
//        &highCutFreqLabel,
//        &lowCutSlopeLabel, 
//        &highCutSlopLabel
//    };
//}

//void SimpleEQAudioProcessorEditor::setLabelText()
//{
//    peakFreqLabel.setText("Peak Freq", juce::dontSendNotification);
//    peakGainLabel.setText("Peak Gain", juce::dontSendNotification);
//    peakQualityLabel.setText("Peak Quality", juce::dontSendNotification);
//    lowCutFreqLabel.setText("LowCut Freq", juce::dontSendNotification);
//    highCutFreqLabel.setText("HighCut Freq", juce::dontSendNotification);
//    lowCutSlopeLabel.setText("LowCut Slope", juce::dontSendNotification);
//    highCutSlopLabel.setText("HighCut Slope", juce::dontSendNotification);
//}