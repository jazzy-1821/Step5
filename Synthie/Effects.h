#pragma once
//#include "Instrument.h"
class Effects //:
//	public CInstrument  // rip Instrument base class
{
	public:
		Effects() : m_wet(0.5), m_dry(0.5) {}  // default 100% wet/dry

		//virtual double Process(double inputSample) = 0; // Pure virtual function for processing
		// ^ this gets replaced by process (add effects) function in each of the effects subclasses

		void SetWet(double wet) { m_wet = wet; }  // this will be the default wet/dry for each effect (1, 0) if they don't specify in score
		void SetDry(double dry) { m_dry = dry; }

	protected:
		double	m_wet;
		double	m_dry;
};

