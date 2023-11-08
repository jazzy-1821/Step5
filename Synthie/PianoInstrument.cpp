#include "pch.h"
#include "PianoInstrument.h"
#include "audio/DirSoundSource.h"
#include <algorithm>

CPianoInstrument::CPianoInstrument()
{
	m_attack = 0.05;
	m_release = 0.25;
	m_time = 0.0;
	m_decayTime = 0.01;
	m_sustainLevel = 0.55;
	m_duration = 1.0;
	m_amplitude = 0.0;
	m_velocity = 60.0; // Set the press velocity to a moderate velocity
	m_dampening = 1.0;
	m_pedal = false;
}

CPianoInstrument::~CPianoInstrument()
{

}

void CPianoInstrument::Start()
{
	m_wavePlayer.SetSampleRate(GetSampleRate());
	m_wavePlayer.Start();
}

bool CPianoInstrument::Generate()
{
	bool valid = m_wavePlayer.Generate();

	m_frame[0] = m_wavePlayer.Frame(0);
	m_frame[1] = m_frame[0];
	return valid;
}

void CPianoInstrument::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "note")
		{
			value.ChangeType(VT_BSTR);
			char filename[100];
			wcstombs(filename, value.bstrVal, 100);
			LoadWaveFile(filename);

		}
	}

	m_duration += m_release;

	Envelope();
	this->GetWavePlayer()->SetSamples(&m_wave[0], (int)m_wave.size());
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

	if (m_interpolatedWave.size() != 0)
	{
		for (unsigned int j = 0; j < m_interpolatedWave.size(); j++) {
			m_wave[j] += m_interpolatedWave[j];
		}
		m_interpolatedWave.clear();
	}

	if (m_pedalWave.size() != 0) {
		for (unsigned int j = 0; j < m_pedalWave.size(); j++) {
			m_wave[j] += m_pedalWave[j];
		}
		m_pedalWave.clear();
	}

	m_file.Close();
	return true;
}

bool CPianoInstrument::PedalDown()
{
	CDirSoundSource m_file;

	char filename[] = "CompletePiano/pedald.wav";


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
		m_pedalWave.push_back(frame[0]);
	}

	m_file.Close();
	return true;
}

bool CPianoInstrument::PedalUp()
{
	CDirSoundSource m_file;

	char filename[] = "CompletePiano/pedalu.wav";

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
		m_pedalWave.push_back(frame[0]);
	}

	m_file.Close();
	return true;
}

bool CPianoInstrument::LoudSample()
{
	CDirSoundSource m_file;

	char filename[] = "CompletePiano/LoudPianoString.wav";

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
		m_loudSampleWave.push_back(frame[0]);
	}
	m_file.Close();
	return true;
}

bool CPianoInstrument::SoftSample()
{
	CDirSoundSource m_file;

	char filename[] = "CompletePiano/SoftPianoString.wav";

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
		m_softSampleWave.push_back(frame[0]);
	}

	m_file.Close();
	return true;
}

void CPianoInstrument::Interpolate(const std::vector<short>& soft, const std::vector<short>& loud, double velocity) {


	for (size_t i = 0; i < soft.size(); i++) {
		double softSample = soft[i] / 32767.0;
		double loudSample = loud[i] / 32767.0;
		double interpolatedSample = (loudSample - softSample) / 2  * (m_velocity / 127.0);

		// Ensure the amplitude is within the range [-1, 1]
		//interpolatedSample = std::max(-1.0, std::min(1.0, interpolatedSample));

		// Convert back to short

		m_interpolatedWave.push_back(static_cast<short>(interpolatedSample * 32767));
	}

}


// Used past ramp example and ChatGPT to help include the sustain and decay in the envelope function
void CPianoInstrument::Envelope()
{
	double changed_wave;
	double m_ramp;
	double m_duration = m_wave.size() / 44100.;

	for (unsigned int i = 0; i < m_wave.size(); i++, m_time += 1 / 44100.)
	{
		if (!m_pedal) {
			if (m_time <= m_attack) {
				// Attack phase
				m_ramp = 1.0 - exp(-5.0 * m_time / m_attack) * (m_velocity / 127.0);
			}
			else if (m_time <= m_attack + m_decayTime) {
				// Decay phase
				m_ramp = m_sustainLevel + (1.0 - m_sustainLevel) * (1.0 - exp(-5.0 * (m_time - m_attack) / m_decayTime)) *(m_velocity / 127.0);
			}
			else {
				// Sustain phase
				m_ramp = m_sustainLevel * (m_velocity / 127.0);
			}
		}
		else {
			// Pedal is pressed, so sustain indefinitely
			m_ramp = 1.0;
		}

		// Continue with the release phase if the pedal is not pressed
		if (!m_pedal && m_time > (m_duration - m_release)) {
			// Release phase
			m_ramp *= exp(-5.0 * (m_time - (m_duration - m_release)) / m_release) * (m_velocity / 127.0);
		}

		changed_wave = m_wave[i] * m_ramp;
		m_wave[i] = short(changed_wave);
	}
}


