//
// Created by Admin on 28/04/2024.
//

#ifndef VIRTUAL_BAND_MIDIQUEUE_H
#define VIRTUAL_BAND_MIDIQUEUE_H
#pragma once

#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiMessage and juce::AbstractFifo
#include <vector>
#include "helpers/helpers.h"

class MidiQueue {
public:
  MidiQueue();
  ~MidiQueue();

  void push(const juce::MidiMessage& message);
  template <typename OutputIt>
  void pop(OutputIt out);
  std::vector<juce::MidiMessage> getMessages();
  std::string getQueueContents() const;
  void msgV2S(std::vector<juce::MidiMessage> messageVector);

private:
  static constexpr auto queueSize = 1024;
  juce::AbstractFifo fifo{queueSize};
  std::vector<juce::MidiMessage> messages;
  Helpers::helpers helpers;
};

#endif  // VIRTUAL_BAND_MIDIQUEUE_H
