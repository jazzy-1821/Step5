#pragma once
#include "Effects.h"
class Reverb :
    public Effects
{
    public:
        double ApplyReverb(double inputSample);  // function to apply reverb
};

