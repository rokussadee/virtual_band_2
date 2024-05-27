//
// Created by Admin on 28/04/2024.
//
#ifndef VIRTUAL_BAND_MIDIPROCESSOR_H
#define VIRTUAL_BAND_MIDIPROCESSOR_H

#pragma once

#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiBuffer
#include "MidiQueue.h"
#include "MidiListModel.h"
#include "MidiTable.h"
#include "helpers/helpers.h"

class MidiProcessor {
public:
  MidiProcessor();
  ~MidiProcessor();
  void processMidi(juce::MidiBuffer& midiMessages);
  void msgV2S(std::vector<juce::MidiMessage> messageVector);
  juce::String toString(const juce::MidiMessageSequence& sequence);

private:
  MidiQueue midiQueue;
  MidiListModel midiListModel;
  Helpers::helpers helpers;
};

#endif  // VIRTUAL_BAND_MIDIPROCESSOR_H
