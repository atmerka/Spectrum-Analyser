/*
  ==============================================================================

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BasicStyle.h"

//==============================================================================
/**
*/
class Sat2AudioProcessorEditor  : public AudioProcessorEditor, public Timer,public Button::Listener
{
public:
    Sat2AudioProcessorEditor (Sat2AudioProcessor&);
    ~Sat2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    //processor refrence
    Sat2AudioProcessor& processor;
    
    //creat Style object
    BasicStyle basicStyle;
    
    //calls this function repeatedly to do graphics
    void timerCallback() override;

    //define sliders
    Slider inputS1, inputS2, inputS3;
    Slider dryWetS1, dryWetS2, dryWetS3;
    Slider outputS, dryWetS;
    
    Slider clipThreshold;
    Slider glitchAmount;
    
    //and buttons
    ToggleButton type1B,type2B,type3B;
    
    
    
    //define attachments for value tree (parameters)
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myInputS1Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myInputS2Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myInputS3Attachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myDryWetS1Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myDryWetS2Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myDryWetS3Attachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myDryWetSAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myOutputSAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myClipThresholdAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> myGlitchAmountAttachment;
    
    
    //functions for button
    void buttonStateChanged(Button* button) override;
    void buttonClicked (Button* button) override;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sat2AudioProcessorEditor)
};
