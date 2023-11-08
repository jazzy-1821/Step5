#include "pch.h"
#include "NoiseGate.h"
#include <cmath> // Include this for std::abs

// HARDCODED THRESHOLD FOR THE NOISEGATE... will update thresh in score???
//const double THRESHOLD = NoiseGate::thresh;//0.05;//NoiseGate::thresh;

double NoiseGate::ApplyNoiseGate(double inputSample) {

    double mixedSample;

    // The gate is open if the sample is louder than the threshold
    if (std::abs(inputSample) > thresh) {
        mixedSample = inputSample; // sample is loud enough to pass through the gate
    }
    else {
        mixedSample = 0.0; // sample is too quiet and gets silenced
    }

    // apply wet/dry mix
    return (mixedSample * m_wet_NG) + (inputSample * m_dry_NG);
}