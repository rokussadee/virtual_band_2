//
// Created by Admin on 28/04/2024.
//

#ifndef VIRTUAL_BAND_MIDILISTMODEL_H
#define VIRTUAL_BAND_MIDILISTMODEL_H

#pragma once

#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiMessage and juce::MidiMessageSequence
#include <vector>
#include "helpers/helpers.h"
#include "agent/GptAgent.h"

class MidiListModel {
public:
  MidiListModel();
  ~MidiListModel();
  void addMessages(const juce::MidiMessageSequence& sequence);

  void clear();

  const juce::MidiMessage& operator[](size_t ind) const;

  size_t size() const;

  std::function<void()> onChange;

  void msgV2S(std::vector<juce::MidiMessage> messageVector);

  std::string generateResponse(const std::string& prompt);

private:
  static constexpr auto numToStore = 1000;
  std::vector<juce::MidiMessage> messages;
  Helpers::helpers helpers;
  GptAgent agent;
};

#endif  // VIRTUAL_BAND_MIDILISTMODEL_H
