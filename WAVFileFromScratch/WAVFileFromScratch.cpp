#include <iostream>
#include <fstream>
#include "Oscillators.h"
#include "utils.h"

int main()
{
    float amplitude    = 0.5;
    float frequency    = 440;
    int   duration     = 5;

    oscillators::SineOscillator sineOscillator(amplitude, frequency);
    std::ofstream audioFile;
    audioFile.open("SineWave.wav", std::ios::binary);

    utils::WriteHeaderAndFormatChunk(audioFile);
    utils::WriteDataChunk(audioFile, sineOscillator, duration);

    audioFile.close();
    return 0;
}
