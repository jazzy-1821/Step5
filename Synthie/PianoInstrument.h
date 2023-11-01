#pragma once
#include "Instrument.h"
#include "Note.h"
#include "AR.h"
#include "WavePlayer.h"
#include <vector>

class CPianoInstrument :
    public CInstrument
{
public:
    CPianoInstrument();
    virtual ~CPianoInstrument();

	
	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote* note);
	bool LoadWaveFile(const char* filename);

private:
	//CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	std::vector<short> m_pedalWave;
};

