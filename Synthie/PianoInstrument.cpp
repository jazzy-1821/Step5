#include "pch.h"
#include "PianoInstrument.h"
#include "audio/DirSoundSource.h"

CPianoInstrument::CPianoInstrument()
{

}

CPianoInstrument::~CPianoInstrument()
{

}

void CPianoInstrument::Start()
{

}

bool CPianoInstrument::Generate()
{
	return false;
}

void CPianoInstrument::SetNote(CNote* note)
{

}

bool CPianoInstrument::LoadWaveFile(const char* filename)
{
	CDirSoundSource m_file;

	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i < m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_wave.push_back(frame[0]);
	}


	if (m_pedalWave.size() != 0) {
		for (unsigned int j = 0; j < m_pedalWave.size(); j++) {
			m_wave[j] += m_pedalWave[j];
		}
		m_pedalWave.clear();
	}

	m_file.Close();
	return true;
	return false;
}
