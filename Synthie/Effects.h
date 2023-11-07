#pragma once
//#include "Instrument.h"
class Effects //:
//	public CInstrument  // rip Instrument base class
{
	public:
		void SetWet(double wet) { m_wet = wet; }
		void SetDry(double dry) { m_dry = dry; }

	protected:
		double	m_wet;
		double	m_dry;
};

