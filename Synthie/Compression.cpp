#include "pch.h"
#include "Compression.h"

double Compression::ApplyCompression(double inputSample) {
    // Apply compression effect logic
    // Modify the inputSample and return the processed sample
    // ...
    //double modifiedSample = inputSample;
    //return modifiedSample;
//}
    // Save the original inputSample for the dry signal
    double mixedSample = inputSample;

    //const double threshold = 0.5;  // Example threshold
    const double compressionRatio = 0.5;  // 50% volume reduction
    // Check if the inputSample exceeds the threshold
    if (inputSample > thresh) {
        // Apply compression by reducing the sample's magnitude by 50%
        mixedSample -= (inputSample - thresh) * compressionRatio;
    }
    else if (inputSample < -thresh) {
        // Apply compression to negative values as well
        mixedSample += (-inputSample - thresh) * compressionRatio;
    }

    // Return the possibly modified sample
    return (mixedSample * m_wet_COMP) + (inputSample * m_dry_COMP);
}