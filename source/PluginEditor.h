#pragma once

#include "BinaryData.h"
#include "LookAndFeel.h"
#include "PluginProcessor.h"
#include "melatonin_inspector/melatonin_inspector.h"
#include <juce_audio_utils/juce_audio_utils.h> // For MidiKeyboardComponent
#include <juce_gui_basics/juce_gui_basics.h> // For juce::AudioProcessorEditor, juce::Graphics, juce::TextButton

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::CustomLNF customLnf;
    juce::CustomDial customDial;
    PluginProcessor& processorRef;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton { "Inspect the UI" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
