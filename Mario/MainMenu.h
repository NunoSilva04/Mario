#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "AllHeaderFiles.h"
#include "SuperMarioBrosTitle.h"
#include "MainMenuBackGround.h"
#include "Coin_Title.h"
#include "MarioMainMenu.h"

class MAINMENU {
public:
	MAINMENU();
	void initMainMenu(ID3D11Device* dev, ID3D11DeviceContext* devCon);
	bool updateMainMenu(ID3D11DeviceContext *devCon, float frame_time, bool playGame);
	void renderMainMenu(ID3D11DeviceContext* devCon, int time);
	void renderLoadingMenu(ID3D11DeviceContext* devCon);
	void cleanMainMenu();

private:
	DirectX::SpriteBatch* superMarioBros_SpriteBatch;
	DirectX::SpriteFont* superMarioBros_SpriteFont;

private:
	SUPERMARIOBROSTITLE superMarioBrosTitle;
	MAINMENUBG mainMenuBg;
	COIN_TITLE coinTitle;
	MARIOMAINMENU MarioMainMenu;
};

#endif // !MAINMENU_H_MAINMENU_H_
