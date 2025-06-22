#include "MarioMainMenu.h"
#include "Camera.h"

void MARIOMAINMENU::initMarioMainMenu(ID3D11Device* dev) {
	initMarioMainMenuShaders(dev);
	initMarioMainMenuVertexBuffer(dev);
	initMarioMainMenuIndexBuffer(dev);
	initMarioMainMenuShaderResourceView(dev);
}

void MARIOMAINMENU::initMarioMainMenuShaders(ID3D11Device* dev) {
	HRESULT hr;

	//Vertex shader
	ID3D10Blob* pMarioMainMenuVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"MarioMainMenuVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pMarioMainMenuVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile mario main menu vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreateVertexShader(pMarioMainMenuVertexShader->GetBufferPointer(), pMarioMainMenuVertexShader->GetBufferSize(),
		nullptr, &marioMainMenuVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Pixel shader
	ID3D10Blob* pMarioMainMenuPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"MarioMainMenuPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pMarioMainMenuPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Coudn't compile mario main menu pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreatePixelShader(pMarioMainMenuPixelShader->GetBufferPointer(), pMarioMainMenuPixelShader->GetBufferSize(),
		nullptr, &marioMainMenuPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Input Layout
	D3D11_INPUT_ELEMENT_DESC marioMainMenuInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(marioMainMenuInputLayoutDesc);

	hr = dev->CreateInputLayout(marioMainMenuInputLayoutDesc, size, pMarioMainMenuVertexShader->GetBufferPointer(),
		pMarioMainMenuVertexShader->GetBufferSize(), &marioMainMenuInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu input layout", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIOMAINMENU::initMarioMainMenuVertexBuffer(ID3D11Device* dev){
	HRESULT hr;

	marioMainMenuVertices[0] = { DirectX::XMFLOAT3(-1.5f, -0.61f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	marioMainMenuVertices[1] = { DirectX::XMFLOAT3(-1.3f, -0.61f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	marioMainMenuVertices[2] = { DirectX::XMFLOAT3(-1.5f, -0.81f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	marioMainMenuVertices[3] = { DirectX::XMFLOAT3(-1.3f, -0.81f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };

	D3D11_BUFFER_DESC marioMainMenuVertexBufferDesc;
	ZeroMemory(&marioMainMenuVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	marioMainMenuVertexBufferDesc.ByteWidth = 4 * sizeof(marioMainMenuStruct);
	marioMainMenuVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	marioMainMenuVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	marioMainMenuVertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA marioMainMenuVertexBufferSubData;
	ZeroMemory(&marioMainMenuVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	marioMainMenuVertexBufferSubData.pSysMem = marioMainMenuVertices;

	hr = dev->CreateBuffer(&marioMainMenuVertexBufferDesc, &marioMainMenuVertexBufferSubData, &marioMainMenuVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu vertex buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIOMAINMENU::initMarioMainMenuIndexBuffer(ID3D11Device* dev){
	HRESULT hr;

	DWORD marioMainMenuIndices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC marioMainMenuIndexBufferDesc;
	ZeroMemory(&marioMainMenuIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	marioMainMenuIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	marioMainMenuIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	marioMainMenuIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	marioMainMenuIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA marioMainMenuIndexBufferSubData;
	ZeroMemory(&marioMainMenuIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	marioMainMenuIndexBufferSubData.pSysMem = marioMainMenuIndices;

	hr = dev->CreateBuffer(&marioMainMenuIndexBufferDesc, &marioMainMenuIndexBufferSubData, &marioMainMenuIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu index buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIOMAINMENU::initMarioMainMenuShaderResourceView(ID3D11Device* dev){
	HRESULT hr;
	
	//Shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"marioMainMenu.png", nullptr, nullptr, &marioMainMenuShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu shader resource view", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Sampler state
	D3D11_SAMPLER_DESC marioMainMenuSamplerStateDesc;
	ZeroMemory(&marioMainMenuSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	marioMainMenuSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	marioMainMenuSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	marioMainMenuSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	marioMainMenuSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	marioMainMenuSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	marioMainMenuSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	marioMainMenuSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&marioMainMenuSamplerStateDesc, &marioMainMenuSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario main menu sampler state", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIOMAINMENU::updateMarioMainMenu(ID3D11DeviceContext* devCon) {
	marioMainMenuWorld = DirectX::XMMatrixTranslation(1.1f, 0.6f, 0.0f);
}

void MARIOMAINMENU::updateMarioMainMenu() {
	marioMainMenuWorld = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
}

void MARIOMAINMENU::renderMarioMainMenu(ID3D11DeviceContext* devCon){
	devCon->VSSetShader(marioMainMenuVertexShader, 0, 0);
	devCon->PSSetShader(marioMainMenuPixelShader, 0, 0);
	devCon->IASetInputLayout(marioMainMenuInputLayout);

	UINT strides = { sizeof(marioMainMenuStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &marioMainMenuVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(marioMainMenuIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &marioMainMenuShaderResourceView);
	devCon->PSSetSamplers(0, 1, &marioMainMenuSamplerState);

	Camera.WVP = marioMainMenuWorld * Camera.CamView * Camera.CamProjection;
	Camera.WVPInformationStruct.WVPInformationMatrix = DirectX::XMMatrixTranspose(Camera.WVP);
	devCon->UpdateSubresource(Camera.WVPBuffer, 0, nullptr, &Camera.WVPInformationStruct, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);

	devCon->DrawIndexed(6, 0, 0);
}

void MARIOMAINMENU::cleanMarioMainMenu(){
	marioMainMenuVertexShader->Release();
	marioMainMenuPixelShader->Release();
	marioMainMenuInputLayout->Release();
	marioMainMenuVertexBuffer->Release();
	marioMainMenuIndexBuffer->Release();
	marioMainMenuShaderResourceView->Release();
	marioMainMenuSamplerState->Release();
}