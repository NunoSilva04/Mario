#include "OptionCursor.h"
#include "Camera.h"
#include "InputManager.h"

OPTIONCURSOR::OPTIONCURSOR() {
	optionCursorVertexShader = nullptr;
	optionCursorPixelShader = nullptr;
	optionCursorInputLayout = nullptr;
	optionCursorVertexBuffer = nullptr;
	optionCursorIndexBuffer = nullptr;
	optionCursorShaderResourceView = nullptr;
	optionCursorSamplerState = nullptr;

	optionCursorVertices[0] = { DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	optionCursorVertices[1] = { DirectX::XMFLOAT3(0.2f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	optionCursorVertices[2] = { DirectX::XMFLOAT3(0.0f, 0.8f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	optionCursorVertices[3] = { DirectX::XMFLOAT3(0.2f, 0.8f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
	optionCursorWorld = DirectX::XMMatrixIdentity();
	translationY = 0.0f;
	coolDown = 0.0f;
	state = 1;
}

OPTIONCURSOR::~OPTIONCURSOR() {

}

void OPTIONCURSOR::initOptionCursor(ID3D11Device* dev) {
	initOptionCursorShaders(dev);
	initOptionCursorVertexBuffer(dev);
	initOptionCursorIndexBuffer(dev);
	initOptionCursorShaderResourceView(dev);
}

void OPTIONCURSOR::initOptionCursorShaders(ID3D11Device* dev){
	HRESULT hr;

	//Vertex shader
	ID3D10Blob* pOptionCursorVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"OptionCursorVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pOptionCursorVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile option cursor vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreateVertexShader(pOptionCursorVertexShader->GetBufferPointer(), pOptionCursorVertexShader->GetBufferSize(), nullptr,
		&optionCursorVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Pixel shader
	ID3D10Blob* pOptionCursorPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"OptionCursorPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pOptionCursorPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile option cursor pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreatePixelShader(pOptionCursorPixelShader->GetBufferPointer(), pOptionCursorPixelShader->GetBufferSize(), nullptr,
		&optionCursorPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Input Layout
	D3D11_INPUT_ELEMENT_DESC optionCursorInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(optionCursorInputLayoutDesc);

	hr = dev->CreateInputLayout(optionCursorInputLayoutDesc, size, pOptionCursorVertexShader->GetBufferPointer(),
		pOptionCursorVertexShader->GetBufferSize(), &optionCursorInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor input layout", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void OPTIONCURSOR::initOptionCursorVertexBuffer(ID3D11Device* dev){
	HRESULT hr;

	optionCursorVertices[0] = { DirectX::XMFLOAT3(-0.23f, -0.27f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	optionCursorVertices[1] = { DirectX::XMFLOAT3(-0.15f, -0.27f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	optionCursorVertices[2] = { DirectX::XMFLOAT3(-0.23f, -0.35f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	optionCursorVertices[3] = { DirectX::XMFLOAT3(-0.15f, -0.35f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };

	D3D11_BUFFER_DESC optionCursorVertexBufferDesc;
	ZeroMemory(&optionCursorVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	optionCursorVertexBufferDesc.ByteWidth = 4 * sizeof(optionCursorStruct);
	optionCursorVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	optionCursorVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	optionCursorVertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA optionCursorVertexBufferSubData;
	ZeroMemory(&optionCursorVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	optionCursorVertexBufferSubData.pSysMem = optionCursorVertices;

	hr = dev->CreateBuffer(&optionCursorVertexBufferDesc, &optionCursorVertexBufferSubData, &optionCursorVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor vertex buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void OPTIONCURSOR::initOptionCursorIndexBuffer(ID3D11Device* dev){
	HRESULT hr;

	DWORD optionCursorIndices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC optionCursorIndexBufferDesc;
	ZeroMemory(&optionCursorIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	optionCursorIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	optionCursorIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	optionCursorIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	optionCursorIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA optionCursorIndexBufferSubData;
	ZeroMemory(&optionCursorIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	optionCursorIndexBufferSubData.pSysMem = optionCursorIndices;

	hr = dev->CreateBuffer(&optionCursorIndexBufferDesc, &optionCursorIndexBufferSubData, &optionCursorIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor index buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void OPTIONCURSOR::initOptionCursorShaderResourceView(ID3D11Device* dev){
	HRESULT hr;

	//Shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"OptionCursor.png", nullptr, nullptr, &optionCursorShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create shader resource view", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Sampler state
	D3D11_SAMPLER_DESC optionCursorSamplerStateDesc;
	ZeroMemory(&optionCursorSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));

	optionCursorSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	optionCursorSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	optionCursorSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	optionCursorSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	optionCursorSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	optionCursorSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	optionCursorSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&optionCursorSamplerStateDesc, &optionCursorSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create option cursor sampler state", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void OPTIONCURSOR::updateOptionCursor(float frame_time) {
	//CoolDown
	if (coolDown < 0.0f) {
		coolDown = 0.0f;
	}
	else {
		coolDown += frame_time;
	}

	//Change option
	if (inputManager.keyPressed[VK_DOWN] && coolDown > 0.3f) {
		translationY -= 0.11f;
		coolDown = -0.1f;
		state += 1;
	}else if (inputManager.keyPressed[VK_UP] && coolDown > 0.3f) {
		translationY += 0.11f;
		coolDown = -0.1f;
		state -= 1;
	}

	//Reset Translation
	if (translationY <= -0.25f) {
		translationY = 0.0f;
		state = 1;
	}
	else if (translationY >= 0.05f) {
		translationY = -0.22f;
		state = 3;
	}

	optionCursorWorld = DirectX::XMMatrixTranslation(0.0f, translationY, 0.0f);
}

void OPTIONCURSOR::renderOptionCursor(ID3D11DeviceContext* devCon){
	devCon->VSSetShader(optionCursorVertexShader, 0, 0);
	devCon->PSSetShader(optionCursorPixelShader, 0, 0);
	devCon->IASetInputLayout(optionCursorInputLayout);

	UINT strides = { sizeof(optionCursorStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &optionCursorVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(optionCursorIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &optionCursorShaderResourceView);
	devCon->PSSetSamplers(0, 1, &optionCursorSamplerState);

	Camera.WVP = optionCursorWorld * Camera.CamView * Camera.CamProjection;
	Camera.WVPInformationStruct.WVPInformationMatrix = DirectX::XMMatrixTranspose(Camera.WVP);
	devCon->UpdateSubresource(Camera.WVPBuffer, 0, nullptr, &Camera.WVPInformationStruct, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);

	devCon->DrawIndexed(6, 0, 0);
}

void OPTIONCURSOR::cleanOptionCursor() {
	optionCursorVertexShader->Release();
	optionCursorPixelShader->Release();
	optionCursorInputLayout->Release();
	optionCursorVertexBuffer->Release();
	optionCursorIndexBuffer->Release();
	optionCursorShaderResourceView->Release();
	optionCursorSamplerState->Release();
}