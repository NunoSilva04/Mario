#include "Mario.h"
#include "Camera.h"
#include "InputManager.h"

void MARIO::initMario(ID3D11Device* dev) {
	initMarioShaders(dev);
	initMarioVertexBuffer(dev);
	initMarioIndexBuffer(dev);
	initMarioShaderResourceView(dev);
}

void MARIO::initMarioShaders(ID3D11Device* dev){
	HRESULT hr;

	//Vertex shader
	ID3D10Blob* pMarioVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"MarioVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pMarioVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile mario vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreateVertexShader(pMarioVertexShader->GetBufferPointer(), pMarioVertexShader->GetBufferSize(), nullptr,
		&marioVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario vertex shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Pixel shader
	ID3D10Blob* pMarioPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"MarioPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pMarioPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile mario pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	hr = dev->CreatePixelShader(pMarioPixelShader->GetBufferPointer(), pMarioPixelShader->GetBufferSize(), nullptr,
		&marioPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Coudln't create mario pixel shader", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Input layout
	D3D11_INPUT_ELEMENT_DESC marioInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(marioInputLayoutDesc);

	hr = dev->CreateInputLayout(marioInputLayoutDesc, size, pMarioVertexShader->GetBufferPointer(),
		pMarioVertexShader->GetBufferSize(), &marioInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario input layout", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIO::initMarioVertexBuffer(ID3D11Device* dev){
	HRESULT hr;

	marioVertices[0] = { DirectX::XMFLOAT3(-2.0f, -0.6f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
	marioVertices[1] = { DirectX::XMFLOAT3(-1.7f, -0.6f, 0.0f), DirectX::XMFLOAT2(0.08333f, 0.0f) };
	marioVertices[2] = { DirectX::XMFLOAT3(-2.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
	marioVertices[3] = { DirectX::XMFLOAT3(-1.7f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.08333f, 1.0f) };

	D3D11_BUFFER_DESC marioVertexBufferDesc;
	ZeroMemory(&marioVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	marioVertexBufferDesc.ByteWidth = 4 * sizeof(marioVertexStruct);
	marioVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	marioVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	marioVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA marioVertexBufferSubData;
	ZeroMemory(&marioVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	marioVertexBufferSubData.pSysMem = marioVertices;

	hr = dev->CreateBuffer(&marioVertexBufferDesc, &marioVertexBufferSubData, &marioVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Coudln't create mario vertex buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIO::initMarioIndexBuffer(ID3D11Device* dev){
	HRESULT hr;

	DWORD marioIndices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC marioIndexBufferDesc;
	ZeroMemory(&marioIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	marioIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	marioIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	marioIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	marioIndexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA marioIndexBufferSubData;
	ZeroMemory(&marioIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	marioIndexBufferSubData.pSysMem = marioIndices;

	hr = dev->CreateBuffer(&marioIndexBufferDesc, &marioIndexBufferSubData, &marioIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario index buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIO::initMarioShaderResourceView(ID3D11Device* dev){
	HRESULT hr;

	//Shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"miniMario.png", nullptr, nullptr, &marioShaderResourceView, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario shader resource view", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Sampler state
	D3D11_SAMPLER_DESC marioSamplerStateDesc;
	ZeroMemory(&marioSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	marioSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	marioSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	marioSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	marioSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	marioSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	marioSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	marioSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&marioSamplerStateDesc, &marioSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create mario sampler state", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

void MARIO::updateMario(ID3D11DeviceContext* devCon, float frame_time, std::shared_ptr<IGrid> const grid,
	std::vector<std::shared_ptr<IGameObjects>> const IgameObjects) {
	prevMarioInfo = currMarioInfo;
	resetCollisions();
	if (getInput() == true) {
		moveOnXAxis(frame_time);
	}
	else {
		//Decrease velocity slowly if no input
		if (DirectX::XMVectorGetX(currMarioInfo.Vx) > 0.0f) {
			currMarioInfo.Vx = DirectX::XMVectorSet(DirectX::XMVectorGetX(currMarioInfo.Vx) - 0.05f, 0.0f, 0.0f, 0.0f);
			if (DirectX::XMVectorGetX(currMarioInfo.Vx) < 0.0f) {
				currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			}
			moveOnXAxis(frame_time);
		}
		else if (DirectX::XMVectorGetX(currMarioInfo.Vx) < 0.0f) {
			currMarioInfo.Vx = DirectX::XMVectorSet(DirectX::XMVectorGetX(currMarioInfo.Vx) + 0.05f, 0.0f, 0.0f, 0.0f);
			if (DirectX::XMVectorGetX(currMarioInfo.Vx) > 0.0f) {
				currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			}
			moveOnXAxis(frame_time);
		}
	}
	if (currMarioInfo.onGround == false) {
		moveOnYAxis(frame_time);
	}

	handleCollision(devCon, grid, IgameObjects);
	applyWallSlide();
	updateMarioState();
	animateMario(devCon);

	totalDisplacement_X = currMarioInfo.center.x - initMarioInfo.center.x;
	totalDisplacement_Y = currMarioInfo.center.y - initMarioInfo.center.y;
	marioWorld = DirectX::XMMatrixTranslation(totalDisplacement_X, totalDisplacement_Y, 0.0f);

	std::wostringstream message;
	message << L"Curr Mario Pos (" << currMarioInfo.center.x << L", " << currMarioInfo.center.y << L")\n";
	message << L"Curr Mario TopLeft (" << currMarioInfo.topLeft.x << L", " << currMarioInfo.topLeft.y << L")\n";
	message << L"Curr Mario BottomRight (" << currMarioInfo.bottomRight.x << L", " << currMarioInfo.bottomRight.y << L")\n";
	message << L"Curr Mario Vx (" << DirectX::XMVectorGetX(currMarioInfo.Vx) << L", " << DirectX::XMVectorGetY(currMarioInfo.Vx) << L")\n";
	message << L"Curr Mario Vy (" << DirectX::XMVectorGetX(currMarioInfo.Vy) << L", " << DirectX::XMVectorGetY(currMarioInfo.Vy) << L")\n";
	//OutputDebugString(message.str().c_str());
}

void MARIO::renderMario(ID3D11DeviceContext* devCon){
	devCon->VSSetShader(marioVertexShader, 0, 0);
	devCon->PSSetShader(marioPixelShader, 0, 0);
	devCon->IASetInputLayout(marioInputLayout);

	UINT strides = { sizeof(marioVertexStruct) };
	UINT offset = { 0 };
	devCon->IASetVertexBuffers(0, 1, &marioVertexBuffer, &strides, &offset);
	devCon->IASetIndexBuffer(marioIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(0, 1, &marioShaderResourceView);
	devCon->PSSetSamplers(0, 1, &marioSamplerState);

	Camera.WVP = marioWorld * Camera.CamView * Camera.CamProjection;
	Camera.WVPInformationStruct.WVPInformationMatrix = DirectX::XMMatrixTranspose(Camera.WVP);
	devCon->UpdateSubresource(Camera.WVPBuffer, 0, nullptr, &Camera.WVPInformationStruct, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &Camera.WVPBuffer);

	devCon->DrawIndexed(6, 0, 0);
}

void MARIO::cleanMario(){
	marioVertexShader->Release();
	marioPixelShader->Release();
	marioInputLayout->Release();
	marioVertexBuffer->Release();
	marioIndexBuffer->Release();
	marioShaderResourceView->Release();
	marioSamplerState->Release();
}