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
	void SetDuration(double dur) { m_duration = dur; }
	void SetDynamic(double dyn) { m_dynamic = dyn; }

	bool PedalDown();
	bool PedalUp();

	CWavePlayer* GetWavePlayer() { return &m_wavePlayer; }

	void ChangeDuration();

	void Envelope();

private:
	CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	std::vector<short> m_pedalWave;
	double m_duration;
	double m_dynamic;
	double m_time;
	double m_attack;
	double m_release;
	bool m_pedal;
	double m_decayTime;
	double m_sustainLevel;
	double m_amplitude; 
	double m_dampening;

};

