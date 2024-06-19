#include "SineWave.h"

namespace oscillator
{
    SineOscillator::SineOscillator(float amplitude, float frequency) :
        amplitude { amplitude },
        frequency { frequency }
    {
        offset = 2 * M_PI * frequency / sampleRate;
    }

    float SineOscillator::GenerateSamples()
    {
        auto sample = amplitude * sin(angle);
        angle += offset;
        return sample;
    }
} // namespace oscillator
