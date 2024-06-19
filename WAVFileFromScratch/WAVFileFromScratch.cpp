#include <iostream>
#include <fstream>
#include "SineWave.h"

static void WriteToFile(std::ofstream& audioFile, int value, int size)
{
    audioFile.write(reinterpret_cast<const char*>(&value), size);
    // size is the number of bytes we want to write in the audio file
    // here size because int is 4 bytes and char is 1 byte maxAmplitude
    // is 32767 and samples will range from +32767 to -32767 which only 
    // needs 2 bytes of the 4 byte integer, hence only 2 bytes are 
    // written in the audio file
}

int main()
{
    float amplitude = 0.5;
    float frequency = 440;
    int   duration  = 5;
    int maxAmplitude = pow(2, oscillator::bitDepth - 1) - 1;

    oscillator::SineOscillator sineOscillator(amplitude, frequency);
    std::ofstream audioFile;
    audioFile.open("SineWave.wav", std::ios::binary);

    // Header Chunk
    audioFile << "RIFF";            // Marks the file as RIFF file
    audioFile << "----";            // Size of the overall file
    audioFile << "WAVE";            // File Type Header

    // Format Chunk
    audioFile << "fmt ";            // Format chunk marker
    WriteToFile(audioFile, 16, 4);  // Length of format data
    WriteToFile(audioFile, 1, 2);   // Compression code (PCM - 1)
    WriteToFile(audioFile, 1, 2);   // No of channels
    WriteToFile(                    // No of samples
        audioFile,
        oscillator::sampleRate,
        4
    );
    WriteToFile(                    // Byte rate
        audioFile,
        oscillator::sampleRate * oscillator::bitDepth * 1 / 8,
        4
    );
    WriteToFile(                    // Block align
        audioFile,
        oscillator::bitDepth * 1 / 8,
        2
    );
    WriteToFile(                    // Bit Depth   
        audioFile,
        oscillator::bitDepth,
        2
    );

    // Data Chunk
    audioFile << "data";            // Marks the data chunk
    audioFile << "----";            // Size of data

    int preDataPosition = audioFile.tellp();
    for (int i = 0; i < duration * oscillator::sampleRate; i++)
    {
        auto sample = sineOscillator.GenerateSamples();
        int  intSample = static_cast<int>(sample * maxAmplitude);
        WriteToFile(audioFile, intSample, 2);
    }
    int postDataPosition = audioFile.tellp();

    audioFile.seekp(preDataPosition - 4);
    WriteToFile(audioFile, postDataPosition - preDataPosition, 4);

    audioFile.seekp(4, std::ios::beg);
    WriteToFile(audioFile, postDataPosition - 8, 4);
    audioFile.close();
    return 0;
}
