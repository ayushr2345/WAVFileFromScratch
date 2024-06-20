#include "Oscillators.h"
#include <iostream>

namespace oscillators
{
    // Sine Oscillator
    SineOscillator::SineOscillator(float amplitude, float frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {
        offset = 2 * M_PI * frequency / g_SampleRate;
    }

    float SineOscillator::GenerateSamples()
    {
        auto sample = amplitude * sin(angle);
        angle += offset;
        return sample;
    }

    // Square Oscillator
    SquareOscillator::SquareOscillator(float amplitude, float frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {}

    float SquareOscillator::GenerateSamples(int n)
    {
        return amplitude * pow(-1, floor(2 * frequency * n / g_SampleRate));
    }
} // namespace oscillators
