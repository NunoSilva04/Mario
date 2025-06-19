#include "MysteryBlock.h"
#include "Id3d.h"

MysteryBlock::MysteryBlock() {
	instanceBuffer = nullptr;
}

MysteryBlock::~MysteryBlock() {

}

void MysteryBlock::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	//Any changes done in the vertices, also must be done in each child class instances 
	DirectX::XMFLOAT3 v0, v1, v2, v3;
	v0 = DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f);
	v1 = DirectX::XMFLOAT3(-2.5f, -1.0f, 0.0f);
	v2 = DirectX::XMFLOAT3(-3.0f, -1.5f, 0.0f);
	v3 = DirectX::XMFLOAT3(-2.5f, -1.5f, 0.0f);
	DirectX::XMVECTOR tempVec;
	int numInstancesToCreate = 3;			//12 Total
	float offsetX = 6.5f, offsetY = 1.4f;
	//1
	instanceStruct tempInstance;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//2
	offsetX = 9.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//3
	offsetX = 10.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//4
	offsetX = 10.0f; offsetY = 2.8f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//5
	offsetX = 35.0f; offsetY = 1.4f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//6
	offsetX = 42.0f; offsetY = 1.4f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//7
	offsetX = 49.5f; offsetY = 2.8f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//8
	offsetX = 54.5f; offsetY = 1.4f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//8
	offsetX = 55.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//9
	offsetX = 56.5f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//10
	offsetX = 55.5f; offsetY = 2.8f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//11
	offsetX = 66.5f; offsetY = 2.8f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
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

	//12
	offsetX = 67.0f; offsetY = 2.8f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
	tempInstance.instanceID = 11;
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

const Microsoft::WRL::ComPtr<ID3D11Buffer> MysteryBlock::getInstanceBuffer() const {
	return instanceBuffer;
}

const UINT MysteryBlock::getSizeofInstanceStruct() const {
	return sizeof(instanceStruct);
}

const int MysteryBlock::getNumBlockTypeInstances() {
	return instances.size();
}

const int MysteryBlock::getNumBlockTypeInstancesToRender() const {
	return instancesToRender.size();
}

const DirectX::XMFLOAT3 MysteryBlock::getInstanceVertice(int ID, int verticeNumber) {
	return instances[ID].verticesPos[verticeNumber];
}

void MysteryBlock::resetInstances() {
	instancesToRender = std::vector<instanceStruct>();
}

void MysteryBlock::addIstance(int instanceID) {
	instanceStruct newInstance;
	newInstance.instanceID = instanceID;
	newInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 4, 0.0f);
	newInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 5, 0.0f);
	newInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 4, 0.33333f);
	newInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 5, 0.33333f);
	newInstance.transformMatrix = initNumInstances[instanceID].transformMatrix;
	newInstance.verticesPos[0] = initNumInstances[instanceID].verticesPos[0];
	newInstance.verticesPos[1] = initNumInstances[instanceID].verticesPos[1];
	newInstance.verticesPos[2] = initNumInstances[instanceID].verticesPos[2];
	newInstance.verticesPos[3] = initNumInstances[instanceID].verticesPos[3];
	instancesToRender.push_back(newInstance);
}

void MysteryBlock::updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) {
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

void MysteryBlock::getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const {
	positions[0] = initNumInstances[currInstance].verticesPos[0];
	positions[1] = initNumInstances[currInstance].verticesPos[1];
	positions[2] = initNumInstances[currInstance].verticesPos[2];
	positions[3] = initNumInstances[currInstance].verticesPos[3];
}