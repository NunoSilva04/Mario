#include "MainMenu.h"
#include "Camera.h"
#include "Player.h"
#include "InputManager.h"
#include "OptionCursor.h"

MAINMENU::MAINMENU() {
	superMarioBros_SpriteBatch = nullptr;
	superMarioBros_SpriteFont = nullptr;
}

void MAINMENU::initMainMenu(ID3D11Device* dev, ID3D11DeviceContext* devCon) {
	superMarioBros_SpriteBatch = new DirectX::SpriteBatch(devCon);
	superMarioBros_SpriteFont = new DirectX::SpriteFont(dev, L"myfileb.spritefont");

	//Initiate super mario bros title
	superMarioBrosTitle.initSuperMarioBrosTitleShaders(dev);
	superMarioBrosTitle.initSuperMarioBrosTitleVertexBuffer(dev);
	superMarioBrosTitle.initSuperMarioBrosTitleIndexBuffer(dev);
	superMarioBrosTitle.initSuperMarioBrosTitleTexture(dev);

	//Initiate Main Menu Bg
	mainMenuBg.initMainMenuBgShaders(dev);
	mainMenuBg.initMainMenuBgVertexBuffer(dev);
	mainMenuBg.initMainMenuBgIndexBuffer(dev);
	mainMenuBg.initMainMenuBgShaderResourceView(dev);

	//Inititate coin title
	coinTitle.initCoinTitleShaders(dev);
	coinTitle.initCoinTitleVertexBuffer(dev);
	coinTitle.initCoinTitleIndexBuffer(dev);
	coinTitle.initCoinTitleShaderResourceView(dev);

	//Init optionCursor
	OPTIONCURSOR& OptionCursor = OPTIONCURSOR::getInstance();
	OptionCursor.initOptionCursor(dev);

	//Init marioMainMenu
	MarioMainMenu.initMarioMainMenu(dev);
}

bool MAINMENU::updateMainMenu(ID3D11DeviceContext* devCon, float frame_time, bool playGame) {
	PLAYER& player = PLAYER::getInstance();
	OPTIONCURSOR& OptionCursor = OPTIONCURSOR::getInstance();

	OptionCursor.updateOptionCursor(frame_time);
	if (OptionCursor.state == 1 && inputManager.keyPressed[VK_RETURN]) {
		playGame = true;
		MarioMainMenu.updateMarioMainMenu(devCon);
		return playGame;
	}
	else if (OptionCursor.state == 2 && inputManager.keyPressed[VK_RETURN]) {
		player.resetPlayerStat();
	}
	else if (OptionCursor.state == 3 && inputManager.keyPressed[VK_RETURN]) {
		PostQuitMessage(0);
	}

	return playGame;
}

void MAINMENU::renderMainMenu(ID3D11DeviceContext *devCon, int time) {
	PLAYER& player = PLAYER::getInstance();
	OPTIONCURSOR& OptionCursor = OPTIONCURSOR::getInstance();

	std::wostringstream score, numCoins, timeString;
	score << player.player1.score;
	numCoins << player.player1.num_coins;
	timeString << time;

	//Super mario bros bg
	mainMenuBg.renderMainMenuBg(devCon);

	//Start batch
	superMarioBros_SpriteBatch->Begin();
	
	//Mario 
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"Mario", DirectX::XMFLOAT2(400, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Score
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, score.str().c_str(), DirectX::XMFLOAT2(400, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Coins
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"x", DirectX::XMFLOAT2(780, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, numCoins.str().c_str(), DirectX::XMFLOAT2(810, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//World
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"World", DirectX::XMFLOAT2(1000, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//1-1
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"1-1", DirectX::XMFLOAT2(1050, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Time
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"Time", DirectX::XMFLOAT2(1400, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, timeString.str().c_str(), DirectX::XMFLOAT2(1450, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//1985 NINTENDO
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"1985 NINTENDO", DirectX::XMFLOAT2(1200, 580),
		DirectX::SimpleMath::Color(0.9216, 0.7412, 0.5059, 1.0f), 0);
	
	//Play
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"PLAY", DirectX::XMFLOAT2(900, 650),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//Reset
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"RESET", DirectX::XMFLOAT2(900, 700),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Exit
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"EXIT", DirectX::XMFLOAT2(900, 750),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//TOP
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"TOP-", DirectX::XMFLOAT2(900, 820),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Score
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, score.str().c_str(), DirectX::XMFLOAT2(1000, 820),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//End Batch
	superMarioBros_SpriteBatch->End();
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);


	coinTitle.renderCoinTitle(devCon);
	superMarioBrosTitle.renderSuperMarioBrosTitle(devCon);
	OptionCursor.renderOptionCursor(devCon);
	MarioMainMenu.renderMarioMainMenu(devCon);
}

void MAINMENU::renderLoadingMenu(ID3D11DeviceContext* devCon) {
	PLAYER& player = PLAYER::getInstance();
	OPTIONCURSOR& OptionCursor = OPTIONCURSOR::getInstance();

	std::wostringstream score, numCoins, numLives;
	score << player.player1.score;
	numCoins << player.player1.num_coins;
	numLives << player.player1.numLives;

	//Start batch
	superMarioBros_SpriteBatch->Begin();
	
	//Mario 
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"Mario", DirectX::XMFLOAT2(400, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Score
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, score.str().c_str(), DirectX::XMFLOAT2(400, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Coins
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"x", DirectX::XMFLOAT2(780, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, numCoins.str().c_str(), DirectX::XMFLOAT2(810, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//World
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"World", DirectX::XMFLOAT2(1000, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//1-1
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"1-1", DirectX::XMFLOAT2(1050, 110),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//Time
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"Time", DirectX::XMFLOAT2(1400, 80),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//World
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"World", DirectX::XMFLOAT2(870, 400),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//1-1
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"1-1", DirectX::XMFLOAT2(900, 450),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//x NumLives
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, L"x", DirectX::XMFLOAT2(900, 570),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	superMarioBros_SpriteFont->DrawString(superMarioBros_SpriteBatch, numLives.str().c_str(), DirectX::XMFLOAT2(950, 570),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//End Batch
	superMarioBros_SpriteBatch->End();
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);

	coinTitle.renderCoinTitle(devCon);
	MarioMainMenu.renderMarioMainMenu(devCon);
}

void MAINMENU::cleanMainMenu() {
	OPTIONCURSOR& OptionCursor = OPTIONCURSOR::getInstance();
	delete superMarioBros_SpriteBatch;
	delete superMarioBros_SpriteFont;
	superMarioBrosTitle.cleanSuperMarioBrosTitle();
	mainMenuBg.cleanMainMenuBg();
	coinTitle.cleanCoinTitle();
	OptionCursor.cleanOptionCursor();
	MarioMainMenu.cleanMarioMainMenu();
}