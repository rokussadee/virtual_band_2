//
// Created by Admin on 29/04/2024.
//
#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiMessage and juce::MidiMessageSequence
#include <juce_core/juce_core.h> // For juce::jmin and juce::jmax
#include "MidiListModel.h"

MidiListModel::MidiListModel() = default;

MidiListModel::~MidiListModel() = default;

void MidiListModel::addMessages(const juce::MidiMessageSequence& sequence) {
  const auto numNewMessages = sequence.getNumEvents();
  const auto numToAdd = juce::jmin(numToStore, numNewMessages);
  const auto numToRemove =
      juce::jmax(0, (int)messages.size() + numToAdd - numToStore);

  DBG("MidiListModel;\n\tnumNewMessages: " << numNewMessages << "\n\tnumToAdd: " << numToAdd << "\n\tnumToRemove: " << numToRemove);
  messages.erase(messages.begin(), std::next(messages.begin(), numToRemove));
  for (int i = 0; i < numToAdd; ++i)
    messages.push_back(sequence.getEventPointer(i)->message);

  if (onChange)
    onChange();

  msgV2S(messages);
}

void MidiListModel::clear() {
  messages.clear();
  if (onChange)
    onChange();
}

size_t MidiListModel::size() const {
  return messages.size();
}

const juce::MidiMessage& MidiListModel::operator[](size_t ind) const {
  return messages[ind];
}


void MidiListModel::msgV2S(std::vector<juce::MidiMessage> messageVector)
{
    std::ostringstream stream = helpers.msgV2S(messageVector);

    std::cout << "Midi Messages in MidiListModel: " << stream.str() << std::endl;
}