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
	void SetVelocity(double vel) { m_velocity = vel; }

	bool PedalDown();
	bool PedalUp();

	bool LoudSoftSample();


	CWavePlayer* GetWavePlayer() { return &m_wavePlayer; }

	std::vector<short> Interpolate(const std::vector<short>& soft, const std::vector<short>& loud, double velocity);

	void Envelope();

private:
	CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	std::vector<short> m_pedalWave;
	std::vector<short> m_loudSampleWave;
	std::vector<short> m_softSampleWave;
	double m_duration;
	double m_velocity;
	double m_time;
	double m_attack;
	double m_release;
	bool m_pedal;
	double m_decayTime;
	double m_sustainLevel;
	double m_amplitude; 
	double m_dampening;

};

