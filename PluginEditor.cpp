/*
  ==============================================================================


  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Sat2AudioProcessorEditor::Sat2AudioProcessorEditor (Sat2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //timer to recall every 20ms
    startTimer(20);

    
    //input sliders
    inputS1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    inputS1.setTextBoxStyle(Slider::TextBoxLeft, true, 0, 0);
    inputS1.setLookAndFeel(&basicStyle);
    inputS1.setSkewFactor(4);
    inputS1.setTextValueSuffix("dB");
    
    
    myInputS1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "INPUT1", inputS1);
    addAndMakeVisible(inputS1);
    
    inputS2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
       inputS2.setTextBoxStyle(Slider::TextBoxLeft, true, 0, 0);
       inputS2.setLookAndFeel(&basicStyle);
       inputS2.setSkewFactor(4);
       
       myInputS2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "INPUT2", inputS2);
       addAndMakeVisible(inputS2);
//    inputS2.setRange(1.0f, 500.0f);
    inputS2.setTextValueSuffix("dB");
    
    
    inputS3.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    inputS3.setTextBoxStyle(Slider::TextBoxLeft, true, 0, 0);
    inputS3.setLookAndFeel(&basicStyle);
    inputS3.setSkewFactor(4);
    
    myInputS3Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "INPUT3", inputS3);
    addAndMakeVisible(inputS3);
//       inputS3.setRange(1.0f, 500.0f);
   inputS3.setTextValueSuffix("dB");
       
    
    //drywet sliders
      dryWetS1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
      dryWetS1.setTextBoxStyle(Slider::TextBoxRight, true, 0, 0);
      dryWetS1.setLookAndFeel(&basicStyle);
      dryWetS1.setSkewFactor(4);
    dryWetS1.setTextValueSuffix("%");
      
      myDryWetS1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "DRYWET1", dryWetS1);
      addAndMakeVisible(dryWetS1);
    
     dryWetS2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
     dryWetS2.setTextBoxStyle(Slider::TextBoxRight, true, 0, 0);
     dryWetS2.setLookAndFeel(&basicStyle);
     dryWetS2.setSkewFactor(4);
     dryWetS2.setTextValueSuffix("%");
    
     myDryWetS2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "DRYWET2", dryWetS2);
     addAndMakeVisible(dryWetS2);
    
    dryWetS3.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetS3.setTextBoxStyle(Slider::TextBoxRight, true, 0, 0);
    dryWetS3.setLookAndFeel(&basicStyle);
    dryWetS3.setSkewFactor(4);
    dryWetS3.setTextValueSuffix("%");
    
    
    myDryWetS3Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "DRYWET3", dryWetS3);
    addAndMakeVisible(dryWetS3);
         
    //GLOBAL SLIDERS
    dryWetS.setSliderStyle(Slider::LinearVertical);
    dryWetS.setTextBoxStyle(Slider::TextBoxRight, true, 0, 0);
    dryWetS.setLookAndFeel(&basicStyle);
    dryWetS.setSkewFactor(4);
    dryWetS.setTextValueSuffix("%");
    
    myDryWetSAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "DRYWET", dryWetS);
    addAndMakeVisible(dryWetS);
    
    outputS.setSliderStyle(Slider::LinearVertical);
   outputS.setTextBoxStyle(Slider::TextBoxLeft, true, 0, 0);
   outputS.setLookAndFeel(&basicStyle);
   outputS.setSkewFactor(4);
    outputS.setTextValueSuffix("dB");
   
   myOutputSAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "OUTPUT", outputS);
   addAndMakeVisible(outputS);
    
    
    //GLITCH CLIP
    clipThreshold.setSliderStyle(Slider::LinearVertical);
    clipThreshold.setTextBoxStyle(Slider::TextBoxLeft, true, 0, 0);
    clipThreshold.setLookAndFeel(&basicStyle);
//    clipThreshold.setSkewFactor(4);
    
    clipThreshold.setTextValueSuffix("db");
    
    myClipThresholdAttachment=std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "CLIPTHRESHOLD", clipThreshold);
    addAndMakeVisible(clipThreshold);
    

    glitchAmount.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    glitchAmount.setTextBoxStyle(Slider::TextBoxRight, true, 0, 0);
    glitchAmount.setLookAndFeel( &basicStyle);
//    glitchAmount.setSkewFactor(4);
    
    glitchAmount.setTextValueSuffix("%");
    
    myGlitchAmountAttachment  =std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getMyVTS(), "GLITCHAMOUNT", glitchAmount);
    
    
    addAndMakeVisible(glitchAmount);
    
    
    //BUTTONS
    type1B.addListener(this);
    addAndMakeVisible(type1B);
    type1B.setButtonText("type1");
    type1B.setColour(0x1006502, Colours::lightblue);
    type1B.setLookAndFeel(&basicStyle);
    
    
    
    type2B.addListener(this);
    addAndMakeVisible(type2B);
    type2B.setButtonText("type2");
    type2B.setColour(0x1006502, Colours::lightblue);
    type2B.setLookAndFeel(&basicStyle);
    
    type3B.addListener(this);
    addAndMakeVisible(type3B);
    type3B.setButtonText("type3");
    type3B.setColour(0x1006502, Colours::lightblue);
    type3B.setLookAndFeel(&basicStyle);
    
    
    
    
    //set plugin window size
    setSize (800, 400);
    
}

Sat2AudioProcessorEditor::~Sat2AudioProcessorEditor()
{
}

//==============================================================================
void Sat2AudioProcessorEditor::paint (Graphics& g)
{
    //BACKGROUND
    g.fillAll (Colours::powderblue.withAlpha(0.4f));

    
    //HEADING
    g.setColour(Colours::lightblue.withAlpha(0.8f));
    g.setFont(30.0f);
    g.drawText("M U L T I - S A T", 0, 0, getWidth(), getHeight()*0.2, Justification::centred);
    
    //heading box
    g.setColour(Colours::black.withAlpha(0.3f));
    g.drawRect(0, 0, getWidth(), getHeight()*0.2);
    
    
    
    //boxes (OUTLINES)
    g.drawRect(0.0f, getHeight()* 0.2, getWidth()*0.13f, getHeight()*0.8f);
    g.drawRect(0.13f* getWidth(), getHeight()* 0.2f, getWidth()*0.13f, getHeight()*0.8f);
    g.drawRect(0.26f* getWidth(), getHeight()* 0.2f, getWidth()*0.13f, getHeight()*0.8f);
    
    g.drawRect(0.4f* getWidth(), getHeight()* 0.2f, getWidth()*0.1f, getHeight()*0.8f);
    g.drawRect(0.5f* getWidth(), getHeight()* 0.2f, getWidth()*0.1f, getHeight()*0.8f);
    
    g.drawRect(0.6f* getWidth(), getHeight()* 0.2f, getWidth()*0.4f, getHeight()*0.8f);
    
    
    //headings
    g.setFont(14.0f);
    g.setColour(Colours::lightgrey.withAlpha(0.6f));
    
    g.drawText("1/X", 0.0f, 0.2*getHeight(), 0.13*getWidth(), 0.1*getHeight(), Justification::centred);
    g.drawText("Sin", 0.13f*getWidth(), 0.2*getHeight(), 0.13*getWidth(), 0.1*getHeight(), Justification::centred);
    g.drawText("Tanh", 0.26f*getWidth(), 0.2*getHeight(), 0.13*getWidth(), 0.1*getHeight(), Justification::centred);
    
    g.drawText("%ALL", 0.4f*getWidth(), 0.2f*getHeight(), 0.1f*getWidth(), 0.1f*getHeight(), Justification::centred);
    g.drawText("OUTPUT", 0.5f*getWidth(), 0.2f*getHeight(), 0.1f*getWidth(), 0.1f*getHeight(), Justification::centred);
    
    g.drawText("G L I T C H ~ C L I P", 0.6f*getWidth(), 0.2f*getHeight(), 0.4f*getWidth(), 0.1f*getHeight(), Justification::centred);
    
    
    g.drawText("TYPE", 0.61*getWidth(), 0.8*getHeight(), 0.1*getWidth(), 0.2*getHeight(), Justification::centred);
    g.drawText("THRESHOLD", 0.7*getWidth(), 0.8*getHeight(), 0.1*getWidth(), 0.2*getHeight(), Justification::centred);
    g.drawText("GLITCH AMOUNT", 0.8*getWidth(), 0.8*getHeight(), 0.2*getWidth(), 0.2*getHeight(), Justification::centred);
    
    //bottom
    g.setColour(Colours::black.withAlpha(0.4f));
    g.fillRect(0, 0.93*getHeight(), getWidth(), getHeight()*0.07);
    
    g.setColour(Colours::white);
    g.drawText("SATURATION ALGORITHMS", 0, getHeight()*0.93, getWidth()*0.4,0.07*getHeight(), Justification::centred);
    g.drawText("GLOBAL", 0.4*getWidth(), 0.93*getHeight(), 0.2*getWidth(), 0.07*getHeight(), Justification::centred);
    g.drawText("NOISE CLIPPING/DIGITAL DISTORTION", 0.6*getWidth(), 0.93*getHeight(), 0.4*getWidth(), 0.07*getHeight(), Justification::centred);
    
    
}

void Sat2AudioProcessorEditor::resized()
{
    //layout sliders
    inputS1.setBoundsRelative(0.0f, 0.3f, 0.13f, 0.25f);
    inputS2.setBoundsRelative(0.13f, 0.3f, 0.13f, 0.25f);
    inputS3.setBoundsRelative(0.26f, 0.3f, 0.13f, 0.25f);
    
    dryWetS1.setBoundsRelative(0.0f, 0.6f, 0.13f, 0.25f);
    dryWetS2.setBoundsRelative(0.13f, 0.6f, 0.13f, 0.25f);
    dryWetS3.setBoundsRelative(0.26f, 0.6f, 0.13f, 0.25f);
    
    
    dryWetS.setBoundsRelative(0.4f, 0.3f, 0.1f, 0.6f);
    outputS.setBoundsRelative(0.5, 0.3f, 0.1f, 0.6f);
    
    
    clipThreshold.setBoundsRelative(0.7, 0.3, 0.1, 0.6);
    glitchAmount.setBoundsRelative(0.8, 0.3, 0.2, 0.6);
    
    type1B.setBoundsRelative(0.65, 0.4, 0.05, 0.1);
    type2B.setBoundsRelative(0.65, 0.55, 0.05, 0.1);
    type3B.setBoundsRelative(0.65, 0.7, 0.05, 0.1);
    
}

void Sat2AudioProcessorEditor::timerCallback()
{
    repaint();
}


void Sat2AudioProcessorEditor::buttonStateChanged(Button* button)
{
    //SET DISTORTION TYPE FOR GLITCH CLIP
    if(button->getButtonText() == "type1")
    {
        if(button->getToggleState())
        {
            processor.distType = 0;
            type2B.setToggleState(0, dontSendNotification);
            type3B.setToggleState(0, dontSendNotification);
        }
        
    }
    if(button->getButtonText() == "type2")
    {
        if(button->getToggleState())
       {
           processor.distType = 1;
           type1B.setToggleState(0, dontSendNotification);
           type3B.setToggleState(0, dontSendNotification);
       }
        
    }
    
    if(button->getButtonText() == "type3")
       {
           if(button->getToggleState())
          {
              processor.distType = 2;
              type2B.setToggleState(0, dontSendNotification);
              type1B.setToggleState(0, dontSendNotification);
          }
           
       }
}
void Sat2AudioProcessorEditor::buttonClicked (Button* button)
{
    
}
