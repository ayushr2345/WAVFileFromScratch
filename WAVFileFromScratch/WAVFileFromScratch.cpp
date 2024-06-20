#include <iostream>
#include <fstream>
#include "Oscillators.h"
#include "utils.h"

int main()
{
    double amplitude = 0.5;
    double frequency = 440;
    int    duration  = 5;

    oscillators::SineOscillator sineOscillator(amplitude, frequency);
    std::ofstream audioFile;
    audioFile.open("SineWave.wav", std::ios::binary);

    utils::WriteHeaderAndFormatChunk(audioFile);
    utils::WriteDataChunk(audioFile, sineOscillator, duration);
    audioFile.close();

    oscillators::SquareOscillator squareOscillator(amplitude, frequency);
    std::ofstream audioFile1;
    audioFile1.open("SquareWave.wav", std::ios::binary);

    utils::WriteHeaderAndFormatChunk(audioFile1);
    utils::WriteDataChunk(audioFile1, squareOscillator, duration);
    audioFile1.close();

    return 0;
}
