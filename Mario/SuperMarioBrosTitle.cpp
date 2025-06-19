#include "SuperMarioBrosTitle.h"
#include "Camera.h"

SUPERMARIOBROSTITLE::SUPERMARIOBROSTITLE() {
	superMarioBrosTitleVertexShader = nullptr;
	superMarioBrosTitlePixelShader = nullptr;
	superMarioBrosTitleInputLayout = nullptr;
	superMarioBrosTitleVertexBuffer = nullptr;
	superMarioBrosTitleIndexBuffer = nullptr;
	superMarioBrosTitleShaderResourceView = nullptr;
	superMarioBrosTitleSamplerState = nullptr;

	superMarioBrosVertices[0] = { DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	superMarioBrosVertices[1] = { DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	superMarioBrosVertices[2] = { DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	superMarioBrosVertices[3] = { DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f),  DirectX::XMFLOAT2(1.0f, 1.0f) };
}

void SUPERMARIOBROSTITLE::initSuperMarioBrosTitleShaders(ID3D11Device* dev) {
	HRESULT hr;

	//Super mario bros title vertex shader
	ID3D10Blob* pSuperMarioBrosVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"SuperMarioBrosTitleVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pSuperMarioBrosVertexShader,
		0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile Super Mario Bros title vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pSuperMarioBrosVertexShader->GetBufferPointer(), pSuperMarioBrosVertexShader->GetBufferSize(),
		0, &superMarioBrosTitleVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Super mario bros title pixel shader
	ID3D10Blob* pSuperMarioBrosTitlePixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"SuperMarioBrosTitlePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, 
		&pSuperMarioBrosTitlePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile super mario bros title pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pSuperMarioBrosTitlePixelShader->GetBufferPointer(), pSuperMarioBrosTitlePixelShader->GetBufferSize(),
		0, &superMarioBrosTitlePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Super mario bros title input layout
	D3D11_INPUT_ELEMENT_DESC superMarioBrosTitleInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(superMarioBrosTitleInputLayoutDesc);

	hr = dev->CreateInputLayout(superMarioBrosTitleInputLayoutDesc, size, pSuperMarioBrosVertexShader->GetBufferPointer(),
		pSuperMarioBrosVertexShader->GetBufferSize(), &superMarioBrosTitleInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void SUPERMARIOBROSTITLE::initSuperMarioBrosTitleVertexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	superMarioBrosVertices[0] = { DirectX::XMFLOAT3(-1.3f, 0.9f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	superMarioBrosVertices[1] = { DirectX::XMFLOAT3(1.3f, 0.9f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };
	superMarioBrosVertices[2] = { DirectX::XMFLOAT3(-1.3f, -0.1f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	superMarioBrosVertices[3] = { DirectX::XMFLOAT3(1.3f, -0.1f, 0.0f),  DirectX::XMFLOAT2(1.0f, 1.0f) };

	D3D11_BUFFER_DESC superMarioBrosTitleVertexBufferDesc;
	ZeroMemory(&superMarioBrosTitleVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	superMarioBrosTitleVertexBufferDesc.ByteWidth = 4 * sizeof(superMarioBrosTitleStruct);
	superMarioBrosTitleVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	superMarioBrosTitleVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	superMarioBrosTitleVertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA superMarioBrosTitleVertexBufferSubData;
	ZeroMemory(&superMarioBrosTitleVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	superMarioBrosTitleVertexBufferSubData.pSysMem = superMarioBrosVertices;

	hr = dev->CreateBuffer(&superMarioBrosTitleVertexBufferDesc, &superMarioBrosTitleVertexBufferSubData, 
		&superMarioBrosTitleVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void SUPERMARIOBROSTITLE::initSuperMarioBrosTitleIndexBuffer(ID3D11Device* dev) {
	HRESULT hr;

	DWORD superMarioBrosIndices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC superMarioBrosTitleIndexBufferDesc;
	ZeroMemory(&superMarioBrosTitleIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	superMarioBrosTitleIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	superMarioBrosTitleIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	superMarioBrosTitleIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	superMarioBrosTitleIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA superMarioBrosTitleIndexBufferSubData;
	ZeroMemory(&superMarioBrosTitleIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));

	superMarioBrosTitleIndexBufferSubData.pSysMem = superMarioBrosIndices;

	hr = dev->CreateBuffer(&superMarioBrosTitleIndexBufferDesc, &superMarioBrosTitleIndexBufferSubData,
		&superMarioBrosTitleIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void SUPERMARIOBROSTITLE::initSuperMarioBrosTitleTexture(ID3D11Device* dev) {
	HRESULT hr;

	//Shader Resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"SuperMarioBrosTitle.png", nullptr, nullptr,
		&superMarioBrosTitleShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create super mario bros title shader resource view", L"Error", MB_OK);
		exit(-1);
	}

	//Sampler state
	D3D11_SAMPLER_DESC superMarioBrosTitleSamplerStateDesc;
	ZeroMemory(&superMarioBrosTitleSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));

	superMarioBrosTitleSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	superMarioBrosTitleSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	superMarioBrosTitleSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	superMarioBrosTitleSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	superMarioBrosTitleSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	superMarioBrosTitleSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	superMarioBrosTitleSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&superMarioBrosTitleSamplerStateDesc, &superMarioBrosTitleSamplerState);
	if(FAILED(hr)){
		MessageBox(nullptr, L"Couldn't create super mario bros title sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void SUPERMARIOBROSTITLE::renderSuperMarioBrosTitle(ID3D11DeviceContext* devCon) {
	devCon->VSSetShader(superMarioBrosTitleVertexShader, 0, 0);
	devCon->PSSetShader(superMarioBrosTitlePixelShader, 0, 0);
	devCon->IASetInputLayout(superMarioBrosTitleInputLayout);

	UINT strides = { sizeof(superMarioBrosTitleStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &superMarioBrosTitleVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(superMarioBrosTitleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &superMarioBrosTitleShaderResourceView);
	devCon->PSSetSamplers(0, 1, &superMarioBrosTitleSamplerState);

	Camera.WVP = Camera.World * Camera.CamView * Camera.CamProjection;
	Camera.WVPInformationStruct.WVPInformationMatrix = DirectX::XMMatrixTranspose(Camera.WVP);
	devCon->UpdateSubresource(Camera.WVPBuffer, 0, nullptr, &Camera.WVPInformationStruct, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);

	devCon->DrawIndexed(6, 0, 0);
}

void SUPERMARIOBROSTITLE::cleanSuperMarioBrosTitle() {
	superMarioBrosTitleVertexShader->Release();
	superMarioBrosTitlePixelShader->Release();
	superMarioBrosTitleInputLayout->Release();
	superMarioBrosTitleVertexBuffer->Release();
	superMarioBrosTitleIndexBuffer->Release();
	superMarioBrosTitleShaderResourceView->Release();
	superMarioBrosTitleSamplerState->Release();
}