#include "Block.h"
#include "FloorTile.h"
#include "DarkFloorTile.h"
#include "Brick.h"
#include "DarkBrick.h"
#include "MysteryBlock.h"
#include "UnbreakableBrick.h"
#include "Pipe.h"
#include "IGrid.h"

namespace wrl = Microsoft::WRL;

wrl::ComPtr<ID3D11VertexShader> Block::vertexShader = nullptr;
wrl::ComPtr<ID3D11PixelShader> Block::pixelShader = nullptr;
wrl::ComPtr<ID3D11SamplerState> Block::samplerState = nullptr;
wrl::ComPtr<ID3D11InputLayout> Block::inputLayout = nullptr;
wrl::ComPtr<ID3D11Buffer> Block::vertexBuffer = nullptr;
wrl::ComPtr<ID3D11Buffer> Block::indexBuffer = nullptr;
wrl::ComPtr<ID3D11ShaderResourceView> Block::shaderResourceView = nullptr;
bool Block::hasShader = false;
bool Block::hasVertexBuffer = false;
bool Block::hasIndexBuffer = false;
bool Block::hasSRV = false;
std::vector<std::shared_ptr<Block>> Block::allBlockArray;

Block::Block() {
	
}

Block::~Block() {

}

std::shared_ptr<GameObjects> Block::createBlockType(const std::string specificType) {
	if (specificType == "FloorTile") {
		allBlockArray.push_back(std::make_shared<FloorTile>());
		return allBlockArray[0];
	}
	if (specificType == "DarkFloorTile") {
		allBlockArray.push_back(std::make_shared<DarkFloorTile>());
		return nullptr;
	}
	if (specificType == "Brick") {
		allBlockArray.push_back(std::make_shared<Brick>());
		return nullptr;
	}
	if (specificType == "DarkBrick") {
		allBlockArray.push_back(std::make_shared<DarkBrick>());
		return nullptr;
	}
	if (specificType == "MysteryBlock") {
		allBlockArray.push_back(std::make_shared<MysteryBlock>());
		return nullptr;
	}
	if (specificType == "UnbreakableBrick") {
		allBlockArray.push_back(std::make_shared<UnbreakableBrick>());
		return nullptr;
	}
	if (specificType == "Pipe") {
		allBlockArray.push_back(std::make_shared<Pipe>());
		return nullptr;
	}
}

void Block::initObject(ID3D11Device* dev){
	for (int i = 0; i < allBlockArray.size(); i++) {
		if (!hasShader) {
			allBlockArray[i]->initBlockShaders(dev);
			hasShader = true;
		}
		if (!hasVertexBuffer) {
			allBlockArray[i]->initBlockVertexBuffer(dev);
			hasVertexBuffer = true;
		}
		if (!hasIndexBuffer) {
			allBlockArray[i]->initBlockIndexBuffer(dev);
			hasIndexBuffer = true;
		}
		if (!hasSRV) {
			allBlockArray[i]->initBlockShaderResourceView(dev);
			hasSRV = true;
		}
		allBlockArray[i]->initInstanceBuffer(dev);
	}
}

void Block::initBlockShaders(ID3D11Device* dev){
	HRESULT hr;

	//Vertex shader
	wrl::ComPtr<ID3D10Blob> pVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"BlockVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, pVertexShader.GetAddressOf(), 0, 0);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't compile block vertex shader\n");
		PostQuitMessage(0);
	}

	hr = dev->CreateVertexShader(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), nullptr,
		vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create block vertex shader\n");
		PostQuitMessage(0);
	}

	//Pixel shader 
	wrl::ComPtr<ID3D10Blob> pPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"BlockPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, pPixelShader.GetAddressOf(), 0, 0);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't compile block pixel shader\n");
		PostQuitMessage(0);
	}

	hr = dev->CreatePixelShader(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize(), nullptr,
		pixelShader.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create block pixel shader\n");
		PostQuitMessage(0);
	}

	//Input layout
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TRANSFORM_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TRANSFORM_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"V0_UV", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"V1_UV", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"V2_UV", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"V3_UV", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	};
	UINT size = ARRAYSIZE(inputLayoutDesc);

	hr = dev->CreateInputLayout(inputLayoutDesc, size, pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(),
		inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create block input layout\n");
		PostQuitMessage(0);
	}
}

void Block::initBlockVertexBuffer(ID3D11Device* dev){
	HRESULT hr;

	//Any changes done in the vertices, also must be done in each child class instances 
	vertexStruct vertices[] = {
		{DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-2.5f, -1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-3.0f, -1.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-2.5f, -1.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
	};

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
		OutputDebugString(L"Couldn't create block vertex buffer\n");
		PostQuitMessage(0);
	}
}

void Block::initBlockIndexBuffer(ID3D11Device* dev){
	HRESULT hr;

	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
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
		OutputDebugString(L"Couldn't create block index buffer\n");
		PostQuitMessage(0);
	}
}

void Block::initBlockShaderResourceView(ID3D11Device* dev){
	HRESULT hr;

	//Shader Resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"BlockTextures.png", nullptr, nullptr, shaderResourceView.GetAddressOf(),
		nullptr);
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create block texture\n");
		PostQuitMessage(0);
	}

	//Sampler state
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
		OutputDebugString(L"Couldn't create sampler state\n");
		PostQuitMessage(0);
	}
}

void Block::updateObject(ID3D11DeviceContext* devCon, std::shared_ptr<IGrid> const IGridsToUse) {
	for (int i = 0; i < allBlockArray.size(); i++) {
		allBlockArray[i]->resetInstances();
	}

	int numGrids = IGridsToUse->getNumGridsRendered();
	for (int currGrid = 0; currGrid < numGrids; currGrid++) {
		int numObjects = IGridsToUse->getCurrGridNumObjects(currGrid);
		for (int currObject = 0; currObject < numObjects; currObject++) {
			int objectSubType = IGridsToUse->getObjectSubType(currGrid, currObject);
			int instanceID = IGridsToUse->getObjectSubTypeInstanceID(currGrid, currObject);
			allBlockArray[objectSubType]->addIstance(instanceID);
		}
	}
	
	for (int i = 0; i < allBlockArray.size(); i++) {
		allBlockArray[i]->updateBlockTypeInstanceBuffer(devCon);
	}
}

void Block::renderObject(ID3D11DeviceContext* devCon) {
	for (int i = 0; i < allBlockArray.size(); i++) {
		wrl::ComPtr<ID3D11Buffer> buffers[] = { vertexBuffer, allBlockArray[i]->getInstanceBuffer() };
		UINT strides[] = { sizeof(vertexStruct), allBlockArray[i]->getSizeofInstanceStruct() };
		UINT offset[] = { 0,0 };
		devCon->IASetInputLayout(inputLayout.Get());
		devCon->IASetVertexBuffers(0, 2, buffers->GetAddressOf(), strides, offset);
		devCon->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		devCon->VSSetShader(vertexShader.Get(), 0, 0);

		devCon->PSSetShader(pixelShader.Get(), 0, 0);
		devCon->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
		devCon->PSSetSamplers(0, 1, samplerState.GetAddressOf());

		devCon->DrawIndexedInstanced(6, allBlockArray[i]->getNumBlockTypeInstancesToRender(), 0, 0, 0);
	}
}

int Block::getNumObjectSubType() const {
	return allBlockArray.size();
}

int Block::getObjectSubTypeNumInstances(int currObjectSubType) const {
	return allBlockArray[currObjectSubType]->getNumBlockTypeInstances();
}

void Block::getObjectSubTypePosition(int currObjectSubType, DirectX::XMFLOAT3* positions, int currInstance) const {
	return allBlockArray[currObjectSubType]->getVerticesPosition(positions, currInstance);
}