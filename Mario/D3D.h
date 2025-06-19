#ifndef D3D_H_
#define D3D_H_

#include "AllHeaderFiles.h"
#include "Id3d.h"
#include "MainMenu.h"
#include "Game.h"

static int width = GetSystemMetrics(SM_CXSCREEN);
static int height = GetSystemMetrics(SM_CYSCREEN);

class D3D : public Id3d{
public:
	D3D();
	void initD3D(HWND hWnd);
	void updateD3D(float frame_time);
	void renderD3D(int time);
	void cleanD3D();
	
	//Test
	void initD3DTest(HWND hWnd);
	void renderD3DTest();


private:
	static ID3D11Device* dev;
	ID3D11DeviceContext* devCon;
	ID3D11RenderTargetView* renderTargetView;
	IDXGISwapChain* swapChain;
	IDXGISwapChain1* swapChain1;
	bool playGame;
	int start_timer, end_timer;
	ID3D11Device* getDevice() override;

private:
	MAINMENU MainMenu;
	GAME Game;
};

#endif // !D3D_H_
