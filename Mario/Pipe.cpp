#include "Pipe.h"
#include "Id3d.h"

Pipe::Pipe() {
	instanceBuffer = nullptr;
}

Pipe::~Pipe() {

}

void Pipe::initInstanceBuffer(ID3D11Device* dev) {		// 6 Total Instances
	HRESULT hr;

	//Any changes done in the vertices, also must be done in each child class instances 
	DirectX::XMFLOAT3 v0, v1, v2, v3;
	v0 = DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f);
	v1 = DirectX::XMFLOAT3(-2.5f, -1.0f, 0.0f);
	v2 = DirectX::XMFLOAT3(-3.0f, -1.5f, 0.0f);
	v3 = DirectX::XMFLOAT3(-2.5f, -1.5f, 0.0f);
	DirectX::XMVECTOR tempVec;
	float offsetX = 13.0f, offsetY = 0.5f;
	instanceStruct tempInstance;

	//0 (small pipe)
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 0;
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

	//1 and 2 (medium pipe - goes from bottom to top)
	offsetX = 20.0f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 4, 1.0f);
	tempInstance.instanceID = 1;
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

	offsetX = 20.0f; offsetY += 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 2;
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

	//3, 4 and 5  (Tall pipe - goes from bottom to top 
	offsetX = 25.0f; offsetY = 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 4, 1.0f);
	tempInstance.instanceID = 3;
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
	
	offsetY += 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 4, 1.0f);
	tempInstance.instanceID = 4;
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

	offsetY += 0.25f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 5;
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

	//6, 7 and 8 (Tall pipe - goes from bottom to top)
	offsetX = 30.0f; offsetY = 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 4, 1.0f);
	tempInstance.instanceID = 6;
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

	offsetY += 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 4, 1.0f);
	tempInstance.instanceID = 7;
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

	offsetY += 0.25f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 8;
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

	//9 (small pipe)
	offsetX = 83.0f; offsetY = 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 9;
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

	//10 (small pipe) 
	offsetX = 93.0f; offsetY = 0.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 0, 0.33333f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 0, 1.0f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 2, 1.0f);
	tempInstance.instanceID = 10;
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

const Microsoft::WRL::ComPtr<ID3D11Buffer> Pipe::getInstanceBuffer() const {
	return instanceBuffer;
}

const UINT Pipe::getSizeofInstanceStruct() const {
	return sizeof(instanceStruct);
}

const int Pipe::getNumBlockTypeInstances() {
	return instances.size();
}

const int Pipe::getNumBlockTypeInstancesToRender() const {
	return instancesToRender.size();
}

const DirectX::XMFLOAT3 Pipe::getInstanceVertice(int ID, int verticeNumber) {
	return instances[ID].verticesPos[verticeNumber];
}

void Pipe::resetInstances() {
	instancesToRender = std::vector<instanceStruct>();
}

void Pipe::addIstance(int instanceID) {
	instanceStruct newInstance;
	newInstance.instanceID = instanceID;
	newInstance.newUVValues[0] = initNumInstances[instanceID].newUVValues[0];
	newInstance.newUVValues[1] = initNumInstances[instanceID].newUVValues[1];
	newInstance.newUVValues[2] = initNumInstances[instanceID].newUVValues[2];
	newInstance.newUVValues[3] = initNumInstances[instanceID].newUVValues[3];
	newInstance.transformMatrix = initNumInstances[instanceID].transformMatrix;
	newInstance.verticesPos[0] = initNumInstances[instanceID].verticesPos[0];
	newInstance.verticesPos[1] = initNumInstances[instanceID].verticesPos[1];
	newInstance.verticesPos[2] = initNumInstances[instanceID].verticesPos[2];
	newInstance.verticesPos[3] = initNumInstances[instanceID].verticesPos[3];
	instancesToRender.push_back(newInstance);
}

void Pipe::updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) {
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

void Pipe::getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const {
	positions[0] = initNumInstances[currInstance].verticesPos[0];
	positions[1] = initNumInstances[currInstance].verticesPos[1];
	positions[2] = initNumInstances[currInstance].verticesPos[2];
	positions[3] = initNumInstances[currInstance].verticesPos[3];
}