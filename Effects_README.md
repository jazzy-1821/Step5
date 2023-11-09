#### Herein lies the page describing the effects components

The classes that make up the effects portion of the program are listed below:  
Effects, Compression, Reverb, NoiseGate, and **TENTATIVELY** Flange.  

The Effects class is the base class for all 4 **currently 3 working** effects. "Effects" contains functions and member variables that all effects require (i.e. m_wet, m_dry to represent default wet/dry for all effects, SetWet, SetDry)  

##### Controllable Effects Send:  
I thought this deserved its own section.    
*in a perfect world, once I get this working:*  
The controllable effects work by reading in wet/dry values and any appropriate thresholds from the score. Even though I made my effects separate from CInstrument, the effects are still read in as if they are instruments. This was simply the easiest way to update the wet/dry/threshold values from the score (as the professor said in the project notes).  

*i.e.*  

if (effectType.CompareNoCase(L"Compression") == 0 || effectType.CompareNoCase(L"NoiseGate") == 0) {  
    threshold = getAttrAsDouble(L"threshold");  
}  

// Depending on the effect type, apply the values to the synthesizer's members  
if (effectType.CompareNoCase(L"Compression") == 0) {  
    m_compression.SetWetCOMP(wet);  
    m_compression.SetDryCOMP(dry);  
    m_compression.SetThreshCOMP(threshold);  
    effects_send[0] = true;  
}  
else if (effectType.CompareNoCase(L"NoiseGate") == 0) {  
    m_noiseGate.SetWetNG(wet);  
    m_noiseGate.SetDryNG(dry);  
    m_noiseGate.SetThreshNG(threshold);  
    effects_send[1] = true;  
}  
else if (effectType.CompareNoCase(L"Reverb") == 0) {  
    m_reverb.SetWetR(wet);  
    m_reverb.SetDryR(dry);  
    // Reverb does not use a threshold  
    effects_send[2] = true;  
}  

Here is an example from Synthesizer.cpp of me updating the wet/dry/threshod (if applicable) values from the score

#### Grading:  
10 - Component passes audio  
20 - 1 Effect  
30 - 3 Effects  
40 - Controllable effects send  
50 - 4 Effects  

Grading components I implemented:
+ 10 (Component passes audio)  
+ 20 (1 Effect)  - Reverb
+ 30 (3 Effects) - Compression, Noise Gate, Reverb
40 (Controllable effects send) **WORK IN PROGRESS**  
50 (4 Effects) **WORK IN PROGRESS**  
Current sum: **30 points**

The ___.score is score file for my effects. The ___.wav is the resulting wav file
