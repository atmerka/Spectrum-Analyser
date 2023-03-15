/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Sat2AudioProcessor::Sat2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),  myVTS(*this, nullptr, "Parameters", createParameters())
#endif
{
    //Add this as a listener to the value tree
    myVTS.state.addListener(this);
    
    updateParam();
}

Sat2AudioProcessor::~Sat2AudioProcessor()
{
}

//==============================================================================
const String Sat2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Sat2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Sat2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Sat2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Sat2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Sat2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Sat2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Sat2AudioProcessor::setCurrentProgram (int index)
{
}

const String Sat2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Sat2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Sat2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    updateParam();
}

void Sat2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Sat2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Sat2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    //setup main audio buffer
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    AudioSampleBuffer distBuffer;
    
    //clear distorted buffer, set it
    distBuffer.clear();
    distBuffer.setSize(2, buffer.getNumSamples());

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //read from here
        auto* channelData = buffer.getWritePointer (channel);
        //write to here then write to channeldata
        auto* channelDataDist = distBuffer.getWritePointer(channel);


        for(int s=0; s<buffer.getNumSamples();s++)
        {

            float sample = channelData[s];
            
            
            //DIFFERENT TYPES OF DISTORTION!! ==========
//            float val = std::tanh(channelData[s]*gain);
//            float val = std::fmod(gain*sample+1, 2.0) -1;
//            float val = std::fmod(gain*sample+varA, varB) -varC;
            
            //a GOOD RATIO but noise
//            float val = std::fmod(gain*sample-1, 1.5) -0.3;
            //better ratio
//            float val = std::fmod(gain*sample-0.7, 1.5) +0.7;
//            if(val<0) val+=2.0;
            
//            float val = std::sin(sample*gain);
//            float pi = M_PI;
//            float val = 2/pi * std::atan(sample*pi*2);
//            float val = 2/pi * std::atan(sample*gain);
            
            //DIFFERENT TYPES OF DISTORTION!! ==========
            float val1 = gain1*sample/(1+ abs(gain1*sample));
            
            float pi = M_PI;
            float val2 = 2/pi * std::atan(sample*gain2);
            
            float val3 = std::sin(sample*gain3);

            if(gainCompensation)
            {
                val1 = val1 * (1-(gain1/16000));
                val2 = val2 * (1-(gain2/16000));
                val3 = val3 * (1-(gain3/16000));
            }
            
            channelDataDist[s]  = (val1*dryWet1
                                + val2*dryWet2
                                + val3*dryWet3)/3;
        }
        
    }
    
    
    //drywet
    for(int c = 0 ; c< totalNumInputChannels; ++c)
    {
        //read from here
        auto* channelData = buffer.getWritePointer (c);
        //write to here then write to channeldata
        auto* channelDataDist = distBuffer.getWritePointer(c);

        for(int s=0; s <buffer.getNumSamples();s++)
        {
            float val = channelData[s]* (1-dryWet) + channelDataDist[s]* dryWet;
          
            channelData[s] =val;
            
        }
    }
    
    
    
    //GLITCH CLIP
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
        
        
        float valL;
        float valR;
        
        if(distType == 0)
        {
            //     Threshold distortion algorithm
            //    ========================================================
        
            for (int chan=0; chan<buffer.getNumChannels(); chan++)
            {
                auto* data = buffer.getWritePointer(chan);
                
                for (int i=0; i < buffer.getNumSamples(); i++)
                {
                //            if(abs(data[i])>threshold) distorting = true;
                //            else distorting = false;
                    rdm =  r.nextFloat();
                    if(chan ==0){lAmountR = rdm * glitchAmount*(1-clipThreshold); valL =data[i];}
                    if(chan ==1){rAmountR = rdm * glitchAmount*(1-clipThreshold); valR =data[i];}
                    
                    if(data[i]>0)
                    {
                        if(data[i]>clipThreshold)
                        {
                           
                            
                            data[i] = clipThreshold + rdm *glitchAmount*(1-clipThreshold);
                            

                            
                        }
                    }
                    if(data[i]<0)
                    {
                        if(data[i]<-clipThreshold)
                        {
                            data[i] = -clipThreshold - rdm *glitchAmount*(1-clipThreshold);
                            
                        }
                    }
                    
                }
            }
        }
        
        //=====================================================================================

        if(distType == 1)
        {
        //    Full distortion algorithm
        //    ====================================================================================
        
            for (int chan=0; chan<buffer.getNumChannels(); chan++)
            {
                auto* data = buffer.getWritePointer(chan);
                
                for (int i=0; i < buffer.getNumSamples(); i++)
                {
                //            if(abs(data[i])>threshold) distorting = true;
                //            else distorting = false;
                    rdm = r.nextFloat();
                    
                    if(chan ==0){lAmountR = rdm * glitchAmount; valL =data[i];}
                    if(chan ==1){rAmountR = rdm * glitchAmount; valR =data[i];}
                    
                    
                    if(data[i]>0)
                    {
                        if(data[i]>clipThreshold)
                        {
                            data[i] =  rdm*glitchAmount;
                            
                        }
                    }
                    if(data[i]<0)
                    {
                        if(data[i]<-clipThreshold)
                        {
                            data[i] = -rdm*glitchAmount;
                            
                        }
                    }
                //         pan = abs(valR) - abs(valL);
                }
            }
        
        }
        //    ====================================================================================
        
        if(distType == 2)
        {
            //    Times distortion algorithm
            //    ====================================================================================
            
            for (int chan=0; chan<buffer.getNumChannels(); chan++)
            {
                auto* data = buffer.getWritePointer(chan);
                
                for (int i=0; i < buffer.getNumSamples(); i++)
                {
                    //                if(abs(data[i])>threshold) distorting = true;
                    //                else distorting = false;
                    rdm = r.nextFloat();
                    if(chan ==0){lAmountR = rdm * glitchAmount*data[i]; valL =data[i];}
                    if(chan ==1){rAmountR = rdm * glitchAmount*data[i]; valR =data[i];}
                    
                    
                    if(data[i]>0)
                    {
                        if(data[i]>clipThreshold)
                        {
                            data[i] =  rdm*glitchAmount*data[i];
                            
                        }
                    }
                    if(data[i]<0)
                    {
                        if(data[i]<-clipThreshold)
                        {
                            data[i] = -rdm*glitchAmount*data[i];
                            
                        }
                    }
                //                    pan = abs(valR) - abs(valL);
                }
            }
            
        }
    
    
    //OUTPUT
    for(int c = 0 ; c< totalNumInputChannels; ++c)
    {
        //read from here
        auto* channelData = buffer.getWritePointer (c);

        for(int s=0; s <buffer.getNumSamples();s++)
        {
         
          
            channelData[s] = channelData[s] * output;
            
        }
    }
    
    updateParam();
}

//==============================================================================
bool Sat2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Sat2AudioProcessor::createEditor()
{
    return new Sat2AudioProcessorEditor (*this);
}

//==============================================================================
void Sat2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = myVTS.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void Sat2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
       
       if (xmlState.get() != nullptr)
           if (xmlState->hasTagName (myVTS.state.getType()))
               myVTS.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Sat2AudioProcessor();

}

void Sat2AudioProcessor::updateParam()
{
 
    //gain parameters
     gain1 = 4* myVTS.getRawParameterValue("INPUT1")->load();
     gain1 = 1+std::pow(10, gain1);
     if(gain1<0.1) gain1 =0.1;

    
     gain2 = 4* myVTS.getRawParameterValue("INPUT2")->load();
    gain2 = 1+std::pow(10, gain2);
      if(gain2<0.1) gain2 =0.1;

     gain3 = 4* myVTS.getRawParameterValue("INPUT3")->load();
    gain3 = 1+std::pow(10, gain3);
      if(gain3<0.1) gain3 =0.1;


    //dry wet parameters
    
     dryWet1 =  myVTS.getRawParameterValue("DRYWET1")->load();
     dryWet2 =  myVTS.getRawParameterValue("DRYWET2")->load();
     dryWet3 =  myVTS.getRawParameterValue("DRYWET3")->load();
    
    output =  myVTS.getRawParameterValue("OUTPUT")->load();
    dryWet =  myVTS.getRawParameterValue("DRYWET")->load();
    
    clipThreshold = myVTS.getRawParameterValue("CLIPTHRESHOLD")->load();
    glitchAmount = myVTS.getRawParameterValue("GLITCHAMOUNT")->load();

    
}

AudioProcessorValueTreeState::ParameterLayout Sat2AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    //set parameters
    
    parameters.push_back(std::make_unique<AudioParameterFloat> ("INPUT1", "input1", 0.0f,1.0f,0.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("INPUT2", "input2", 0.0f,1.0f,0.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("INPUT3", "input3", 0.0f,1.0f,0.0f));
    
    parameters.push_back(std::make_unique<AudioParameterFloat> ("DRYWET1", "drywet1", 0.0f,1.0f,1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("DRYWET2", "drywet2", 0.0f,1.0f,1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("DRYWET3", "drywet3", 0.0f,1.0f,1.0f));
    
    parameters.push_back(std::make_unique<AudioParameterFloat> ("OUTPUT", "output", 0.0f,1.0f,1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("DRYWET", "drywet", 0.0f,1.0f,1.0f));
    
    parameters.push_back(std::make_unique<AudioParameterFloat> ("CLIPTHRESHOLD", "clipthreshold", 0.0f,1.0f,1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat> ("GLITCHAMOUNT", "glitchAMOUNT", 0.0f,1.0f,0.0f));
    
    
    
    return {parameters.begin(), parameters.end()};
}

void Sat2AudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    shouldUpdate = true;
}
