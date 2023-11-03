#pragma once
#include "PianoInstrument.h"

class CPianoFactory
{
public:
	CPianoFactory();
	virtual ~CPianoFactory();

	CPianoInstrument* CreateInstrument();
	void SetNote(CNote* note);

};

