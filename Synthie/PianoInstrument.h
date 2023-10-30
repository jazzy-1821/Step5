#pragma once
#include "Instrument.h"
#include "AR.h"

class CPianoInstrument :
    public CInstrument
{
public:
    CPianoInstrument();
    virtual ~CPianoInstrument();

	/*
	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote* note);*/
};

