#include "Player.h"

PLAYER::PLAYER() {
	player1.num_coins = 0;
	player1.score = 0;
	player1.numLives = 3;
}

PLAYER::~PLAYER() {

}

bool PLAYER::checkFileExists() {
	std::ifstream file("PlayerStats.txt");
	return file.good();
}

void PLAYER::createPlayerStat() {
	std::ofstream file("PlayerStats.txt");

	if (file.is_open()) {
		file << "Number of Coins: " << player1.num_coins << "\n";
		file << "Score: " << player1.score << "\n";
		file << "Number of Lives: " << player1.numLives << "\n";
	}

	file.close();
}

void PLAYER::openPlayerStat() {
	std::ifstream file;

	//Open file
	file.open("PlayerStats.txt");
	if (file.is_open()) {
		std::string line;

		while (std::getline(file, line)) {
			//Extract Score
			if (line.find("Score: ") != std::string::npos) {
				int index = line.find(":");
				std::string number = line.substr(index + 1);
				int score = std::stoi(number);
				player1.score = score;
			}
			//Extract number of coins
			if (line.find("Number of Coins: ") != std::string::npos) {
				int index = line.find(":");
				std::string strToExtract = line.substr(index + 2);
				int numCoins = std::stoi(strToExtract);
				player1.num_coins = numCoins;
			}

			//Extract number of Lives
			if (line.find("Number of Lives: ") != std::string::npos) {
				int index = line.find(":");
				std::string strToExtract = line.substr(index + 2);
				int numLives = std::stoi(strToExtract);
				player1.numLives = numLives;
			}
		}
	}

	//Close file
	file.close();
}

void PLAYER::updatePlayerStat() {
	std::wostringstream debugString;

	std::ifstream currFile;
	std::ofstream newFile;

	//Open files
	currFile.open("PlayerStats.txt");
	newFile.open("temp.txt");

	if (currFile.is_open() && newFile.is_open()) {
		std::string string;
		
		while (std::getline(currFile, string)) {
			if (string.find("Score") != std::string::npos) {
				string = "Score: " + std::to_string(player1.score);
				newFile << string << "\n";
			}
			else {
				newFile << string << "\n";
			}
		}
	}

	//Close files
	currFile.close();
	newFile.close();

	//Rename and remove file
	std::remove("PlayerStats.txt");
	std::rename("temp.txt", "PlayerStats.txt");
}

void PLAYER::resetPlayerStat() {
	std::ofstream newFile;

	//Open new file
	newFile.open("temp.txt");
	if (newFile.is_open()) {
		player1.num_coins = 0;
		player1.score = 0;
		player1.numLives = 3;
		newFile << "Number of Coins: " << player1.num_coins << "\n";
		newFile << "Score: " << player1.score << "\n";
		newFile << "Number of Lives: " << player1.numLives << "\n";
	}

	//Close new file
	newFile.close();

	//Remove old file
	std::remove("PlayerStats.txt");
	std::rename("temp.txt", "PlayerStats.txt");
}