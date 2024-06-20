#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace oscillators
{
    const int g_SampleRate   = 44100;
    const int g_BitDepth     = 16;
    const int g_MaxAmplitude = pow(2, g_BitDepth - 1) - 1;

    class IOscillator
    {
    public:
        IOscillator() = default;
        virtual float GenerateSamples() = 0;
    };

    class SineOscillator : public IOscillator
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
} // namespace oscillators
