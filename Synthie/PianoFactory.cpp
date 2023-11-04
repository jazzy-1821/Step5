#include "pch.h"
#include "PianoFactory.h"

CPianoFactory::CPianoFactory()
{
}

CPianoFactory::~CPianoFactory()
{
}

CPianoInstrument* CPianoFactory::CreateInstrument()
{
	CPianoInstrument* instrument = new CPianoInstrument();

	instrument->SetDuration(m_duration);
	instrument->SetPedal(m_pedal);

	if (m_pedalDown) {
		instrument->PedalDown();
		m_pedalDown = false;
	}
	if (m_pedalUp) {
		instrument->PedalUp();
		m_pedalUp = false;
	}

	return instrument;
}

void CPianoFactory::SetNote(CNote* note)
{
}
