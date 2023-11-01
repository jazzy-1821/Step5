#pragma once
#include "Effects.h"

class Compression:
    public Effects
{
    public:
        double ApplyCompression(double inputSample);  // function to apply Compression
};

