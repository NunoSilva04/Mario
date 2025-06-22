#include "Clouds.h"

CLOUDS::CLOUDS() {
	objectType = BackgroundObjects::Clouds;
	instanceBuffer = nullptr;
	shaderResourceView[0] = nullptr;
	shaderResourceView[1] = nullptr;
}

CLOUDS::~CLOUDS() {

}

void CLOUDS::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	instanceStruct tempStruct;
	DirectX::XMMATRIX translationMatrix, scaleMatrix;
	//BIG CLOUD
	//1
	translationMatrix = DirectX::XMMatrixTranslation(15.0f, 3.7f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(20.0f, 3.85f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(52.0f, 3.7f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//4
	translationMatrix = DirectX::XMMatrixTranslation(65.0f, 3.90f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(98.0f, 3.70f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(125.0f, 3.90f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.7f, 0.5f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 1;
	instances.push_back(tempStruct);

	//SMALL CLOUD
	//1
	translationMatrix = DirectX::XMMatrixTranslation(7.0f, 4.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//2
	translationMatrix = DirectX::XMMatrixTranslation(22.0f, 4.25f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//3
	translationMatrix = DirectX::XMMatrixTranslation(82.0f, 4.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//4
	translationMatrix = DirectX::XMMatrixTranslation(102.0f, 4.25f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//5
	translationMatrix = DirectX::XMMatrixTranslation(172.0f, 4.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//6
	translationMatrix = DirectX::XMMatrixTranslation(192.0f, 4.25f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//7
	translationMatrix = DirectX::XMMatrixTranslation(255.0f, 4.0f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//8
	translationMatrix = DirectX::XMMatrixTranslation(275.0f, 4.25f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 0.4f, 1.0f);
	tempStruct.transformMatrix = DirectX::XMMatrixMultiply(translationMatrix, scaleMatrix);
	tempStruct.size = 0;
	instances.push_back(tempStruct);
	//8
	translationMatrix = DirectX::XMMatrixTranslation(295.0f, 4.0f, 0.0f);
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
		OutputDebugString(L"Couldn't create cloud instance buffer\n");
		PostQuitMessage(0);
	}
}

void CLOUDS::initShaderResourceView(ID3D11Device* dev) {
	HRESULT hr;

	//Shader resource views
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"SmallCloud.png", nullptr, nullptr,
		shaderResourceView[0].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create small cloud shader resource view\n");
		PostQuitMessage(0);
	}

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"BigCloud.png", nullptr, nullptr,
		shaderResourceView[1].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create big cloud shader resource view\n");
		PostQuitMessage(0);
	}
}