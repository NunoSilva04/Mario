#include "Coin_title.h"

COIN_TITLE::COIN_TITLE() {
	coinTitleVertexShader = nullptr;			
	coinTitlePixelShader = nullptr;
	coinTitleInputLayout = nullptr;
	coinTitleVertexBuffer = nullptr;
	coinTitleIndexBuffer = nullptr;
	coinTitleShaderResourceView = nullptr;
	coinTitleSamplerState = nullptr;

	coinTitleStruct coinTitleVertices[] = {
		{DirectX::XMFLOAT3(-1.5f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-1.3f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-1.5f, 0.8f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.3f, 0.8f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
	};
}
void COIN_TITLE::initCoinTitleShaders(ID3D11Device* dev) {
	HRESULT hr;

	//Vertex shader
	ID3D10Blob* pCoinTitleVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"CoinTitleVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pCoinTitleVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile coin title vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pCoinTitleVertexShader->GetBufferPointer(), pCoinTitleVertexShader->GetBufferSize(), nullptr,
		&coinTitleVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Pixel shader
	ID3D10Blob* pCoinTitlePixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"CoinTitlePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pCoinTitlePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile coin title pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pCoinTitlePixelShader->GetBufferPointer(), pCoinTitlePixelShader->GetBufferSize(), nullptr,
		&coinTitlePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Input Layout
	D3D11_INPUT_ELEMENT_DESC coinTitleInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(coinTitleInputLayoutDesc);

	hr = dev->CreateInputLayout(coinTitleInputLayoutDesc, size, pCoinTitleVertexShader->GetBufferPointer(),
		pCoinTitleVertexShader->GetBufferSize(), &coinTitleInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void COIN_TITLE::initCoinTitleVertexBuffer(ID3D11Device* dev){
	HRESULT hr;

	coinTitleStruct coinTitleVertices[] = {
		{DirectX::XMFLOAT3(-0.5f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.4f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.9f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.4f, 0.9f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC coinTitleVertexBufferDesc;
	ZeroMemory(&coinTitleVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	coinTitleVertexBufferDesc.ByteWidth = 4 * sizeof(coinTitleStruct);
	coinTitleVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	coinTitleVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	coinTitleVertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA coinTitleVertexBufferSubData;
	ZeroMemory(&coinTitleVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	coinTitleVertexBufferSubData.pSysMem = coinTitleVertices;

	hr = dev->CreateBuffer(&coinTitleVertexBufferDesc, &coinTitleVertexBufferSubData, &coinTitleVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void COIN_TITLE::initCoinTitleIndexBuffer(ID3D11Device* dev){
	HRESULT hr;

	DWORD coinTitleIndices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC coinTitleIndexBufferDesc;
	ZeroMemory(&coinTitleIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	coinTitleIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	coinTitleIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	coinTitleIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	coinTitleIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA coinTitleIndexBufferSubData;
	ZeroMemory(&coinTitleIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	coinTitleIndexBufferSubData.pSysMem = coinTitleIndices;

	hr = dev->CreateBuffer(&coinTitleIndexBufferDesc, &coinTitleIndexBufferSubData, &coinTitleIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void COIN_TITLE::initCoinTitleShaderResourceView(ID3D11Device* dev){
	HRESULT hr;

	//Shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"Coin_Title.png", nullptr, nullptr, &coinTitleShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title shader resource view", L"Error", MB_OK);
		exit(-1);
	}

	//Sampler State
	D3D11_SAMPLER_DESC coinTitleSamplerStateDesc;
	ZeroMemory(&coinTitleSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));

	coinTitleSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	coinTitleSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	coinTitleSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	coinTitleSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	coinTitleSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	coinTitleSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	coinTitleSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&coinTitleSamplerStateDesc, &coinTitleSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create coin title sample state", L"Error", MB_OK);
		exit(-1);
	}
}

void COIN_TITLE::renderCoinTitle(ID3D11DeviceContext* devCon){
	devCon->VSSetShader(coinTitleVertexShader, 0, 0);
	devCon->PSSetShader(coinTitlePixelShader, 0, 0);
	devCon->IASetInputLayout(coinTitleInputLayout);

	UINT strides = { sizeof(coinTitleStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &coinTitleVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(coinTitleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &coinTitleShaderResourceView);
	devCon->PSSetSamplers(0, 1, &coinTitleSamplerState);

	devCon->DrawIndexed(6, 0, 0);
}

void COIN_TITLE::cleanCoinTitle(){
	coinTitleVertexShader->Release();			
	coinTitlePixelShader->Release();
	coinTitleInputLayout->Release();
	coinTitleVertexBuffer->Release();
	coinTitleIndexBuffer->Release();
	coinTitleShaderResourceView->Release();
	coinTitleSamplerState->Release();
}