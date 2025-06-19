#ifndef SUPERMARIOBROSTITLE_H_
#define SUPERMARIOBROSTITLE_H_

#include "AllHeaderFiles.h"

class SUPERMARIOBROSTITLE {
public:
	SUPERMARIOBROSTITLE();
	void initSuperMarioBrosTitleShaders(ID3D11Device* dev);
	void initSuperMarioBrosTitleVertexBuffer(ID3D11Device* dev);
	void initSuperMarioBrosTitleIndexBuffer(ID3D11Device* dev);
	void initSuperMarioBrosTitleTexture(ID3D11Device* dev);
	void renderSuperMarioBrosTitle(ID3D11DeviceContext* devCon);
	void cleanSuperMarioBrosTitle();

private:
	typedef struct superMarioBrosTitleStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	}superMarioBrosTitleStruct;
	superMarioBrosTitleStruct superMarioBrosVertices[4];

	ID3D11VertexShader* superMarioBrosTitleVertexShader;
	ID3D11PixelShader* superMarioBrosTitlePixelShader;
	ID3D11InputLayout* superMarioBrosTitleInputLayout;
	ID3D11Buffer* superMarioBrosTitleVertexBuffer;
	ID3D11Buffer* superMarioBrosTitleIndexBuffer;
	ID3D11ShaderResourceView* superMarioBrosTitleShaderResourceView;
	ID3D11SamplerState* superMarioBrosTitleSamplerState;
};

#endif // !SUPERMARIOBROSTITLE_H_
