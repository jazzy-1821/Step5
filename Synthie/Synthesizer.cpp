#include "pch.h"
//#include "StdAfx.h"
#include "Synthesizer.h"
#include <cmath>
#include <string>
#include "ToneInstrument.h"
#include "xmlhelp.h"


using namespace std;

CSynthesizer::CSynthesizer(void)
{
    CoInitialize(NULL);

    m_channels = 2;
    m_sampleRate = 44100.;
    m_samplePeriod = 1 / m_sampleRate;
    m_time = 0;

    m_bpm = 120;
    m_secperbeat = 0.5;
    m_beatspermeasure = 4;
}


CSynthesizer::~CSynthesizer(void)
{
}

void CSynthesizer::Clear(void)
{
    m_instruments.clear();
    m_notes.clear();
}


void CSynthesizer::OpenScore(CString& filename)
{
    Clear();

    //
    // Create an XML document
    //

    CComPtr<IXMLDOMDocument>  pXMLDoc;
    bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
        IID_IXMLDOMDocument, (void**)&pXMLDoc));
    if (!succeeded)
    {
        AfxMessageBox(L"Failed to create an XML document to use");
        return;
    }

    // Open the XML document
    VARIANT_BOOL ok;
    succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
    if (!succeeded || ok == VARIANT_FALSE)
    {
        AfxMessageBox(L"Failed to open XML score file");
        return;
    }

    //
    // Traverse the XML document in memory!!!!
    // Top level tag is <score>
    //

    CComPtr<IXMLDOMNode> node;
    pXMLDoc->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR nodeName;
        node->get_nodeName(&nodeName);

        if (nodeName == "score")
        {
            XmlLoadScore(node);
        }
    }

    sort(m_notes.begin(), m_notes.end());
}


void CSynthesizer::XmlLoadScore(IXMLDOMNode* xml)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == L"bpm")
        {
            value.ChangeType(VT_R8);
            m_bpm = value.dblVal;
            m_secperbeat = 1 / (m_bpm / 60);
        }
        else if (name == L"beatspermeasure")
        {
            value.ChangeType(VT_I4);
            m_beatspermeasure = value.intVal;
        }
    }


    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if (name == L"instrument")
        {
            XmlLoadInstrument(node);
        }

        if (name == L"effects")
        {
            XmlLoadEffect(node);
        }
    }
}

void CSynthesizer::XmlLoadInstrument(IXMLDOMNode* xml)
{
    wstring instrument = L"";
    wstring effect = L"";

    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        // Get the value of the attribute.  
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "instrument")
        {
            instrument = value.bstrVal;
        }
        else if (name == "effect")
        {
            effect = value.bstrVal;
        }
    }


    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if (name == L"note")
        {
            XmlLoadNote(node, instrument, effect);
        }
    }
}

///
/// ASHLIN ADDED FOR PROJECT 1 EFFECTS PROCESSING FROM SCORE
/// 
void CSynthesizer::XmlLoadEffect(IXMLDOMNode* effectNode) {
    // Check the effectNode for validity
    if (effectNode == nullptr) {
        // Handle the error appropriately
        return;
    }

    BSTR nodeName;
    effectNode->get_nodeName(&nodeName);
    CString effectType(nodeName, SysStringLen(nodeName));
    SysFreeString(nodeName);

    // Helper lambda function to get attribute value as double
    auto getAttrAsDouble = [effectNode](const wchar_t* attrName) -> double {
        double value = 0;
        IXMLDOMNamedNodeMap* attributes;
        effectNode->get_attributes(&attributes);
        if (attributes) {
            IXMLDOMNode* attrNode;
            BSTR bstrAttrName = SysAllocString(attrName);
            attributes->getNamedItem(bstrAttrName, &attrNode);
            SysFreeString(bstrAttrName);
            if (attrNode) {
                VARIANT varValue;
                attrNode->get_nodeValue(&varValue);
                if (varValue.vt == VT_BSTR) {
                    value = _wtof(varValue.bstrVal);
                }
                VariantClear(&varValue);
                attrNode->Release();
            }
            attributes->Release();
        }
        return value;
     };


    // Extract the values from the node
    double wet = getAttrAsDouble(L"wet");
    double dry = getAttrAsDouble(L"dry");
    double threshold = 0; // Default to 0, will be set only for compression and noisegate

    if (effectType.CompareNoCase(L"Compression") == 0 || effectType.CompareNoCase(L"NoiseGate") == 0) {
        threshold = getAttrAsDouble(L"threshold");
    }

    // Depending on the effect type, apply the values to the synthesizer's members
    if (effectType.CompareNoCase(L"Compression") == 0) {
        m_compression.SetWetCOMP(wet);
        m_compression.SetDryCOMP(dry);
        m_compression.SetThreshCOMP(threshold);
        effects_send[0] = true;
    }
    else if (effectType.CompareNoCase(L"NoiseGate") == 0) {
        m_noiseGate.SetWetNG(wet);
        m_noiseGate.SetDryNG(dry);
        m_noiseGate.SetThreshNG(threshold);
        effects_send[1] = true;
    }
    else if (effectType.CompareNoCase(L"Reverb") == 0) {
        m_reverb.SetWetR(wet);
        m_reverb.SetDryR(dry);
        // Reverb does not use a threshold
        effects_send[2] = true;
    }
}


void CSynthesizer::XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument, std::wstring& effect)
{
    m_notes.push_back(CNote());
    m_notes.back().XmlLoad(xml, instrument, effect);
}


//! Start the synthesizer
void CSynthesizer::Start(void)
{
    m_instruments.clear();
    m_currentNote = 0;
    m_measure = 0;
    m_beat = 0;
    m_time = 0;
    effects_send[0] = false;
    effects_send[1] = false;
    effects_send[2] = false;
    effects_send[3] = false;
}

//! Generate one audio frame
bool CSynthesizer::Generate(double* frame)
{
    //
    // Phase 1: Determine if any notes need to be played.
    //

    bool effects_send[] = { true, true, true, true };  // starts as false, set to true for each effect added in score

    while (m_currentNote < (int)m_notes.size())
    {
        // Get a pointer to the current note
        CNote* note = &m_notes[m_currentNote];

        // If the measure is in the future we can't play
        // this note just yet.
        if (note->Measure() > m_measure)
            break;

        // If this is the current measure, but the
        // beat has not been reached, we can't play
        // this note.
        if (note->Measure() == m_measure && note->Beat() > m_beat)
            break;

        //
        // Play the note!
        //

        // Create the instrument object
        CInstrument* instrument = NULL;

        if (note->Instrument() == L"ToneInstrument")
        {
            instrument = new CToneInstrument();
        }

        else if (note->Instrument() == L"PianoInstrument")
        {
            m_pianoFactory.SetNote(note);
            instrument = m_pianoFactory.CreateInstrument();
        }

        //
        // PROJECT 1: ASHLIN UPDATE EFFECTS FROM SCORE
        //
        else if (note->Effects() == L"Compression")
        {
            effects_send[0] = true;
        }
        else if (note->Effects() == L"NoiseGate")
        {
            effects_send[1] = true;
        }
        else if (note->Effects() == L"Reverb")
        {
            effects_send[2] = true;
        }
        

        // Configure the instrument object
        if (instrument != NULL)
        {
            instrument->SetSampleRate(GetSampleRate());
            instrument->SetBpm(GetBpm());
            instrument->SetNote(note);
            instrument->Start();
            


            m_instruments.push_back(instrument);
        }

        m_currentNote++;
    }

    //
    // Phase 2: Clear all channels to silence 
    //

    for (int c = 0; c < GetNumChannels(); c++)
    {
        frame[c] = 0;
    }

    //
    // Phase 3: Play an active instruments
    //

    //
    // We have a list of active (playing) instruments.  We iterate over 
    // that list.  For each instrument we call generate, then add the
    // output to our output frame.  If an instrument is done (Generate()
    // returns false), we remove it from the list.
    //

    for (list<CInstrument*>::iterator node = m_instruments.begin(); node != m_instruments.end(); )
    {
        // Since we may be removing an item from the list, we need to know in 
        // advance, what is after it in the list.  We keep that node as "next"
        list<CInstrument*>::iterator next = node;
        next++;

        // Get a pointer to the allocated instrument
        CInstrument* instrument = *node;

        // Call the generate function
        if (instrument->Generate())
        {
            // If we returned true, we have a valid sample.  Add it 
            // to the frame.
            for (int c = 0; c < GetNumChannels(); c++)
            {
                frame[c] += instrument->Frame(c);
            }
        }
        else
        {
            // If we returned false, the instrument is done.  Remove it
            // from the list and delete it from memory.
            m_instruments.erase(node);
            delete instrument;
        }

        // Move to the next instrument in the list
        node = next;
    }

    //
    // PHASE 3a: add effects
    // 

    // order =  compress, noisegate, reverb, 4th effect

    // ADD LOOP/LOGIC TO UPDATE EFFECTS_SEND

    for (int c = 0; c < GetNumChannels(); c++)
    {
        double processedFrame = frame[c];

        // Apply effects in the order they were added if they are set to be used
        if (effects_send[0]) processedFrame = m_compression.ApplyCompression(processedFrame);
        if (effects_send[1]) processedFrame = m_noiseGate.ApplyNoiseGate(processedFrame);
        if (effects_send[2]) processedFrame = m_reverb.ApplyReverb(processedFrame);
        //if (effects_send[4]) processedFrame = m_reverb.ApplyFlange(processedFrame);

        // Now, write the processed frame back to the frame buffer
        frame[c] = processedFrame;
    }
 
    //
    // Phase 4: Advance the time and beats
    //

    // Time advances by the sample period
    m_time += GetSamplePeriod();

    // Beat advances by the sample period divided by the 
    // number of seconds per beat.  The inverse of seconds
    // per beat is beats per second.
    m_beat += GetSamplePeriod() / m_secperbeat;

    // When the measure is complete, we move to
    // a new measure.  We might be a fraction into
    // the new measure, so we subtract out rather 
    // than just setting to zero.
    if (m_beat > m_beatspermeasure)
    {
        m_beat -= m_beatspermeasure;
        m_measure++;
    }

    //
    // Phase 5: Determine when we are done
    //

    // We are done when there is nothing to play.  We'll put something more 
    // complex here later.
    return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}

