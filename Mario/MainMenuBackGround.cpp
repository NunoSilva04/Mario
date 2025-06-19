#include "MainMenuBackGround.h"

MAINMENUBG::MAINMENUBG() {
	ID3D11VertexShader* mainMenuBgVertexShader = nullptr;
	ID3D11PixelShader* mainMenuBgPixelShader = nullptr;
	ID3D11InputLayout* mainMenuBgInputLayout = nullptr;
	ID3D11Buffer* mainMenuBgVertexBuffer = nullptr;
	ID3D11Buffer* mainMenuBgIndexBuffer = nullptr;
	ID3D11ShaderResourceView* mainMenuBgShaderResourceView = nullptr;
	ID3D11SamplerState* mainMenuBgSamplerState = nullptr;

	mainMenuBgStruct mainMenuBgVertices[] = {
		{DirectX::XMFLOAT3(-2.3f, 1.3f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(2.3f, 1.3f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-2.3f, -1.3f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(2.3, -1.3f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
	};
}

void MAINMENUBG::initMainMenuBgShaders(ID3D11Device* dev) {
	HRESULT hr;

	//Vertex shader
	ID3D10Blob* pMainMenuBgVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"MainMenuBgVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pMainMenuBgVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile main menu bg vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pMainMenuBgVertexShader->GetBufferPointer(), pMainMenuBgVertexShader->GetBufferSize(), nullptr,
		&mainMenuBgVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create main menu bg vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Pixel shader
	ID3D10Blob* pMainMenuBgPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"MainMenuBgPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pMainMenuBgPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile main menu bg pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pMainMenuBgPixelShader->GetBufferPointer(), pMainMenuBgPixelShader->GetBufferSize(), nullptr,
		&mainMenuBgPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mai  menu bg pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Input Layout
	D3D11_INPUT_ELEMENT_DESC mainMenuBgInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(mainMenuBgInputLayoutDesc);

	hr = dev->CreateInputLayout(mainMenuBgInputLayoutDesc, size, pMainMenuBgVertexShader->GetBufferPointer(),
		pMainMenuBgVertexShader->GetBufferSize(), &mainMenuBgInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create main menu bg input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void MAINMENUBG::initMainMenuBgVertexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	mainMenuBgStruct mainMenuBgVertices[] = {
		{DirectX::XMFLOAT3(-2.3f, 1.3f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(2.3f, 1.3f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-2.3f, -1.3f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(2.3, -1.3f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC mainMenuBgVertexBufferDesc;
	ZeroMemory(&mainMenuBgVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	mainMenuBgVertexBufferDesc.ByteWidth = 4 * sizeof(mainMenuBgStruct);
	mainMenuBgVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	mainMenuBgVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	mainMenuBgVertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA mainMenuBgVertexBufferSubData;
	ZeroMemory(&mainMenuBgVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	mainMenuBgVertexBufferSubData.pSysMem = mainMenuBgVertices;

	hr = dev->CreateBuffer(&mainMenuBgVertexBufferDesc, &mainMenuBgVertexBufferSubData, &mainMenuBgVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create main menu bg vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void MAINMENUBG::initMainMenuBgIndexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	DWORD mainMenuBgIndices[] = {
		0, 1, 2,
		2, 1, 3
	};

	D3D11_BUFFER_DESC mainMenuBgIndexBufferDesc;
	ZeroMemory(&mainMenuBgIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	mainMenuBgIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	mainMenuBgIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	mainMenuBgIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	mainMenuBgIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA mainMenuBgIndexBufferSubData;
	ZeroMemory(&mainMenuBgIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	mainMenuBgIndexBufferSubData.pSysMem = mainMenuBgIndices;

	hr = dev->CreateBuffer(&mainMenuBgIndexBufferDesc, &mainMenuBgIndexBufferSubData, &mainMenuBgIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't createa main menu bg index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void MAINMENUBG::initMainMenuBgShaderResourceView(ID3D11Device* dev) {
	HRESULT hr;

	//Shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"MainMenuBg.png", nullptr, nullptr, &mainMenuBgShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create main menu bg shader resource view", L"Error", MB_OK);
		exit(-1);
	}

	//Sampler state
	D3D11_SAMPLER_DESC mainMenuBgSamplerStateDesc;
	ZeroMemory(&mainMenuBgSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));

	mainMenuBgSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	mainMenuBgSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	mainMenuBgSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	mainMenuBgSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	mainMenuBgSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	mainMenuBgSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mainMenuBgSamplerStateDesc.MinLOD = 0;
	
	hr = dev->CreateSamplerState(&mainMenuBgSamplerStateDesc, &mainMenuBgSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create main meny bg sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void MAINMENUBG::renderMainMenuBg(ID3D11DeviceContext* devCon) {
	devCon->VSSetShader(mainMenuBgVertexShader, 0, 0);
	devCon->PSSetShader(mainMenuBgPixelShader, 0, 0);
	devCon->IASetInputLayout(mainMenuBgInputLayout);

	UINT strides = { sizeof(mainMenuBgStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &mainMenuBgVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(mainMenuBgIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &mainMenuBgShaderResourceView);
	devCon->PSSetSamplers(0, 1, &mainMenuBgSamplerState);

	devCon->DrawIndexed(6, 0, 0);
}

void MAINMENUBG::cleanMainMenuBg() {
	mainMenuBgVertexShader->Release();
	mainMenuBgPixelShader->Release();
	mainMenuBgInputLayout->Release();
	mainMenuBgVertexBuffer->Release();
	mainMenuBgIndexBuffer->Release();
	mainMenuBgShaderResourceView->Release();
	mainMenuBgSamplerState->Release();
}