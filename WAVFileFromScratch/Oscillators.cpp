#include "Oscillators.h"
#include <iostream>

namespace oscillators
{
    // Sine Oscillator
    SineOscillator::SineOscillator(double amplitude, double frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {
        angle = 2 * M_PI * frequency / g_SampleRate;
    }

    double SineOscillator::GenerateSample(int n)
    {
        return  amplitude * sin(n * angle);
    }

    // Square Oscillator
    SquareOscillator::SquareOscillator(double amplitude, double frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {}

    double SquareOscillator::GenerateSample(int n)
    {
        return amplitude * pow(-1, floor(2 * frequency * n / g_SampleRate));
    }
} // namespace oscillators
