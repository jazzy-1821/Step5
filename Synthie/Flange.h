#pragma once
#include "Effects.h"
class Flange :
    public Effects
{
    public:
        Flange();  // Constructor
        double ApplyFlange(double inputSample, double time);

    private:
        double m_delayBuffer[44100];  // Delay buffer for 1-second maximum delay (adjust as needed)
        int m_readIndex;

        // NEED TO ADD WET/DRY STUFF TO FLANGE
};
