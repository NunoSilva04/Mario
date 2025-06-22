#include "Brick.h"
#include "Id3d.h"

Brick::Brick() {
	instanceBuffer = nullptr;
}

Brick::~Brick() {

}

void Brick::initInstanceBuffer(ID3D11Device* dev) {
	HRESULT hr;

	//Any changes done in the vertices, also must be done in each child class instances 
	DirectX::XMFLOAT3 v0, v1, v2, v3;
	v0 = DirectX::XMFLOAT3(-3.0f, -1.0f, 0.0f);
	v1 = DirectX::XMFLOAT3(-2.5f, -1.0f, 0.0f);
	v2 = DirectX::XMFLOAT3(-3.0f, -1.5f, 0.0f);
	v3 = DirectX::XMFLOAT3(-2.5f, -1.5f, 0.0f);
	DirectX::XMVECTOR tempVec;
	int numInstancesToCreate = 3;
	float offsetX = 9.0f, offsetY = 1.4f;
	int index = 0;
	for (; index < numInstancesToCreate; index++) {
		instanceStruct tempInstance;
		tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
		tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
		tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
		tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
		tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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
		offsetX += 1.0f;
	}

	//3
	offsetX = 41.5f;
	instanceStruct tempInstance;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//4
	index++; offsetX += 1.0f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//5 - 11
	index++; offsetX += 0.5f; offsetY = 2.8f;
	for (; index < 12; index++) {
		tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
		tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
		tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
		tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
		tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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
		offsetX += 0.5f;
	}

	//12 - 14
	offsetX += 1.5f;
	for (; index < 15; index++) {
		tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
		tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
		tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
		tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
		tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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
		offsetX += 0.5f;
	}

	//15
	offsetY = 1.4f;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//16
	offsetX += 2.5f;  offsetY = 1.4f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//17
	offsetX += 0.5f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//18
	offsetX += 9.5f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//19
	offsetX += 1.0f; offsetY = 2.8f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//20
	offsetX += 0.5f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//21
	offsetX += 0.5f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//22
	offsetX += 2.0f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//23
	offsetX += 0.5f; offsetY = 1.4f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//24
	offsetX += 0.5f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//25
	offsetX += 0.5f; offsetY = 2.8f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	//26 - 28
	offsetX += 17.5f; offsetY = 1.4f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	offsetX += 0.5f; offsetY = 1.4f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

	offsetX += 1.0f; offsetY = 1.4f; index++;
	tempInstance.transformMatrix = DirectX::XMMatrixTranslation(offsetX, offsetY, 0.0f);
	tempInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	tempInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	tempInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	tempInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
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

const Microsoft::WRL::ComPtr<ID3D11Buffer> Brick::getInstanceBuffer() const {
	return instanceBuffer;
}

const UINT Brick::getSizeofInstanceStruct() const {
	return sizeof(instanceStruct);
}

const int Brick::getNumBlockTypeInstances() {
	return instances.size();
}

const int Brick::getNumBlockTypeInstancesToRender() const {
	return instancesToRender.size();
}

const DirectX::XMFLOAT3 Brick::getInstanceVertice(int ID, int verticeNumber) {
	return instances[ID].verticesPos[verticeNumber];
}

void Brick::resetInstances() {
	instancesToRender = std::vector<instanceStruct>();
}

void Brick::addIstance(int instanceID) {
	instanceStruct newInstance;
	newInstance.instanceID = instanceID;
	newInstance.newUVValues[0] = DirectX::XMFLOAT2(0.142857f * 2, 0.0f);
	newInstance.newUVValues[1] = DirectX::XMFLOAT2(0.142857f * 3, 0.0f);
	newInstance.newUVValues[2] = DirectX::XMFLOAT2(0.142857f * 2, 0.33333f);
	newInstance.newUVValues[3] = DirectX::XMFLOAT2(0.142857f * 3, 0.33333f);
	newInstance.transformMatrix = initNumInstances[instanceID].transformMatrix;
	newInstance.verticesPos[0] = initNumInstances[instanceID].verticesPos[0];
	newInstance.verticesPos[1] = initNumInstances[instanceID].verticesPos[1];
	newInstance.verticesPos[2] = initNumInstances[instanceID].verticesPos[2];
	newInstance.verticesPos[3] = initNumInstances[instanceID].verticesPos[3];
	instancesToRender.push_back(newInstance);
}

void Brick::updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) {
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

void Brick::getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const {
	positions[0] = initNumInstances[currInstance].verticesPos[0];
	positions[1] = initNumInstances[currInstance].verticesPos[1];
	positions[2] = initNumInstances[currInstance].verticesPos[2];
	positions[3] = initNumInstances[currInstance].verticesPos[3];
}