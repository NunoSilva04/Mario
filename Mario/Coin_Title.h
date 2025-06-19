#ifndef COIN_TITLE_H_
#define COIN_TITLE_H_

#include "AllHeaderFiles.h"

class COIN_TITLE {
public:
	COIN_TITLE();
	void initCoinTitleShaders(ID3D11Device* dev);
	void initCoinTitleVertexBuffer(ID3D11Device* dev);
	void initCoinTitleIndexBuffer(ID3D11Device* dev);
	void initCoinTitleShaderResourceView(ID3D11Device* dev);
	void renderCoinTitle(ID3D11DeviceContext* devCon);
	void cleanCoinTitle();

private:
	ID3D11VertexShader* coinTitleVertexShader;
	ID3D11PixelShader* coinTitlePixelShader;
	ID3D11InputLayout* coinTitleInputLayout;
	ID3D11Buffer* coinTitleVertexBuffer;
	ID3D11Buffer* coinTitleIndexBuffer;
	ID3D11ShaderResourceView* coinTitleShaderResourceView;
	ID3D11SamplerState* coinTitleSamplerState;

	typedef struct coinTitleStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	}coinTitleStruct;
	coinTitleStruct coinTitleVertices[4];
};

#endif // !COIN_TITLE_H_OIN_TITLE_H_
