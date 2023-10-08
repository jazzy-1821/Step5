#include "pch.h"
#include "ToneInstrument.h"

CToneInstrument::CToneInstrument()
{
	m_duration = 0.1;
}

void CToneInstrument::Start()
{
	m_sinewave.SetSampleRate(GetSampleRate());
	m_sinewave.Start();
	m_time = 0;
}

bool CToneInstrument::Generate()
{
    // Tell the component to generate an audio sample
    m_sinewave.Generate();

    // Read the component's sample and make it our resulting frame.
    m_frame[0] = m_sinewave.Frame(0);
    m_frame[1] = m_sinewave.Frame(1);

    // Update time
    m_time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return m_time < m_duration;
}
