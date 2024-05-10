//
// Created by Admin on 29/04/2024.
//

#include <juce_gui_basics/juce_gui_basics.h> // For juce::Graphics, juce::Colours, juce::Justification
#include "MidiTable.h"
#include "MidiListModel.h"

MidiTable::MidiTable(MidiListModel& model) : messages(model) {
  addAndMakeVisible(table);
  table.setModel(this);
  table.setClickingTogglesRowSelection(false);

  // Setting up the headers
  table.getHeader().addColumn("Message", messageColumn, 200);
  table.getHeader().addColumn("Time", timeColumn, 100);
  table.getHeader().addColumn("Channel", channelColumn, 100);
  table.getHeader().addColumn("Data", dataColumn, 200);

  model.onChange = [this] { table.updateContent(); };
}

MidiTable::~MidiTable() {
  messages.onChange = nullptr;
}

void MidiTable::paintRowBackground(juce::Graphics& g,
                                   int rowNumber,
                                   int width,
                                   int height,
                                   bool rowIsSelected) {
  if (rowIsSelected)
    g.fillAll(juce::Colours::lightblue);
  else
    g.fillAll(juce::Colours::white);
}

void MidiTable::paintCell(juce::Graphics& g,
                          int rowNumber,
                          int columnId,
                          int width,
                          int height,
                          bool /*rowIsSelected*/) {
  auto text = getColumnText(messages.size() - 1 - rowNumber, columnId);
  g.setColour(juce::Colours::black);
  g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
}

juce::String MidiTable::getColumnText(const int row, const int columnId) const {
  const auto& message = messages[row];
  switch (columnId) {
    case messageColumn:
      return message.getDescription();
    case timeColumn:
      return juce::String(message.getTimeStamp());
    case channelColumn:
      return juce::String(message.getChannel());
    case dataColumn:
      return juce::MidiMessage::getMidiNoteName(message.getNoteNumber(), true, true,
                                          3) +
             " Velocity " + juce::String(message.getVelocity());
    default:
      return {};
  }
}

int MidiTable::getNumRows() {
    return (int) messages.size();
}
