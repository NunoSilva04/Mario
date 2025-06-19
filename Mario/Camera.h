#ifndef CAMERA_H_
#define CAMERA_H_

#include "AllHeaderFiles.h"
#include "Mario.h"

class SUPERMARIOBROSTITLE;
class MAINMENU;
class GAME;

class CAMERA {
	friend class SUPERMARIOBROSTITLE;
	friend class MAINMENU;
	friend class GAME;

public:
	CAMERA();
	void initCamera(ID3D11Device* dev);
	void updateCamera(ID3D11DeviceContext* devCon, MARIO Mario);
	void renderCamera(ID3D11DeviceContext* devCon);
	void cleanCamera();

public:
	typedef struct WVPStruct {
		DirectX::XMMATRIX WVPInformationMatrix;
	}WVPStruct;
	WVPStruct  WVPInformationStruct;

	ID3D11Buffer* WVPBuffer;
	DirectX::XMMATRIX WVP, World, CamView, CamProjection;
	DirectX::XMVECTOR CamPosition, CamTarget, CamUp;

public:
	float midCameraPosition;
	float screenLeftSide, screenRightSide, halfScreenWidth;
};

extern CAMERA Camera;

#endif // !CAMERA_H_
