#include "utils.h"

int main()
{
	utils::PrintWelcomeScreen();
	utils::PrintMainMenu();

	double amplitude { 0.0 };
	double frequency { 0.0 };
	int    duration  { 0   };
	int    choice    { 0   };
	utils::InputNumberFromUser(choice, 1, (int)utils::MainMenu::MAX_COUNT);

	while (choice)
	{
		if (choice > utils::MainMenu::MIN_COUNT &&
			choice < utils::MainMenu::MAX_COUNT + 1)
		{
			utils::PrintSelectedChoice(choice);
		}
		switch (choice)
		{
		case 1:
		{
			utils::InputParametersFromUserMenuBased(
				frequency,
				amplitude,
				duration);
			
			oscillators::SineOscillator sineOscillator(amplitude, frequency);
			std::ofstream audioFile;
			
			std::string fileName = "Sine_" +
				utils::ConvertToStringWithPrecision<double>(frequency, 2) +
				"Hz_" +
				utils::ConvertToStringWithPrecision<double>(amplitude, 2) +
				"_" +
				std::to_string(duration) + "s.wav";

			audioFile.open(fileName, std::ios::binary);
			wavUtils::WriteHeaderAndFormatChunk(audioFile);
			wavUtils::WriteDataChunk(audioFile, sineOscillator, duration);
			
			audioFile.close();
			std::cout << "Sine wave generated successfully" << std::endl;
			break;
		}
		case 2:
		{
			utils::InputParametersFromUserMenuBased(
				frequency,
				amplitude,
				duration);

			oscillators::SquareOscillator squareOscillator(
				amplitude,
				frequency);
			std::ofstream audioFile;

			std::string fileName = "Square_" +
				utils::ConvertToStringWithPrecision<double>(frequency, 2) +
				"Hz_" +
				utils::ConvertToStringWithPrecision<double>(amplitude, 2) +
				"_" +
				std::to_string(duration) + "s.wav";

			audioFile.open(fileName, std::ios::binary);
			wavUtils::WriteHeaderAndFormatChunk(audioFile);
			wavUtils::WriteDataChunk(audioFile, squareOscillator, duration);

			audioFile.close();
			std::cout << "Square wave generated successfully" << std::endl;
			break;
		}
		case 3:
		{
			exit(0);
		}
		default:
			std::cout << "The selected option is out of bounds!!! "
					  << "Please select appropriate option: " << std::endl;
			break;
		}
		utils::PrintMainMenu();
		std::cin >> choice;
	}

	return 0;
}


