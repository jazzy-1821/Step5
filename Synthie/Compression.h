#pragma once
#include "Effects.h"

class Compression:
    public Effects
{
    public:
        double ApplyCompression(double inputSample);  // function to apply Compression
        
        void SetWetCOMP(double wet) { m_wet_COMP = wet; }
        void SetDryCOMP(double dry) { m_dry_COMP = dry; }

    protected:
        double	m_wet_COMP = m_wet;  // giving each effects its own wet/dry now, defaults to Effects default (1,0)
        double	m_dry_COMP = m_dry;
};

