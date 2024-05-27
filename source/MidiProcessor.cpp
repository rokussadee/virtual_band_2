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
      // Check if the message is a SysEx message and skip it if it is
    DBG("Processing MIDI Metadata");
    DBG("Metadata: TimeStamp = " << metadata.samplePosition
                                    << ", Message = " << metadata.getMessage().getDescription());

    const juce::MidiMessage message = metadata.getMessage();

    const juce::String description = message.getDescription();

    DBG("MIDI Message Description: " << description);
    DBG("MIDI Message Raw Data Pointer: " << juce::String::toHexString((juce::int64)(message.getRawData())));
    DBG("MIDI Message Raw Data Size: " << message.getRawDataSize());

    DBG(description);

    if (message.getRawData() != nullptr && message.getRawDataSize() > 0 && message.isNoteOnOrOff())
    {
        midiQueue.push (message);
        DBG ("message pushed to queue successfully");
        sequence.addEvent(message, metadata.samplePosition);
        DBG("message added to the sequence successfully");
    } else if (message.getRawDataSize() == 0) {
        DBG("MIDI message has zero size, not pushed to queue. Raw Data Pointer: "
             << juce::String::toHexString((juce::int64)(message.getRawData()))
             << ", Size: " << message.getRawDataSize());
    } else {
        DBG("Invalid MIDI message, not pushed to queue. Raw Data Pointer: "
        <<  juce::String::toHexString((juce::int64)(message.getRawData()))
        << ", Size: " << message.getRawDataSize());
    }

    DBG("MidiQueue contents: " << midiQueue.getQueueContents());

    std::vector<juce::MidiMessage> messageVector = midiQueue.getMessages();
    std::ostringstream vts;

    if (!messageVector.empty()) {
        msgV2S(messageVector);
    } else {
        DBG("messageVector is empty");
    }

    std::cout << "MidiQueue getMessages started: \n" << vts.str() << "\nMidiQueue getMessages ended\n" << std::endl; // For debugging purposes
  }

  if(!sequence.getNumEvents() == 0)
  {
      std::vector<juce::MidiMessage> messages;
      midiQueue.pop (std::back_inserter (messages));
      midiListModel.addMessages (sequence);
      DBG("MidiMessageSequence: " << toString(sequence));
  }
}

void MidiProcessor::msgV2S(std::vector<juce::MidiMessage> messageVector)
{
    std::ostringstream stream = helpers.msgV2S(messageVector);

    std::cout << "Midi Messages in MidiProcessor: " << stream.str() << std::endl;
}

juce::String MidiProcessor::toString (const juce::MidiMessageSequence& sequence)
{
    juce::String string = helpers.toString(sequence);

    return string;
}