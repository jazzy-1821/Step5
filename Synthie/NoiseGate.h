#pragma once
#include "Effects.h"

class NoiseGate:
    public Effects  // yahhh base class
{
    public:
        double ApplyNoiseGate(double inputSample);  // function to apply noise gate

        void SetWetNG(double wet) { m_wet_NG = wet; }
        void SetDryNG(double dry) { m_dry_NG = dry; }
        void SetThreshNG(double threshold) { thresh = threshold; }  // updates threshold from default value if diff value specified in score

    protected:
        double	m_wet_NG = m_wet;  // giving each effects its own wet/dry now, defaults to Effects default (1,0)
        double	m_dry_NG = m_dry;
        double thresh = 0.05;  // THRESHOLD, default value of 0.05
};
