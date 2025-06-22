#ifndef GAME_H_
#define GAME_H_

#include "AllHeaderFiles.h"

class GameObjects;
class Grid;
class MARIO;
class BACKGROUND;

class GAME {
public:
	GAME();
	void initGame(ID3D11Device* dev, ID3D11DeviceContext *devCon);
	void updateGame(ID3D11DeviceContext* devCon, float frame_time);
	void renderGame(ID3D11DeviceContext* devCon, float time);
	void cleanGame();

private:
	std::vector<std::shared_ptr<BACKGROUND>> backgroundArray;
	std::vector<std::shared_ptr<GameObjects>> gameObjectsArray;
	std::shared_ptr<Grid>grids;
	MARIO *Mario;

	DirectX::SpriteBatch *gameSpriteBatch;
	DirectX::SpriteFont *gameSpriteFont;
};

#endif // !GAME_H_
