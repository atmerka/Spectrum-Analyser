/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Sat2AudioProcessor  : public AudioProcessor, public ValueTree::Listener
{
public:
    //==============================================================================
    Sat2AudioProcessor();
    ~Sat2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    //gain compensation
    bool gainCompensation = true;
    
    
    //value tree
    AudioProcessorValueTreeState& getMyVTS()  {return myVTS ;}
    void updateParam();
    
    
    //VARIABLES
    float gain1=0.1f;
    float gain2=0.1f;
    float gain3=0.1f;
    
    float dryWet1=0.1f;
    float dryWet2=0.1f;
    float dryWet3=0.1f;
    
    float dryWet=1.0f;
    float output =1.0f;
    
    float clipThreshold = 1.0f;
    float glitchAmount = 0.0f;
    
    
    //for getting sample randomness
    float lAmountR;
    float rAmountR;
    
    int distType=0;
    
private:
    float samp;
    float prevSamp;
    
    //GLITCH CLIP
    //add the dist
    Random r;
    float rdm;
    
    
    
    //value true
    AudioProcessorValueTreeState myVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    std::atomic<bool> shouldUpdate {false};
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sat2AudioProcessor)
};
