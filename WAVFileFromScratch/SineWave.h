#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace oscillator
{
    const int sampleRate = 44100;
    const int bitDepth   = 16;

    class SineOscillator
    {
    private:
        float amplitude { 0.0f };
        float frequency{ 0.0f };
        float angle { 0.0f };
        float offset { 0.0f };
    public:
        SineOscillator(float, float);
        float GenerateSamples();
    };
} // namespace oscillator
