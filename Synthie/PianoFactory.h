#pragma once
#include "PianoInstrument.h"

class CPianoFactory
{
public:
	CPianoFactory();
	virtual ~CPianoFactory();

	CPianoInstrument* CreateInstrument();
	void SetNote(CNote* note);



private:
	double m_duration;
	double m_velocity;
	bool m_pedal;
	bool m_pedalUp;
	bool m_pedalDown;

	
};

