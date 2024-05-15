//
// Created by Admin on 13/05/2024.
//
#include <juce_gui_basics/juce_gui_basics.h>
#include "LookAndFeel.h"

namespace juce
{
    void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
    {
        auto outline = slider.findColour (Slider::thumbColourId);
        auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

        auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin (8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        // Dial background path
        Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour (outline);
        g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::square));

        if (slider.isEnabled())
        {
            // Dial fill path
            Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour (fill);
            g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::square));
        }
        // Adjust line starting point to be closer to the edge instead of center
        auto lineStartRadius = arcRadius * 0.5; // Adjust this value to change start position
        Point<float> lineStartPoint (bounds.getCentreX() + lineStartRadius * std::cos (toAngle - MathConstants<float>::halfPi),
            bounds.getCentreY() + lineStartRadius * std::sin (toAngle - MathConstants<float>::halfPi));
        //Line
        Point<float> thumbPoint (bounds.getCentreX() + (arcRadius + 4.0f) * std::cos (toAngle - MathConstants<float>::halfPi),
            bounds.getCentreY() + (arcRadius + 4.0f) * std::sin (toAngle - MathConstants<float>::halfPi));

        g.setColour (slider.findColour (Slider::thumbColourId));
        //g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
        g.drawLine(lineStartPoint.getX(), lineStartPoint.getY(), thumbPoint.getX(), thumbPoint.getY(), lineW);

        // Calculate square positions
        juce::Rectangle<float> square(-lineW* 0.5f, -lineW* 0.5f, lineW, lineW);

        g.setColour(slider.findColour(juce::Slider::rotarySliderFillColourId));

    }
}