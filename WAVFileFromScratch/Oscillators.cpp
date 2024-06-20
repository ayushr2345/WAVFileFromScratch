#include "Oscillators.h"

namespace oscillators
{
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
} // namespace oscillators
