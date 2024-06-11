//
// Created by Admin on 12/05/2024.
//

#ifndef VIRTUALBAND2_LOOKANDFEEL_H
#define VIRTUALBAND2_LOOKANDFEEL_H
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce
{
    class CustomLNF : public juce::LookAndFeel_V4
    {
    public:

        class ColorScheme
        {
        public:
            enum UIColour {
                windowBackground = 0,
                widgetBackground,
                menuBackground,
                outline,
                defaultText,
                defaultFill,
                highlightedText,
                highlightedFill,
                menuText,
                numColours
            };
        };
        void drawRotarySlider (Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &);
    };

    class CustomButton: public TextButton
    {
    public:
        CustomButton()
        {
            auto buttonText = getButtonText();
            setButtonText("Button");
        }

    };

    class CustomDial : public Slider
    {
    public:
        CustomDial()
        {
            auto rotaryParams = getRotaryParameters();
            rotaryParams.startAngleRadians = juce::MathConstants<float>::pi * 1.05f;
            rotaryParams.endAngleRadians = juce::MathConstants<float>::pi * 2.95f;
            setRotaryParameters(rotaryParams);
            setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
            setRange(0.0f, 100.0f);
            setValue(25.0f);
            setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);

            setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::red);
            setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
            setPaintingIsUnclipped(true);

        }
        void valueChanged() override
        {
            Slider::valueChanged();
            repaint(); // Ensures the component repaints when the value changes
        }
    };
}
#endif // VIRTUALBAND2_LOOKANDFEEL_H
