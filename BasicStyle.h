/*
  ==============================================================================

    BasicStyle.h
    Created: 6 Jul 2022 3:46:46pm
    Author:  Tristan
 
 Overrides the look and feel class to make a custom look for this theme

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BasicStyle    : public LookAndFeel_V4
{
public:

     void drawToggleButton (Graphics&, ToggleButton&,
                                   bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
 
    
    void drawLinearSlider (Graphics& ,
                                      int x, int y, int width, int height,
                                      float sliderPos,
                                      float minSliderPos,
                                      float maxSliderPos,
                                      const Slider::SliderStyle,
                           Slider& ) override;
    
    
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, Slider&) override;
 
    
private:
    
};
