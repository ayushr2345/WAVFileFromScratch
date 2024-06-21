#include <iomanip>
#include "utils.h"

namespace utils
{
	void PrintWelcomeScreen()
	{
		std::cout << std::setw(100) 
				  << "#################### WELCOME ####################"
				  << std::endl;
		std::cout << "Welcome to Writing WAV File from scratch"
				  << "Select from the options given below" << std::endl;
	}

	void PrintMainMenu()
	{
		std::cout << std::endl;
		for (std::map<int, std::string>::iterator it = MainMenuMap.begin();
			it != MainMenuMap.end();
			it++)
		{
			std::cout << it->first << ". " << it->second << std::endl;
		}
		std::cout << "Please enter your choice: ";
	}

	void PrintSecondaryMenu()
	{
		std::cout << "Choose if you want defaults or manual parameters of the"
				  << " wave:" << std::endl;
		std::cout << "1. Default Parameters (f = 440 Hz, A = 0.5, t = 5s)"
				  << std::endl;
		std::cout << "2. Enter the parameters manually" << std::endl;
		std::cout << "3. Go back and select another type of wave" << std::endl;
	}

	void PrintSelectedChoice(const int& choice)
	{
		std::cout << std::endl << std::endl
			      << "You have chosen choice "
			      << MainMenuMap.at(choice)
			      << std::endl;
	}

	void ClearCinFlag()
	{
		// Clear cin error flag so that further operations can be performed accurately
		std::cin.clear();
	}

	void IgnoreStdCinBufferTillEOL()
	{
		// ignore the input stream till the EOL
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	bool CheckAndClearCharactersInStream(const char str[], const int len)
	{
		if (std::cin.gcount() == (static_cast<long long>(len) - 1) &&
			strlen(str) == (static_cast<unsigned long long>(len) - 1))
		{
			// there are characters in the stream before '\n'
			ClearCinFlag();
			IgnoreStdCinBufferTillEOL();
			return true;
		}
		return false;
	}

	void InputParametersFromUser(
		double& frequency,
		double& amplitude,
		int& duration)
	{
		std::cout << "Please enter the amplitude, frequency and duration of"
			      << "the wave : " << std::endl;
		
		std::cout << "1. Frequency (A4 --> 440Hz): ";
		InputNumberFromUser<double>(frequency, 20, 1000);

		std::cout << "2. Amplitude (0 - 1): ";
		InputNumberFromUser<double>(amplitude, 0, 1);

		std::cout << "3. Duration in seconds (1 - 5): ";
		InputNumberFromUser<int>(duration, 1, 5);

		std::cout << amplitude << " " << frequency << " " << duration << std::endl;
	}

	void SetParameterDefaults(
		double& frequency,
		double& amplitude,
		int& duration)
	{
		frequency = 440;
		amplitude = 0.5;
		duration  = 5;
	}
	
	void InputParametersFromUserMenuBased(
		double& frequency,
		double& amplitude,
		int& duration)
	{
		int secondaryChoice{ 0 };
		utils::PrintSecondaryMenu();
		std::cout << "Please select one from the above: ";
		utils::InputNumberFromUser<int>(secondaryChoice, 1, 2);

		if (secondaryChoice == 1)
		{
			utils::SetParameterDefaults(frequency, amplitude, duration);
		}
		else
		{
			utils::InputParametersFromUser(frequency, amplitude, duration);
		}
	}
} // namespace utils

namespace wavUtils
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
} // namespace wavUtils
