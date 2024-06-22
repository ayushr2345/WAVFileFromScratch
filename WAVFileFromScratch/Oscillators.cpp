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

    // Triangle Oscillator
    TriangleOscillator::TriangleOscillator(double amplitude, double frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {
        period = pow(frequency, -1);
    }

    double TriangleOscillator::GenerateSample(int n)
    {
        return amplitude *
               (4 / period) * 
               (n / static_cast<double>(g_SampleRate) -
                   (period / 2)*
                   (floor((2.0 * n / g_SampleRate / period) + (1.0 / 2))))*
               (pow(-1, (floor((2.0 * n / g_SampleRate / period) + (1.0 / 2)))));
    }

    // Sawtooth Oscillator
    SawtoothOscillator::SawtoothOscillator(double amplitude, double frequency) :
        amplitude{ amplitude },
        frequency{ frequency }
    {
        period = pow(frequency, -1);
    }

    double SawtoothOscillator::GenerateSample(int n)
    {
        return amplitude *
               2 *
               (static_cast<double>(n) / g_SampleRate / period -
                   (floor((static_cast<double>(n) / g_SampleRate / period))));
    }
} // namespace oscillators
