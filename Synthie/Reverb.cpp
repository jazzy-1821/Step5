#include "pch.h"
#include "Reverb.h"
#include <vector>

// Assuming a sample rate of 44.1 kHz
const int SAMPLE_RATE = 44100;
// Delay buffer length for 0.5 second delay
const int DELAY_BUFFER_LENGTH = SAMPLE_RATE / 2;
std::vector<double> delayBuffer(DELAY_BUFFER_LENGTH, 0);
// Write and read indexes for the circular buffer
int writeIndex = 0;
int readIndex = DELAY_BUFFER_LENGTH / 2; // 0.25 seconds delay

double Reverb::ApplyReverb(double inputSample) {
    // Read the sample from the delay buffer
    double delayedSample = delayBuffer[readIndex];

    // Mix the delayed sample with the input sample
    double mixedSample = (inputSample + delayedSample) * 0.5;

    // Write the input sample to the delay buffer
    delayBuffer[writeIndex] = inputSample;

    // Increment the write and read indexes and wrap them around if necessary
    writeIndex = (writeIndex + 1) % DELAY_BUFFER_LENGTH;
    readIndex = (readIndex + 1) % DELAY_BUFFER_LENGTH;

    // Return the mixed sample
    return (mixedSample * m_wet) + (inputSample * m_dry);  //mixedSample;
}