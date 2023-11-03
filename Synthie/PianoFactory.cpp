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

	/*instrument->SetDuration(m_duration);
	instrument->SetPedal(m_pedal);
	instrument->SetVolume(m_volume);

	if (m_pedalDown) {
		instrument->PlayPedalDown();
		m_playPedalDown = false;
	}
	if (m_PedalUp) {
		instrument->PlayPedalUp();
		m_playPedalUp = false;
	}

	return instrument;*/
	return nullptr;
}

void CPianoFactory::SetNote(CNote* note)
{
}
