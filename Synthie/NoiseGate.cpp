#include "pch.h"
#include "NoiseGate.h"
#include <cmath> // Include this for std::abs

// Hardcoded threshold value (example: -40dB)
const double THRESHOLD = 0.01; // This is a linear scale, for dB you need to convert

double NoiseGate::ApplyNoiseGate(double inputSample) {
    // If the absolute value of the input is below the threshold, silence it
    double modifiedSample = (std::abs(inputSample) < THRESHOLD) ? 0.0 : inputSample;

    // Return the modified (or unmodified) sample
    return modifiedSample;
}