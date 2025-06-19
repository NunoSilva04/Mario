#include "UnbreakableBrick.h"
#include "Id3d.h"

UnbreakableBrick::UnbreakableBrick() {
	instanceBuffer = nullptr;
}

UnbreakableBrick::~UnbreakableBrick() {

}

void UnbreakableBrick::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	//Any changes done in the vertices, also must be done in each child class instances 
	DirectX::XMFLOAT3 v0, v1, v2, v3;
	v0 = DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f);
	v1 = DirectX::XMFLOAT3(-2.5f, -1.0f, 0.0f);
	v2 = DirectX::XMFLOAT3(-3.0f, -1.5f, 0.0f);
	v3 = DirectX::XMFLOAT3(-2.5f, -1.5f, 0.0f);
	DirectX::XMVECTOR tempVec;
	instanceStruct tempInstance;
	int index = 0;
	float offsetX = 70.0f, offsetY = 0.5f;
	int numRows = 3, numCollumns = 3; 

	//Upstairs
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCollumns; j++) {
			tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
			tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 6, 0.0f);
			tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 7, 0.0f);
			tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 6, 0.33333f);
			tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 7, 0.33333f);
			tempInstance.instanceID = index;
			tempVec = DirectX::XMLoadFloat3(&v0);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[0], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v1);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[1], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v2);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[2], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v3);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[3], tempVec);
			instances.push_back(tempInstance);
			initNumInstances.push_back(tempInstance);
			index++;
			offsetX += 0.5f;
		}
		numCollumns -= 1;
		offsetY += 0.5f;
		offsetX -= 0.5f * numCollumns;
	}

	//Downstairs
	numRows = 3; numCollumns = 3;
	offsetX = 72.5f; offsetY = 0.5f;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCollumns; j++) {
			tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
			tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 6, 0.0f);
			tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 7, 0.0f);
			tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 6, 0.33333f);
			tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 7, 0.33333f);
			tempInstance.instanceID = index;
			tempVec = DirectX::XMLoadFloat3(&v0);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[0], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v1);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[1], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v2);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[2], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v3);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[3], tempVec);
			instances.push_back(tempInstance);
			initNumInstances.push_back(tempInstance);
			index++;
			offsetX += 0.5f;
		}
		numCollumns -= 1;
		offsetY += 0.5f;
		offsetX = 72.5f;
	}

	//Upstairs
	offsetX = 76.0f, offsetY = 0.5f;
	numRows = 3, numCollumns = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCollumns; j++) {
			tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
			tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 6, 0.0f);
			tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 7, 0.0f);
			tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 6, 0.33333f);
			tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 7, 0.33333f);
			tempInstance.instanceID = index;
			tempVec = DirectX::XMLoadFloat3(&v0);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[0], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v1);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[1], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v2);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[2], tempVec);
			tempVec = DirectX::XMLoadFloat3(&v3);
			tempVec = DirectX::XMVector3Transform(tempVec, tempInstance.transformMatrix);
			DirectX::XMStoreFloat3(&tempInstance.verticesPos[3], tempVec);
			instances.push_back(tempInstance);
			initNumInstances.push_back(tempInstance);
			index++;
			offsetX += 0.5f;
		}
		numCollumns -= 1;
		offsetY += 0.5f;
		offsetX -= 0.5f * numCollumns;
	}

	D3D11_BUFFER_DESC instanceBufferDesc;
	ZeroMemory(&instanceBufferDesc, sizeof(D3D11_BUFFER_DESC));
	instanceBufferDesc.ByteWidth = instances.size() * sizeof(instanceStruct);
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA instanceBufferSubData;
	ZeroMemory(&instanceBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	instanceBufferSubData.pSysMem = instances.data();

	hr = dev->CreateBuffer(&instanceBufferDesc, &instanceBufferSubData, instanceBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString(L"Couldn't create block instance buffer\n");
		PostQuitMessage(0);
	}
}

const Microsoft::WRL::ComPtr<ID3D11Buffer> UnbreakableBrick::getInstanceBuffer() const {
	return instanceBuffer;
}

const UINT UnbreakableBrick::getSizeofInstanceStruct() const {
	return sizeof(instanceStruct);
}

const int UnbreakableBrick::getNumBlockTypeInstances() {
	return instances.size();
}

const int UnbreakableBrick::getNumBlockTypeInstancesToRender() const {
	return instancesToRender.size();
}

const DirectX::XMFLOAT3 UnbreakableBrick::getInstanceVertice(int ID, int verticeNumber) {
	return instances[ID].verticesPos[verticeNumber];
}

void UnbreakableBrick::resetInstances() {
	instancesToRender = std::vector<instanceStruct>();
}

void UnbreakableBrick::addIstance(int instanceID) {
	instanceStruct newInstance;
	newInstance.instanceID = instanceID;
	newInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 6, 0.0f);
	newInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 7, 0.0f);
	newInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 6, 0.33333f);
	newInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 7, 0.33333f);
	newInstance.transformMatrix = initNumInstances[instanceID].transformMatrix;
	newInstance.verticesPos[0] = initNumInstances[instanceID].verticesPos[0];
	newInstance.verticesPos[1] = initNumInstances[instanceID].verticesPos[1];
	newInstance.verticesPos[2] = initNumInstances[instanceID].verticesPos[2];
	newInstance.verticesPos[3] = initNumInstances[instanceID].verticesPos[3];
	instancesToRender.push_back(newInstance);
}

void UnbreakableBrick::updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) {
	HRESULT hr;

	if (instancesToRender.size() > initNumInstances.size()) {
		instanceBuffer.Reset();
		D3D11_BUFFER_DESC instanceBufferDesc;
		ZeroMemory(&instanceBufferDesc, sizeof(D3D11_BUFFER_DESC));
		instanceBufferDesc.ByteWidth = instancesToRender.size() * sizeof(instanceStruct);
		instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA instanceBufferSubData;
		ZeroMemory(&instanceBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
		instanceBufferSubData.pSysMem = instancesToRender.data();

		Id3d* tempDev = Id3d::createInstance();
		hr = tempDev->getDevice()->CreateBuffer(&instanceBufferDesc, &instanceBufferSubData, instanceBuffer.GetAddressOf());
		if (FAILED(hr)) {
			OutputDebugString(L"Couldn't create block instance buffer\n");
			PostQuitMessage(0);
		}
		delete tempDev;
	}
	else {
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		hr = devCon->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		if (SUCCEEDED(hr)) {
			memcpy(mappedSubResource.pData, instancesToRender.data(), sizeof(instancesToRender[0]) * instancesToRender.size());
			devCon->Unmap(instanceBuffer.Get(), 0);
		}
		else {
			OutputDebugString(L"Couln't map floor tile instance buffer\n");
			PostQuitMessage(0);
		}
	}
}

void UnbreakableBrick::getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const {
	positions[0] = initNumInstances[currInstance].verticesPos[0];
	positions[1] = initNumInstances[currInstance].verticesPos[1];
	positions[2] = initNumInstances[currInstance].verticesPos[2];
	positions[3] = initNumInstances[currInstance].verticesPos[3];
}