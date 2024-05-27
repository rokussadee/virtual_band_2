//
// Created by Admin on 27/05/2024.
//

#include <juce_audio_basics/juce_audio_basics.h> // For juce::MidiBuffer and juce::MidiMessage

#ifndef VIRTUALBAND2_HELPERS_H
#define VIRTUALBAND2_HELPERS_H

namespace Helpers
{
    class helpers
    {
    public:
        std::ostringstream msgV2S (std::vector<juce::MidiMessage> messageVector) const
        {
            std::ostringstream vts;
            for (auto it = messageVector.begin(); it != messageVector.end(); ++it)
            {
                if(it->isNoteOnOrOff())
                {
                    vts << it->getDescription();
                    DBG (it->getDescription());
                    if (std::next (it) != messageVector.end())
                    {
                        vts << ", ";
                    }
                }
            }
            return vts;
        }

        juce::String toString(const juce::MidiMessageSequence& sequence) {
            juce::String result;
            for (int i = 0; i < sequence.getNumEvents(); ++i) {
                const auto* event = sequence.getEventPointer(i);
                if (event != nullptr) {
                    result += "Time: " + juce::String(event->message.getTimeStamp()) + " Message: " + event->message.getDescription() + "\n";
                }
            }
            return result;
        }
    };
}

#endif //VIRTUALBAND2_HELPERS_H
