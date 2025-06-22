#include "Flag.h"

Flag::Flag() {
	objectType = BackgroundObjects::Flag;
	instanceBuffer = nullptr;
	shaderResourceView[0] = nullptr;
	shaderResourceView[1] = nullptr;
}

Flag::~Flag() {

}

void Flag::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	instanceStruct tempStruct;
	DirectX::XMMATRIX translationMatrix, scaleMatrix;

	translationMatrix = DirectX::XMMatrixTranslation(328.8f, 0.78f, 0.0f);
	scaleMatrix = DirectX::XMMatrixScaling(0.3f, 2.3f, 1.0f);
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
		OutputDebugString(L"Couldn't create castle instance buffer\n");
		PostQuitMessage(0);
	}
}

void Flag::initShaderResourceView(ID3D11Device* dev) {
	//shader is the index 0
	//Shader Resource View
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"Flag.png", nullptr, nullptr, shaderResourceView[0].GetAddressOf(), nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create castle shader resource view\n");
		PostQuitMessage(0);
	}
}