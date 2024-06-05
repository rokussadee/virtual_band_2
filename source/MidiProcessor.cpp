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
// TODO: Setup "listening" state based on button click
//          Approach: Implement a UI button that toggles the state of the application between listening and not listening.
//          Implementation: Use a boolean flag (e.g., isListening) that changes state based on the button click.
//                          This flag will control whether incoming MIDI messages are processed or ignored.
// TODO: pass BPM and # of bars to record
//          Approach: Allow the user to input the desired BPM and the number of bars for recording.
//          Implementation: Create UI elements (e.g., text fields or sliders) for the user to input BPM and bar count.
//                          Store these values in variables (e.g., bpm, numBars).
// TODO: count-in functionality
//          Approach: Implement a count-in feature to give the user a few beats before recording starts.
//          Implementation: Use a timer or a separate thread to handle the count-in.
//                          Display visual feedback (e.g., flashing lights or a countdown) to indicate the count-in progress.
// TODO: MIDI notes get recorded and added to the MidiListModel
//          Approach: Record incoming MIDI notes while in the listening state and add them to the MidiListModel.
//          Implementation: In the MIDI message handler, check the isListening flag.
//                          If true, add the incoming messages to the MidiListModel
// TODO: Pass timing info to Midi note information
//          Approach: Include timing information (e.g., timestamp) with each MIDI note.
//          Implementation: Modify the MidiMessage class to include timing information.
//                          Capture the timestamp when each MIDI message is received and store it in the MidiMessage object.
// TODO: Test GPT agent to conclude on best MIDI formatting
//          Approach: Determine the optimal MIDI format for the GPT agent by conducting tests.
//          Implementation: Create sample MIDI sequences in various formats and test them with the GPT agent.
//                          Evaluate which format yields the best results.
// TODO: IF necessary, reformat timing of Midi notes to a quantized "musical" value that clearly represents its position in the recorded measure.
//          Approach: Quantize the MIDI notes to the nearest musical value (e.g., 1/4 note, 1/8 note) if required for better representation.
//          Implementation: Implement a quantization function that adjusts the timestamps of the notes to the nearest musical value.
//                          This may involve calculating the nearest beat based on the BPM.
//          opt1) Reformat "note on"/"note off" values to a single note value with a length.
//                          Approach: Combine note on and note off messages into a single note representation with a duration.
//                          Implementation: Track note on and note off pairs and calculate the duration between them.
//                                          Store the note with its start time and duration.
//          opt2) leave on/off messages separate
//                          Approach: Keep note on and note off messages as distinct events.
//                          Implementation: No additional changes needed. Ensure both events are recorded accurately.
// TODO: Function that takes the system's note collection and formats it to the GPT agent's preferred format
//          Approach: Implement a function to convert the recorded MIDI notes into the format required by the GPT agent.
//          Implementation: Define the format required by the GPT agent.
//                                          Create a function that processes the MidiListModel data and outputs it in the required format.
// TODO: Find out: What's the preferred method of streaming incoming notes?
//          Approach: Research and decide on the best method to stream MIDI notes in real-time.
//          Implementation: Look into existing protocols and APIs for real-time MIDI streaming.
//                          Consider using WebSockets, MIDI over USB, or other suitable methods.
// TODO: Function that does the reverse of this
//          Approach: Implement a function to convert the GPT agent's output back into a format usable by the system.
//          Implementation: Define the reverse conversion process.
//                          Create a function that takes the GPT agent's output and translates it back into MIDI messages or another suitable format for playback or further processing.
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