/*
  ==============================================================================

    BasicStyle.cpp
    Created: 6 Jul 2022 3:46:46pm
    Author:  trissy the sissy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BasicStyle.h"

//==============================================================================
//BasicStyle::


/** Draws the contents of a standard ToggleButton. */
void BasicStyle::drawToggleButton (Graphics& g, ToggleButton& t,
                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    //button pressed drawing
    if(shouldDrawButtonAsDown)
    {
        g.setColour(Colours::black);
        
        g.fillRect(t.getLocalBounds() );
        
    }
    else {
        
        //draw unpressed button based on toggle state
        if(t.getToggleState())
        {
            g.setColour(Colours::lightblue.withAlpha(0.5f));
        }
        else
        {
            g.setColour(Colours::lightgrey.withAlpha(0.3f));
        }
        g.fillRect(t.getLocalBounds());
        
        g.setColour(Colours::lightgrey);
    
        g.drawRect(t.getLocalBounds());
    
        //draw button name
        g.setColour(t.findColour(0x1006502));
        
        g.drawText(t.getButtonText(), t.getLocalBounds(), Justification::centred);
    }
}



void BasicStyle::drawLinearSlider (Graphics& g,
                                  int x, int y, int width, int height,
                                  float sliderPos,
                                  float minSliderPos,
                                  float maxSliderPos,
                                  const Slider::SliderStyle,
                                  Slider& s)
{
    
    
    //drawing linear vertical slider
    if(s.getSliderStyle() == Slider::LinearVertical)
    {
     
        //ratio of the height to draw
        float ratio = s.getValue()/s.getMaximum();
        
        //how many rectangles
        int numDrawn = int(20 *ratio);
        
        for(int i=0; i<20;i++)
        {
         
            float ratio = i/20.0f;
            
            g.setColour(Colours::lightblue);
            
            g.fillRect(width/2-15.0f, height-ratio*height, 30.0f, 10.0f);
            
            
            if(i>= numDrawn) break;
        }
        
        
        
        //DRAWING NUMBERS
        
        juce::String suffix = s.getTextValueSuffix();
        
        if(s.getTextBoxPosition() == Slider::TextBoxLeft)
        {
            g.setColour(Colours::black.withAlpha(0.4f));
            float gain = s.getValue();
            gain = gain;
            gain = juce::Decibels::gainToDecibels(gain);
            
            gain = std::ceil(gain*100)/100;
            g.drawText((String)gain+ suffix, 0, 0, width, height, Justification::centred);
        }
        
        if(s.getTextBoxPosition() == Slider::TextBoxRight)
        {
            g.setColour(Colours::black.withAlpha(0.4f));
            
            float percent = 100*s.getValue();
            
            g.drawText((String)percent+ suffix, 0, 0, width, height, Justification::centred);
        }
        
    }
    
    //Linear horizontal style
    else if(s.getSliderStyle() == Slider::LinearHorizontal)
    {
    
        //draw outline
        g.setColour(Colours::black);
        g.drawRect(x, y, width, height);
        
        //drawing number
        g.setColour(Colours::lightgrey);
        g.drawText(s.getTextFromValue(s.getValue()), s.getLocalBounds(), Justification::centred);
        
        //draw rectangle
        g.fillRect(x, y,int(sliderPos-12) , height);
        
        g.setColour(Colours::red);
        g.drawRect(x, y,int(sliderPos-12) , height);
        
        
        if(s.getValue()> (s.getMaximum()/2))
        {
    
            g.setColour(Colours::white);
            g.drawText((s.getTextFromValue(s.getValue())), s.getLocalBounds(), Justification::centred);
        }
    }
}
    
    
void BasicStyle::drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                       float sliderPosProportional, float rotaryStartAngle,
                                       float rotaryEndAngle, Slider& s)
{
    
    //draw a circle of blue balls
    //convert the value of the slider to an integer 1- 20
    
    //ratio/number of balls to draw
    float ratio = s.getValue()/s.getMaximum();
    int numDrawn = int(20 *ratio);
    
    float pitwo = 2 * 3.1415;
    float r = width/2-12;
    
    //draw each ball at the right place until we get to the ratio
    for(int i=0; i< 20;i++)
    {
        //distances from centre to each ball
        float adjacent = cos((i/20.0f)*pitwo)*r;
        float opposite = sin((i/20.0f)*pitwo)*r;
        
        //x is middle minus distance to x
        //y is midd +distance to y
        
        //draw balls
        g.setColour(Colours::aliceblue);
        g.fillEllipse(width/2-adjacent, height/2-opposite, 9.0f, 9.0f);
        
        //another ball
        g.setColour(Colours::lightblue);
        g.drawEllipse(width/2-adjacent, height/2-opposite, 9.0f, 9.0f, 2.0f);
        
        //stop drawing
        if(i>(numDrawn-2)) break;
    }
    
    
    //get suffix from slider
    juce::String suffix = s.getTextValueSuffix();

    //write values on sliders
    if(s.getTextBoxPosition() == Slider::TextBoxLeft)
    {
        float gain = s.getValue();
        gain = 4* gain;
        gain = std::pow(10, gain);
        gain = juce::Decibels::gainToDecibels(gain);
        g.drawText((String)gain+ suffix, 0, 0, width, height, Justification::centred);
    }
    
    if(s.getTextBoxPosition() == Slider::TextBoxRight)
    {
        float perc = s.getValue()*100;

        g.drawText((String)perc + suffix, 0, 0, width, height, Justification::centred);
    }
    
}
