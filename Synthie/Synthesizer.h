#pragma once
#include "msxml2.h"
#include <list>
#include <string>
#include <vector>
#include "Instrument.h"
#include "Note.h"
#include "Reverb.h"  // PROJECT 1
#include "Compression.h"  // PROJECT 1
#include "NoiseGate.h"  // PROJECT 1
#include "Flange.h"
#include "PianoFactory.h"
#include "xmlhelp.h"
#include <algorithm>
//#include <tinyxml2.h> // used for XmlLoadEffect
#pragma comment(lib, "msxml2.lib")
class CSynthesizer
{
public:
	CSynthesizer(void);
	virtual ~CSynthesizer(void);

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

	double GetBpm() { return m_bpm; }


	void Start(void);
	bool Generate(double* frame);

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	void Clear(void);

	void OpenScore(CString& filename);

	// PROJECT 1 EFFECTS
	NoiseGate m_noiseGate;
	Compression m_compression;
	Reverb m_reverb;
	//Flange m_flange;
	void XmlLoadEffect(IXMLDOMNode* effectNode);  // // ASHLIN ADDED FOR PROJECT 1


private:
	void XmlLoadScore(IXMLDOMNode* xml);
	void XmlLoadInstrument(IXMLDOMNode* xml);
	void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument, std::wstring& effect);
	void AddEffectToSynthesizer(Effects* effect);  // ASHLIN ADDED FOR PROJECT 1

	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double m_time;

	double  m_bpm;				//!< Beats per minute
	int     m_beatspermeasure;	//!< Beats per measure
	double  m_secperbeat;		//!< Seconds per beat

	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure

	bool effects_send[4];// = { false, false, false, false };  // order: compression, noisegate, reverb  <- initialized to false, false, false, false in XmlLoadInstrument?

	CPianoFactory m_pianoFactory;

	std::list<CInstrument*>  m_instruments;

	std::vector<CNote> m_notes;
};

