//
// Created by Admin on 28/04/2024.
//

#ifndef VIRTUAL_BAND_MIDITABLE_H
#define VIRTUAL_BAND_MIDITABLE_H

#pragma once

#include <juce_gui_basics/juce_gui_basics.h> // For juce::Component and juce::TableListBoxModel
#include "MidiListModel.h"

class MidiTable final : public juce::Component, private juce::TableListBoxModel {
public:
  explicit MidiTable(MidiListModel& m);
  ~MidiTable() override;

  void paintRowBackground(juce::Graphics& g,
                          int rowNumber,
                          int width,
                          int height,
                          bool rowIsSelected) override;
  void paintCell(juce::Graphics& g,
                 int rowNumber,
                 int columnId,
                 int width,
                 int height,
                 bool rowIsSelected) override;
  int getNumRows() override;
  juce::String getColumnText(const int row, const int columnId) const;

private:
  enum ColumnIDs { messageColumn = 1, timeColumn, channelColumn, dataColumn };

  MidiListModel& messages;
  juce::TableListBox table;
};

#endif  // VIRTUAL_BAND_MIDITABLE_H
