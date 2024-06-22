#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace oscillators
{
    const int g_SampleRate   = 44100;
    const int g_BitDepth     = 16;
    const int g_MaxAmplitude = static_cast<int>(pow(2, g_BitDepth - 1) - 1);

    class IOscillator
    {
    public:
        IOscillator() = default;
        virtual double GenerateSample(int) = 0;
    };

    // Sine Oscillator
    class SineOscillator : public IOscillator
    {
    private:
        double amplitude { 0.0f };
        double frequency { 0.0f };
        double angle     { 0.0f };
    public:
        SineOscillator(double, double);
        double GenerateSample(int) override;
    };

    // Square Oscillator
    class SquareOscillator : public IOscillator
    {
    private:
        double amplitude { 0.0f };
        double frequency { 0.0f };
    public:
        SquareOscillator(double, double);
        double GenerateSample(int) override;
    };

    // Triangle Oscillator
    class TriangleOscillator : public IOscillator
    {
    private:
        double amplitude { 0.0f };
        double frequency { 0.0f };
        double period    { 0.0f };
    public:
        TriangleOscillator(double, double);
        double GenerateSample(int) override;
    };

    // SawtoothOscillator
    class SawtoothOscillator : public IOscillator
    {
    private:
        double amplitude{ 0.0f };
        double frequency{ 0.0f };
        double period{ 0.0f };
    public:
        SawtoothOscillator(double, double);
        double GenerateSample(int) override;
    };
} // namespace oscillators
