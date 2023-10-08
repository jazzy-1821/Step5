#include "pch.h"
#include "Synthesizer.h"

CSynthesizer::CSynthesizer() 
{
	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;
}
