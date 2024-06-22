#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Oscillators.h"

#ifndef _WIN32
#include <limits>
#include <cstring>
#endif	


namespace utils
{
	enum MainMenu
	{
		MIN_COUNT     = 0,
		SINE_WAVE     = 1,
		SQUARE_WAVE   = 2,
		TRIANGLE_WAVE = 3,
		SAWTOOTH_WAVE = 4,
		EXIT		  = 5,
		MAX_COUNT     = EXIT
	};

	// Used so that this MainMenuArray is available to the main.cpp
	// and we can print the selected choice.
	static std::map<int, std::string> MainMenuMap =
	{
		{
			MainMenu(SINE_WAVE),
			std::string("Sine Wave")
		},
		{
			MainMenu(SQUARE_WAVE),
			std::string("Square Wave")
		},
		{
			MainMenu(TRIANGLE_WAVE),
			std::string("Triangle Wave")
		},
		{
			MainMenu(SAWTOOTH_WAVE),
			std::string("Sawtooth Wave")
		},
		{
			MainMenu(EXIT),
			std::string("Exit from program")
		}
	};

	void PrintWelcomeScreen();
	void PrintMainMenu();
	void PrintSecondaryMenu();
	void PrintSelectedChoice(const int&);
	void ClearCinFlag();
	void IgnoreStdCinBufferTillEOL();
	bool CheckAndClearCharactersInStream(const char[], const int);

	// templates should not have definition in a separate source file 
	// as it would give compilation and linking errors
	template<typename T>
	void InputNumberFromUser(
		T& choice,
		T range_start = std::numeric_limits<T>::min(),
		T range_stop = std::numeric_limits<T>::max())
	{
		std::cin >> choice;
		while (std::cin.fail() ||
			   std::cin.peek() != '\n' ||
			   choice < range_start ||
			   choice > range_stop)
		{
			ClearCinFlag();
			IgnoreStdCinBufferTillEOL();
			std::cout << "Wrong input type!";
			std::cout << "Please enter a value within range : "
				      << range_start << " to " << range_stop << ": ";
			std::cin >> choice;
		}
	}
	void InputParametersFromUser(double&, double&, int&);
	void SetParameterDefaults(double&, double&, int&);
	bool InputParametersFromUserMenuBased(double&, double&, int&);

	template <typename T>
	std::string ConvertToStringWithPrecision(const T value, const int n = 6)
	{
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << value;
		return std::move(out).str();
	}
} //namespace utils

namespace wavUtils
{
    void WriteToFile(std::ofstream& audioFile, int value, int size);
	void WriteHeaderAndFormatChunk(std::ofstream& audioFile);

    // Should only be called after calling WriteHeaderAndFormatChunk method
	void WriteDataChunk(std::ofstream&, oscillators::IOscillator&, int);
} // namespace wavUtils
