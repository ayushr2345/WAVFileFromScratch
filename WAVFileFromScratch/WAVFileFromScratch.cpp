#include <iostream>
#include <fstream>
#include "Oscillators.h"
#include "utils.h"

int main()
{
    float amplitude = 0.5;
    float frequency = 440;
    int   duration  = 5;

    // oscillators::SineOscillator sineOscillator(amplitude, frequency);
    // std::ofstream audioFile;
    // audioFile.open("SineWave.wav", std::ios::binary);

    // utils::WriteHeaderAndFormatChunk(audioFile);
    // utils::WriteDataChunk(audioFile, sineOscillator, duration);

    // audioFile.close();

    oscillators::SquareOscillator squareOscillator(amplitude, frequency);
    std::ofstream audioFile, audioFile1;
    audioFile.open("SquareWave.wav", std::ios::binary);
    audioFile1.open("SquareWave", std::ios::binary);

    utils::WriteHeaderAndFormatChunk(audioFile);
    
    // Data Chunk
        audioFile << "data";            // Marks the data chunk
        audioFile << "----";            // Size of data

        int preDataPosition = audioFile.tellp();
        for (int i = 0; i < duration * oscillators::g_SampleRate; i++)
        {
            auto sample = squareOscillator.GenerateSamples(i);
            int  intSample = static_cast<int>(sample * oscillators::g_MaxAmplitude);
            // std::cout << intSample << std::endl;
            utils::WriteToFile(audioFile, intSample, 2);
            audioFile1 << intSample << std::endl;
        }
        int postDataPosition = audioFile.tellp();

        audioFile.seekp(preDataPosition - 4);
        utils::WriteToFile(audioFile, postDataPosition - preDataPosition, 4);

        audioFile.seekp(4, std::ios::beg);
        utils::WriteToFile(audioFile, postDataPosition - 8, 4);

    audioFile.close();
    return 0;
}
