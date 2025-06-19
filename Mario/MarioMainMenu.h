#ifndef MARIOMAINMENU_H_
#define MARIOMAINMENU_H_

#include "AllHeaderFiles.h"

class MARIOMAINMENU {
public:
	MARIOMAINMENU() {
		marioMainMenuVertexShader = nullptr;
		marioMainMenuPixelShader = nullptr;
		marioMainMenuInputLayout = nullptr;
		marioMainMenuVertexBuffer = nullptr;
		marioMainMenuIndexBuffer = nullptr;
		marioMainMenuShaderResourceView = nullptr;
		marioMainMenuSamplerState = nullptr;

		marioMainMenuVertices[0] = { DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
		marioMainMenuVertices[1] = { DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
		marioMainMenuVertices[2] = { DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
		marioMainMenuVertices[3] = { DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
		
		marioMainMenuWorld = DirectX::XMMatrixIdentity();
	};
	~MARIOMAINMENU() {

	};

	void initMarioMainMenu(ID3D11Device* dev);
	void initMarioMainMenuShaders(ID3D11Device* dev);
	void initMarioMainMenuVertexBuffer(ID3D11Device* dev);
	void initMarioMainMenuIndexBuffer(ID3D11Device* dev);
	void initMarioMainMenuShaderResourceView(ID3D11Device* dev);
	void updateMarioMainMenu(ID3D11DeviceContext* devCon);
	void renderMarioMainMenu(ID3D11DeviceContext* devCon);
	void cleanMarioMainMenu();

private:
	ID3D11VertexShader* marioMainMenuVertexShader;
	ID3D11PixelShader* marioMainMenuPixelShader;
	ID3D11InputLayout* marioMainMenuInputLayout;
	ID3D11Buffer* marioMainMenuVertexBuffer;
	ID3D11Buffer* marioMainMenuIndexBuffer;
	ID3D11ShaderResourceView* marioMainMenuShaderResourceView;
	ID3D11SamplerState* marioMainMenuSamplerState;
	DirectX::XMMATRIX marioMainMenuWorld;

	struct marioMainMenuStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	};
	marioMainMenuStruct marioMainMenuVertices[4];
};

#endif // !MARIOMAINMENU_H_