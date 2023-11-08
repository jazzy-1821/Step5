#define _USE_MATH_DEFINES
#include "pch.h"
#include "Flange.h"
#include <cmath>

/*
Flange::Flange() {
    // Initialize Flange parameters (adjust as needed)
    m_readIndex = 0;
    for (int i = 0; i < 44100; ++i) {
        m_delayBuffer[i] = 0.0;
    }
}

double Flange::ApplyFlange(double inputSample, double time) {
    // Calculate modulation offset based on modulation rate
    double offset = 10.0 * sin(2 * M_PI * 0.25 * time);  // Adjust modulation rate as needed

    // Calculate the delayed sample index with the offset
    int writeIndex = (m_readIndex + static_cast<int>(44100 * offset)) % 44100;

    // Get the delayed sample from the delay buffer
    double delayedSample = m_delayBuffer[writeIndex];

    // Mix the input sample with the delayed sample
    double mixedSample = (inputSample + delayedSample) * 0.5;

    // Store the mixed sample in the delay buffer
    m_delayBuffer[m_readIndex] = mixedSample;

    // Increment read index and wrap around
    m_readIndex = (m_readIndex + 1) % 44100;

    // Return the mixed sample
    return (mixedSample * m_wet) + (inputSample * m_dry);
}*/