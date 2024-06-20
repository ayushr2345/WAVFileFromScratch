#pragma once
#include <fstream>
#include "Oscillators.h"

namespace utils
{
    void WriteToFile(std::ofstream& audioFile, int value, int size)
    {
        audioFile.write(reinterpret_cast<const char*>(&value), size);
        // size is the number of bytes we want to write in the audio file
        // here size because int is 4 bytes and char is 1 byte maxAmplitude
        // is 32767 and samples will range from +32767 to -32767 which only 
        // needs 2 bytes of the 4 byte integer, hence only 2 bytes are 
        // written in the audio file
    }

    void WriteHeaderAndFormatChunk(std::ofstream& audioFile)
    {
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
            oscillators::g_SampleRate,
            4);
        WriteToFile(                    // Byte rate
            audioFile,
            oscillators::g_SampleRate * oscillators::g_BitDepth * 1 / 8,
            4);
        WriteToFile(                    // Block align
            audioFile,
            oscillators::g_BitDepth * 1 / 8,
            2);
        WriteToFile(                    // Bit Depth   
            audioFile,
            oscillators::g_BitDepth,
            2);
    }

    // Should only be called after calling the WriteHeaderAndFormatChunk method
    void WriteDataChunk(
        std::ofstream& audioFile,
        oscillators::IOscillator& oscillator,
        int duration)
    {
        // Data Chunk
        audioFile << "data";            // Marks the data chunk
        audioFile << "----";            // Size of data

        int preDataPosition = static_cast<int>(audioFile.tellp());
        for (int i = 0; i < duration * oscillators::g_SampleRate; i++)
        {
            auto sample = oscillator.GenerateSample(i);
            int  intSample = static_cast<int>(
                sample * oscillators::g_MaxAmplitude);

            WriteToFile(audioFile, intSample, 2);
        }
        int postDataPosition = static_cast<int>(audioFile.tellp());

        audioFile.seekp(preDataPosition - 4);
        WriteToFile(audioFile, postDataPosition - preDataPosition, 4);

        audioFile.seekp(4, std::ios::beg);
        WriteToFile(audioFile, postDataPosition - 8, 4);
    }
} // namespace utils
