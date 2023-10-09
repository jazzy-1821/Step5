#pragma once
#include "AudioNode.h"
#include "Note.h"
class CInstrument :
    public CAudioNode
{
public:
    virtual void SetNote(CNote* note) = 0;
};

