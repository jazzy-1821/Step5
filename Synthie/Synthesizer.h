#pragma once
#include <list>
#include "Instrument.h"

using namespace std;

class CSynthesizer
{
public:
    CSynthesizer();

    void Start();

    bool Generate(double * frame);

    //! Number of audio channels
    int GetNumChannels() { return m_channels; }

    //! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

    //! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

    //! Get the time since we started generating audio
    double GetTime() { return m_time; }

private:
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;
    double m_time;
    std::list<CInstrument*>  m_instruments;
};

