#pragma once
#include "Effects.h"

class Compression:
    public Effects
{
    public:
        double ApplyCompression(double inputSample);  // function to apply Compression
        
        void SetWetCOMP(double wet) { m_wet_COMP = wet; }
        void SetDryCOMP(double dry) { m_dry_COMP = dry; }
        void SetThreshCOMP(double threshold) { thresh = threshold; }  // updates threshold from default value if diff value specified in score

    protected:
        double	m_wet_COMP = m_wet;  // giving each effects its own wet/dry now, defaults to Effects default (1,0)
        double	m_dry_COMP = m_dry;
        double thresh = 0.5;
};

