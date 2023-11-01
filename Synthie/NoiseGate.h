#pragma once
#include "Effects.h"

class NoiseGate:
    public Effects  // yahhh base class
{
    public:
        double ApplyNoiseGate(double inputSample);  // function to apply noise gate
};
