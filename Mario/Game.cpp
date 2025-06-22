#include "Game.h"
#include "GameObjectFactory.h"
#include "GameObjects.h"
#include "Block.h"
#include "IGrid.h"
#include "Grid.h"
#include "Camera.h"
#include "Mario.h"
#include "Background.h"
#include "Player.h"

GAME::GAME() {
	grids = std::make_shared<Grid>(7);
	Mario = new MARIO();
	gameSpriteBatch = nullptr;
	gameSpriteFont = nullptr;
}

void GAME::initGame(ID3D11Device* dev, ID3D11DeviceContext *devCon) {
	gameSpriteBatch = new DirectX::SpriteBatch(devCon);
	gameSpriteFont = new DirectX::SpriteFont(dev, L"myfileb.spritefont");

	backgroundArray.push_back(BACKGROUND::createBackgroundObjects(BackgroundObjects::DarkGreenBush));
	backgroundArray.push_back(BACKGROUND::createBackgroundObjects(BackgroundObjects::LightGreenBush));
	backgroundArray.push_back(BACKGROUND::createBackgroundObjects(BackgroundObjects::Clouds));
	backgroundArray.push_back(BACKGROUND::createBackgroundObjects(BackgroundObjects::Flag));
	backgroundArray.push_back(BACKGROUND::createBackgroundObjects(BackgroundObjects::Castle)); 
	for (int i = 0; i < backgroundArray.size(); i++) {
		backgroundArray[i]->initBackground(dev);
	}

	gameObjectsArray.push_back(GameObjectFactory::createGameObject(ObjectTypes::Block, "FloorTile"));
	GameObjectFactory::createGameObject(ObjectTypes::Block, "DarkFloorTile");
	GameObjectFactory::createGameObject(ObjectTypes::Block, "Brick");
	GameObjectFactory::createGameObject(ObjectTypes::Block, "DarkBrick");
	GameObjectFactory::createGameObject(ObjectTypes::Block, "MysteryBlock");
	GameObjectFactory::createGameObject(ObjectTypes::Block, "UnbreakableBrick");
	GameObjectFactory::createGameObject(ObjectTypes::Block, "Pipe");
	std::vector<std::shared_ptr<IGameObjects>> IgameObjectsArray;
	for (int i = 0; i < gameObjectsArray.size(); i++) {
		if (i == 0) {
			gameObjectsArray[i]->initObject(dev);
			std::shared_ptr<Block> tempBlock = std::dynamic_pointer_cast<Block>(gameObjectsArray[i]);
			if (tempBlock == nullptr) {
				PostQuitMessage(0);
				OutputDebugString(L"Couldn't convert a gameObject into IGameObject\n");
				break;
			}
			else {
				IgameObjectsArray.push_back(std::static_pointer_cast<IGameObjects>(tempBlock));
			}
		}
	}

	grids->createGrid(IgameObjectsArray);
	Mario->initMario(dev);
}

void GAME::updateGame(ID3D11DeviceContext* devCon, float frame_time){
	grids->updateRenderableGrids(Camera.screenLeftSide, Camera.screenRightSide);
	std::vector<std::shared_ptr<IGameObjects>> IGameObjectsArray;
	for (int i = 0; i < gameObjectsArray.size(); i++) {
		std::shared_ptr<Block> tempBlock = std::dynamic_pointer_cast<Block>(gameObjectsArray[i]);
		IGameObjectsArray.push_back(tempBlock);
	}
	Mario->updateMario(devCon, frame_time, std::static_pointer_cast<IGrid>(grids), IGameObjectsArray);
	for (int i = 0; i < gameObjectsArray.size(); i++) {
		gameObjectsArray[i]->updateObject(devCon, std::static_pointer_cast<IGrid>(grids));
	}
	Camera.updateCamera(devCon, *Mario);
}

void GAME::renderGame(ID3D11DeviceContext* devCon, float time){
	for (int i = 0; i < backgroundArray.size(); i++) {
		backgroundArray[i]->renderBackground(devCon);
	}
	for (int i = 0; i < gameObjectsArray.size(); i++) {
		gameObjectsArray[i]->renderObject(devCon);
	}
	Mario->renderMario(devCon);

	PLAYER& player = PLAYER::getInstance();
	std::wostringstream score, numCoins, timeString;
	score << player.player1.score;
	numCoins << player.player1.num_coins;
	timeString << time;

	gameSpriteBatch->Begin();

	//Mario
	gameSpriteFont->DrawString(gameSpriteBatch, L"Mario", DirectX::XMFLOAT2(20, 10),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	gameSpriteFont->DrawString(gameSpriteBatch, score.str().c_str(), DirectX::XMFLOAT2(20, 40),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	//Coins
	gameSpriteFont->DrawString(gameSpriteBatch, L"x", DirectX::XMFLOAT2(350, 40),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	gameSpriteFont->DrawString(gameSpriteBatch, numCoins.str().c_str(), DirectX::XMFLOAT2(380, 40),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	//World 1-1
	gameSpriteFont->DrawString(gameSpriteBatch, L"World", DirectX::XMFLOAT2(1500, 10),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	gameSpriteFont->DrawString(gameSpriteBatch, L"1-1", DirectX::XMFLOAT2(1550, 40),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	//Time
	gameSpriteFont->DrawString(gameSpriteBatch, L"Time", DirectX::XMFLOAT2(1800, 10),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);
	gameSpriteFont->DrawString(gameSpriteBatch, timeString.str().c_str(), DirectX::XMFLOAT2(1850, 40),
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), 0);

	gameSpriteBatch->End();
}

void GAME::cleanGame(){
	Mario->cleanMario();
	delete Mario;
	delete gameSpriteBatch;
	delete gameSpriteFont;
}