#include "pch.h"
#include "Compression.h"

double Compression::ApplyCompression(double inputSample) {
    // Apply compression effect logic
    // Modify the inputSample and return the processed sample
    // ...
    //double modifiedSample = inputSample;
    //return modifiedSample;
//}
    const double threshold = 0.5;  // Example threshold
    const double compressionRatio = 0.5;  // 50% volume reduction
    // Check if the inputSample exceeds the threshold
    if (inputSample > threshold) {
        // Apply compression by reducing the sample's magnitude by 50%
        inputSample -= (inputSample - threshold) * compressionRatio;
    }
    else if (inputSample < -threshold) {
        // Apply compression to negative values as well
        inputSample += (-inputSample - threshold) * compressionRatio;
    }

    // Return the possibly modified sample
    return inputSample;
}