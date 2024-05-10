//
// Created by Admin on 29/04/2024.
//

#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiBuffer and juce::MidiMessage
#include <juce_audio_processors/juce_audio_processors.h> // For juce::MidiBuffer operations
#include <juce_core/juce_core.h> // For DBG macro
#include "MidiProcessor.h"

MidiProcessor::MidiProcessor() {}

MidiProcessor::~MidiProcessor() {}

void MidiProcessor::processMidi(juce::MidiBuffer& midiMessages) {
  juce::MidiMessageSequence sequence;

  for (const juce::MidiMessageMetadata metadata : midiMessages) {
    DBG("Processing MIDI Metadata");
    DBG("Metadata: TimeStamp = " << metadata.samplePosition
                                    << ", Message = " << metadata.getMessage().getDescription());

    const juce::MidiMessage message = metadata.getMessage();

    const juce::String description = message.getDescription();

    DBG("MIDI Message Description: " << description);
    DBG("MIDI Message Raw Data Pointer: " << juce::String::toHexString((juce::int64)(message.getRawData())));
    DBG("MIDI Message Raw Data Size: " << message.getRawDataSize());

    DBG(description);

    if (message.getRawData() != nullptr && message.getRawDataSize() > 0)
    {
        midiQueue.push (message);
        DBG ("message pushed to queue successfully");
    } else if (message.getRawDataSize() == 0) {
        DBG("MIDI message has zero size, not pushed to queue. Raw Data Pointer: "
             << juce::String::toHexString((juce::int64)(message.getRawData()))
             << ", Size: " << message.getRawDataSize());
    } else {
        DBG("Invalid MIDI message, not pushed to queue. Raw Data Pointer: "
        <<  juce::String::toHexString((juce::int64)(message.getRawData()))
        << ", Size: " << message.getRawDataSize());
    }

    sequence.addEvent(message, metadata.samplePosition);
  }

  std::vector<juce::MidiMessage> messages;
  midiQueue.pop(std::back_inserter(messages));
  midiListModel.addMessages(sequence);
}
