//
// Created by Admin on 29/04/2024.
//
#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiMessage and juce::AbstractFifo
#include "MidiQueue.h"

// Properly initialize messages with queueSize
MidiQueue::MidiQueue() : messages(queueSize) {
    DBG("MidiQueue initialized with size: " << messages.size());
}
MidiQueue::~MidiQueue() {}

void MidiQueue::push(const juce::MidiMessage& message) {
    DBG("Preparing to push MIDI Message:");
    DBG("Message Timestamp: " << message.getTimeStamp());
    DBG("Message Size: " << message.getRawDataSize());
    DBG("Message Data Pointer: " << juce::String::toHexString((juce::int64)(message.getRawData())));

  int size1, start1, size2, start2;
  fifo.prepareToWrite(1, start1, size1, start2, size2);
  DBG("Prepared to write: size1 = " << size1 << ", start1 = " << start1
                                     << ", size2 = " << size2 << ", start2 = " << start2);

  // Safety check before writing
  if (start1 >= messages.size() || start1 < 0) {
      DBG("start1: " << start1  <<  ", messages.size(): " << messages.size());
      DBG("Error: start1 index out of bounds: " << start1);
      return;
  }
  if (start2 >= messages.size() || (size2 > 0 && start2 < 0)) {
      DBG("start2: " << start2  <<  ", messages.size(): " << messages.size());
      DBG("Error: start2 index out of bounds: " << start2);
      return;
  }

  if (size1 > 0)
  {
      if (message.getRawData() != nullptr && message.getRawDataSize() > 0) {
          messages[start1] = message;
          DBG("Message assigned at start1");
      } else if (message.getRawDataSize() == 0) {
          DBG("Skipping push: MIDI message size is zero at start1.");
      }  else {
          DBG("Invalid MIDI message data, skipping push at start1.");
      }
  }
  if (size2 > 0)
  {
      if (message.getRawData() != nullptr && message.getRawDataSize() > 0)
      {
          messages[start2] = message;
          DBG ("Message assigned at start2");
      } else if (message.getRawDataSize() == 0) {
          DBG("Skipping push: MIDI message size is zero at start2.");
      } else
      {
          DBG ("Invalid MIDI message data, skipping push at start2.");
      }
      fifo.finishedWrite (size1 + size2);
      DBG("Finished writing to FIFO, size1 + size2 = " << (size1 + size2));
  }
  msgV2S(messages);
}

template <typename OutputIt>
void MidiQueue::pop(OutputIt out) {
  int size1, start1, size2, start2;
  fifo.prepareToRead(fifo.getNumReady(), start1, size1, start2, size2);
  for (int i = start1; i < start1 + size1; i++)
    *out++ = messages[i];
  for (int i = start2; i < start2 + size2; i++)
    *out++ = messages[i];
  fifo.finishedRead(size1 + size2);
}
template void
    MidiQueue::pop<std::back_insert_iterator<std::vector<juce::MidiMessage>>>(
        std::back_insert_iterator<std::vector<juce::MidiMessage>>);


std::vector<juce::MidiMessage> MidiQueue::getMessages()
{
    std::vector<juce::MidiMessage> result;
    int size1, start1, size2, start2;
    fifo.prepareToRead(fifo.getNumReady(), start1, size1, start2, size2);
    DBG("prepareToRead: start1 = " << start1 << ", size1 = " << size1 << ", start2 = " << start2 << ", size2 = " << size2);

    for (int i = start1; i < start1 + size1; ++i) {
        if (!messages[i].isSysEx()) {
        DBG("Reading message at index " << i << ": " << messages[i].getDescription());
        result.push_back(messages[i]);
        }
    }

    for (int i = start2; i < start2 + size2; ++i) {
        if (!messages[i].isSysEx()) {
        DBG("Reading message at index " << i << ": " << messages[i].getDescription());
        result.push_back(messages[i]);
        }
    }

    fifo.finishedRead(size1 + size2);
    msgV2S(result);
    DBG("Finished reading, total messages read: " << result.size());
    return result;
//    while (!messages.empty())
//    {
//        messages.push_back(result.front());
//        result.pop_front();
//    }
//    return messages;
}

std::string MidiQueue::getQueueContents() const
{
    std::string contents;
    for (const auto& message : messages)
    {
        if (message.isSysEx()) {
            continue;
        }
        contents += message.getDescription().toStdString() + "\n";
    }
    return contents;
}


void MidiQueue::msgV2S(std::vector<juce::MidiMessage> messageVector)
{
    std::ostringstream stream = helpers.msgV2S(messageVector);

    std::cout << "Midi Messages in MidiQueue: " << stream.str() << std::endl;
}