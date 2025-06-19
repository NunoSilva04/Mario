#include "Background.h"
#include "DarkGreenBush.h"
#include "LightGreenBush.h"
#include "Clouds.h"

namespace wrl = Microsoft::WRL;

Microsoft::WRL::ComPtr<ID3D11VertexShader> BACKGROUND::vertexShader = nullptr;
Microsoft::WRL::ComPtr<ID3D11PixelShader> BACKGROUND::pixelShader = nullptr;
Microsoft::WRL::ComPtr<ID3D11InputLayout> BACKGROUND::inputLayout = nullptr;
Microsoft::WRL::ComPtr<ID3D11Buffer> BACKGROUND::vertexBuffer = nullptr;
Microsoft::WRL::ComPtr<ID3D11Buffer> BACKGROUND::indexBuffer = nullptr;
Microsoft::WRL::ComPtr<ID3D11SamplerState> BACKGROUND::samplerState = nullptr;
BACKGROUND::vertexStruct BACKGROUND::vertices[4] = { {}, {}, {}, {} };
bool BACKGROUND::hasShaders = false;
bool BACKGROUND::hasVertexBuffer = false;
bool BACKGROUND::hasIndexBuffer = false;
bool BACKGROUND::hasSamplerState = false;


std::unique_ptr<BACKGROUND> BACKGROUND::createBackgroundObjects(BackgroundObjects type) {
	switch (type) {
	case BackgroundObjects::DarkGreenBush:
		return std::make_unique<DARKGREENBUSH>();
		break;

	case BackgroundObjects::LightGreenBush:
		return std::make_unique<LIGHTGREENBUSH>();
		break;

	case BackgroundObjects::Clouds:
		return std::make_unique<CLOUDS>();
		break;

	case BackgroundObjects::Castle:
		
		break;

	default:
		return nullptr;
	}
}

void BACKGROUND::initBackground(ID3D11Device* dev) {
	if (!hasShaders) {
		initShaders(dev);
	}
	if (!hasVertexBuffer) {
		initVertexBuffer(dev);
	}
	if (!hasIndexBuffer) {
		initIndexBuffer(dev);
	}
	initInstanceBuffer(dev);
	initShaderResourceView(dev);
	if (!hasSamplerState) {
		initSamplerState(dev);
	}
}

void BACKGROUND::initShaders(ID3D11Device* dev) {
	HRESULT hr;

	//Vertex shader
	wrl::ComPtr<ID3D10Blob> pVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"BackgroundVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, pVertexShader.GetAddressOf(), 0, 0);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't compile background vertex shader\n");
		PostQuitMessage(0);
	}

	hr = dev->CreateVertexShader(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), nullptr,
		vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create background vertex shader\n");
		PostQuitMessage(0);
	}

	//Pixel shader
	wrl::ComPtr<ID3D10Blob> pPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"BackgroundPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, pPixelShader.GetAddressOf(), 0, 0);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't compile background pixel shader\n");
		PostQuitMessage(0);
	}

	hr = dev->CreatePixelShader(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize(), nullptr,
		pixelShader.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Coulnd't create background pixel shader\n");
		PostQuitMessage(0);
	}

	//Input Layout
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TRANSFORM_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"SIZE", 0, DXGI_FORMAT_R32_SINT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	};
	UINT size = ARRAYSIZE(inputLayoutDesc);

	hr = dev->CreateInputLayout(inputLayoutDesc, size, pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(),
		inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create background input layout\n");
		PostQuitMessage(0);
	}

	hasShaders = true;
}

void BACKGROUND::initVertexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	vertices[0] = { DirectX::XMFLOAT3(-3.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	vertices[1] = { DirectX::XMFLOAT3(-0.5f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	vertices[2] = { DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	vertices[3] = { DirectX::XMFLOAT3(-0.5f, -1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.ByteWidth = 4 * sizeof(vertexStruct);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferSubData;
	ZeroMemory(&vertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferSubData.pSysMem = vertices;

	hr = dev->CreateBuffer(&vertexBufferDesc, &vertexBufferSubData, vertexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create background vertex buffer\n");
		PostQuitMessage(0);
	}

	hasVertexBuffer = true;
}

void BACKGROUND::initIndexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferSubData;
	ZeroMemory(&indexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	indexBufferSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&indexBufferDesc, &indexBufferSubData, indexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create background index buffer\n");
		PostQuitMessage(0);
	}

	hasIndexBuffer = true;
}

void BACKGROUND::initSamplerState(ID3D11Device* dev) {
	HRESULT hr;

	D3D11_SAMPLER_DESC samplerStateDesc;
	ZeroMemory(&samplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&samplerStateDesc, samplerState.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create background sampler state\n");
		PostQuitMessage(0);
	}

	hasSamplerState = true;
}

void BACKGROUND::renderBackground(ID3D11DeviceContext* devCon) {
	wrl::ComPtr<ID3D11Buffer> buffers[] = { vertexBuffer, instanceBuffer };
	UINT strides[] = { sizeof(vertexStruct), sizeof(instanceStruct) };
	UINT offset[] = { 0,0 };
	devCon->IASetInputLayout(inputLayout.Get());
	devCon->IASetVertexBuffers(0, 2, buffers->GetAddressOf(), strides, offset);
	devCon->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->VSSetShader(vertexShader.Get(), 0, 0);

	devCon->PSSetShader(pixelShader.Get(), 0, 0);
	devCon->PSSetShaderResources(0, 2, shaderResourceView->GetAddressOf());
	devCon->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	devCon->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);
}