#include "pch.h"
#include "PianoFactory.h"
#include <string>
CPianoFactory::CPianoFactory()
{
	m_duration = 1.0;
	m_pedal = false;
	m_pedalDown = false;
	m_pedalUp = false;
}

CPianoFactory::~CPianoFactory()
{
}

CPianoInstrument* CPianoFactory::CreateInstrument()
{
	CPianoInstrument* instrument = new CPianoInstrument();

	instrument->SetDuration(m_duration);
	instrument->SetPedal(m_pedal);
	instrument->SetVelocity(m_velocity);

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
	// Get a list of all attribute nodes and the
// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			m_duration = value.dblVal;
		}
		else if (name == "pedal")
		{
			value.ChangeType(VT_BSTR);
			char pedal[100];
			wcstombs(pedal, value.bstrVal, 100);
			std::string pedal_str(pedal);

			if (pedal_str == "pressed") {
				m_pedalDown = true;
				m_pedal = true;
			}
			if (pedal_str == "released") {
				m_pedalUp = true;
				m_pedal = false;
			}
		}
		else if (name == "velocity")
		{
			value.ChangeType(VT_R8);
			m_velocity = value.dblVal;
		}

	}
}


