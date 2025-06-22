#include "Camera.h"

CAMERA Camera;

CAMERA::CAMERA() {
	WVPBuffer = nullptr;
	CamPosition = DirectX::XMVectorSet(0.0f, 0.0f, -3.f, 0.0f);
	CamTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	CamUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	World = DirectX::XMMatrixIdentity();
	midCameraPosition = 0.7f;
	halfScreenWidth = 3.682f;
	screenLeftSide = DirectX::XMVectorGetX(CamPosition) - halfScreenWidth;
	screenRightSide = DirectX::XMVectorGetX(CamPosition) + halfScreenWidth;
}

void CAMERA::initCamera(ID3D11Device* dev) {
	HRESULT hr;

	D3D11_BUFFER_DESC WVPBufferDesc;
	ZeroMemory(&WVPBufferDesc, sizeof(D3D11_BUFFER_DESC));

	WVPBufferDesc.ByteWidth = sizeof(WVPStruct);
	WVPBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	WVPBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	WVPBufferDesc.CPUAccessFlags = 0;
	
	hr = dev->CreateBuffer(&WVPBufferDesc, nullptr, &WVPBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create WVPBuffer", L"Error", MB_OK);
		exit(-1);
	}

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	//Set Matrices
	CamView = DirectX::XMMatrixLookAtLH(CamPosition, CamTarget, CamUp);
	CamProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), (float)width / height, 0.1f, 100.0f);
}

void CAMERA::updateCamera(ID3D11DeviceContext* devCon) {
	CamPosition = DirectX::XMVectorSet(0.0f, 0.0f, -3.f, 0.0f);
	CamTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	CamView = DirectX::XMMatrixLookAtLH(CamPosition, CamTarget, CamUp);
}

void CAMERA::updateCamera(ID3D11DeviceContext* devCon, MARIO Mario) {
	if (Mario.currMarioInfo.bottomRight.x >= midCameraPosition) {
		midCameraPosition = Mario.currMarioInfo.bottomRight.x;
	}
										
	CamPosition = DirectX::XMVectorSet(midCameraPosition, 0.1f, -5.0f, 0.0f);
	CamTarget = DirectX::XMVectorSet(midCameraPosition, 0.1f, 0.0f, 0.0f);
	CamView = DirectX::XMMatrixLookAtLH(CamPosition, CamTarget, CamUp);
	screenLeftSide = DirectX::XMVectorGetX(CamPosition) - halfScreenWidth;
	screenRightSide = DirectX::XMVectorGetX(CamPosition) + halfScreenWidth;
	midCameraPosition = screenLeftSide + halfScreenWidth;
}

void CAMERA::renderCamera(ID3D11DeviceContext* devCon) {
	WVP = World * CamView * CamProjection;
	WVPInformationStruct.WVPInformationMatrix = DirectX::XMMatrixTranspose(WVP);
	devCon->UpdateSubresource(WVPBuffer, 0, nullptr, &WVPInformationStruct, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &WVPBuffer);
}

void CAMERA::cleanCamera() {
	WVPBuffer->Release();
}