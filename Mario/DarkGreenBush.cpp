#include "DarkGreenBush.h"

DARKGREENBUSH::DARKGREENBUSH() {
	objectType = BackgroundObjects::DarkGreenBush;
	instanceBuffer = nullptr;
	shaderResourceView[0] = nullptr;
	shaderResourceView[1] = nullptr;
}

DARKGREENBUSH::~DARKGREENBUSH() {

}

void DARKGREENBUSH::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	instanceStruct tempStruct;
	DirectX::XMMATRIX translationMatrix, scaleMatrix;
	//TALL DARK GREEN BUSH
	//1
	translationMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(25.5f, 0.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(50.0f, 0.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//4
	translationMatrix = DirectX::XMMatrixTranslation(74.0f, 0.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(98.0f, 0.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);

	//SMALL DARK GREEN BUSH
	//1
	translationMatrix = DirectX::XMMatrixTranslation(11.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(64.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(110.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//4
	translationMatrix = DirectX::XMMatrixTranslation(160.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(205.0f, -1.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 1.0f);
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
		OutputDebugString(L"Couldn't create dark green bush instance buffer\n");
		PostQuitMessage(0);
	}
}

void DARKGREENBUSH::initShaderResourceView(ID3D11Device* dev){
	HRESULT hr;

	//Shader resource views
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"SmallDarkGreenBush.png", nullptr, nullptr, 
		shaderResourceView[0].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create first dark green bush shader resource view\n");
		PostQuitMessage(0);
	}

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"TallDarkGreenBush.png", nullptr, nullptr,
		shaderResourceView[1].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create second dark green bush shader resource view\n");
		PostQuitMessage(0);
	}
}