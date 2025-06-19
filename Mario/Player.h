#ifndef PLAYER_H_
#define PLAYER_H_

#include "AllHeaderFiles.h"
#include <fstream>

class MAINMENU;

class PLAYER {
	friend class MAINMENU;

public:
	static PLAYER& getInstance() {
		static PLAYER instance;
		return instance;
	}
	bool checkFileExists();
	void createPlayerStat();
	void openPlayerStat();
	void updatePlayerStat();
	void resetPlayerStat();

private:
	//Singleton
	PLAYER();
	~PLAYER();

	PLAYER(const PLAYER&) = delete;
	PLAYER& operator = (const PLAYER&) = delete;

	struct PlayerStatsStruct{
		int score;
		int num_coins;
		int numLives;
	};
	PlayerStatsStruct player1;
};

#endif // !PLAYER_H_
