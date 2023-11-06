#include "pch.h"
#include "NoiseGate.h"
#include <cmath> // Include this for std::abs

const double THRESHOLD = 0.01;  // std::pow(10.0, THRESHOLD_dB / 20.0); // Convert dB to linear

double NoiseGate::ApplyNoiseGate(double inputSample) {

    // The gate is open if the sample is louder than the threshold
    if (std::abs(inputSample) > THRESHOLD) {
        // The sample is loud enough to pass through the gate
        return inputSample;
    }
    else {
        // The sample is too quiet and gets silenced
        return 0.0;
    }
}