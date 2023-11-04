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

	void SetPedal(bool pedal) { m_pedal = pedal; }
	void SetDuration(double d) { m_duration = d; }

	bool PedalDown();
	bool PedalUp();

	CWavePlayer* GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	std::vector<short> m_pedalWave;
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	bool m_pedal;
};

