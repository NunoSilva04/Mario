#include "LightGreenBush.h"

LIGHTGREENBUSH::LIGHTGREENBUSH() {
	objectType = BackgroundObjects::LightGreenBush;
	instanceBuffer = nullptr;
	shaderResourceView[0] = nullptr;
	shaderResourceView[1] = nullptr;
}

LIGHTGREENBUSH::~LIGHTGREENBUSH() {

}

void LIGHTGREENBUSH::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	instanceStruct tempStruct;
	DirectX::XMMATRIX translationMatrix, scaleMatrix;
	//BIG LIGHT GREEN BUSH
	//1
	translationMatrix = DirectX::XMMatrixTranslation(8.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(40.5f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(60.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//4
	translationMatrix = DirectX::XMMatrixTranslation(93.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(107.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//6
	translationMatrix = DirectX::XMMatrixTranslation(139.7f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);

	//SMALL LIGHT GREEN BUSH
	//1
	translationMatrix = DirectX::XMMatrixTranslation(30.0f, -1.5f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(123.0f, -1.5f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(205.0f, -1.5f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);

	D3D11_BUFFER_DESC instanceBufferDesc;
	ZeroMemory(&instanceBufferDesc, sizeof(D3D11_BUFFER_DESC));
	instanceBufferDesc.ByteWidth = instances.size() * sizeof(instanceStruct);
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA instanceBufferSubData;
	ZeroMemory(&instanceBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	instanceBufferSubData.pSysMem = instances.data();

	hr = dev->CreateBuffer(&instanceBufferDesc, &instanceBufferSubData, instanceBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create light green bush instance buffer\n");
		PostQuitMessage(0);
	}
}

void LIGHTGREENBUSH::initShaderResourceView(ID3D11Device* dev) {
	HRESULT hr;

	//Shader resource views
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"SmallLightGreenBush.png", nullptr, nullptr,
		shaderResourceView[0].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create small light green bush shader resource view\n");
		PostQuitMessage(0);
	}

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"BigLightGreenBush.png", nullptr, nullptr,
		shaderResourceView[1].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create big light green bush shader resource view\n");
		PostQuitMessage(0);
	}
}