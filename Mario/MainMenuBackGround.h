#ifndef MAINMENUBACKGROUND_H_
#define MAINMENUBACKGROUND_H_

#include "AllHeaderFiles.h"

class MAINMENUBG {
public:
	MAINMENUBG();
	void initMainMenuBgShaders(ID3D11Device* dev);
	void initMainMenuBgVertexBuffer(ID3D11Device* dev);
	void initMainMenuBgIndexBuffer(ID3D11Device* dev);
	void initMainMenuBgShaderResourceView(ID3D11Device* dev);
	void renderMainMenuBg(ID3D11DeviceContext* devCon);
	void cleanMainMenuBg();

private:
	ID3D11VertexShader* mainMenuBgVertexShader;
	ID3D11PixelShader* mainMenuBgPixelShader;
	ID3D11InputLayout* mainMenuBgInputLayout;
	ID3D11Buffer* mainMenuBgVertexBuffer;
	ID3D11Buffer* mainMenuBgIndexBuffer;
	ID3D11ShaderResourceView* mainMenuBgShaderResourceView;
	ID3D11SamplerState* mainMenuBgSamplerState;

	typedef struct mainMenuBgStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	}mainMenuBgStruct;

	mainMenuBgStruct mainMenuBgVertices[4];
};

#endif // !MAINMENUBACKGROUND_H_
