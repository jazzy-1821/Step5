#pragma once
#include "Effects.h"
class Reverb :
    public Effects
{
    public:
        double ApplyReverb(double inputSample);  // function to apply reverb

        void SetWetNG(double wet) { m_wet_R = wet; }
        void SetDryNG(double dry) { m_dry_R = dry; }

    protected:
        double	m_wet_R = m_wet;  // giving each effects its own wet/dry now, defaults to Effects default (1,0)
        double	m_dry_R = m_dry;
};

