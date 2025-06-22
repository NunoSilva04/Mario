#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "AllHeaderFiles.h"
#include <wrl/client.h>
#include <memory>

enum class BackgroundObjects {
	DarkGreenBush,
	LightGreenBush,
	Clouds,
	Castle,
	Flag,
};

class BACKGROUND {
public:
	virtual ~BACKGROUND(){}
	static std::unique_ptr<BACKGROUND> createBackgroundObjects(BackgroundObjects type);
	void initBackground(ID3D11Device* dev);
	void initShaders(ID3D11Device* dev);
	void initVertexBuffer(ID3D11Device* dev);
	void initIndexBuffer(ID3D11Device* dev);
	virtual void initInstanceBuffer(ID3D11Device* dev) = 0;
	virtual void initShaderResourceView(ID3D11Device* dev) = 0;
	void initSamplerState(ID3D11Device* dev);
	void renderBackground(ID3D11DeviceContext* devCon);

private:
	static Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	static Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	struct vertexStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	};
	static vertexStruct vertices[4];
	static bool hasShaders, hasVertexBuffer, hasIndexBuffer, hasSamplerState;

protected:
	BackgroundObjects objectType;
	Microsoft::WRL::ComPtr<ID3D11Buffer> instanceBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView[2];

	struct instanceStruct {
		DirectX::XMMATRIX transformMatrix;
		int size;
	};
	std::vector<instanceStruct> instances;
};

#endif // !BACKGROUND_H_