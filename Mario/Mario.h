#ifndef MARIO_H_
#define MARIO_H_

#include "AllHeaderFiles.h"

#define GRAVITY -9.8

class CAMERA;
class IGameObjects;
class IGrid;

class MARIO {
	friend class CAMERA;

public:
	MARIO() {
		marioVertexShader = nullptr;
		marioPixelShader = nullptr;
		marioInputLayout = nullptr;
		marioVertexBuffer = nullptr;
		marioIndexBuffer = nullptr;
		marioShaderResourceView = nullptr;
		marioSamplerState = nullptr;
		marioWorld = DirectX::XMMatrixIdentity();

		marioVertices[0] = { DirectX::XMFLOAT3(-2.0f, -0.6f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
		marioVertices[1] = { DirectX::XMFLOAT3(-1.7f, -0.6f, 0.0f), DirectX::XMFLOAT2(0.08333f, 0.0f) };
		marioVertices[2] = { DirectX::XMFLOAT3(-2.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
		marioVertices[3] = { DirectX::XMFLOAT3(-1.7f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.08333f, 1.0f) };
		
		currMarioInfo.center = DirectX::XMFLOAT3((marioVertices[0].position.x + marioVertices[1].position.x) / 2,
												 marioVertices[2].position.y + std::fabs((marioVertices[2].position.y - marioVertices[0].position.y) / 2),
												 0.0f);
		currMarioInfo.topLeft = marioVertices[0].position;
		currMarioInfo.bottomRight = marioVertices[3].position;
		currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		currMarioInfo.onGround = false;
		currMarioInfo.facingRight = true;
		currMarioInfo.spriteNumber = 1;
		currMarioInfo.collisionTop = false;
		currMarioInfo.collisionRight = false;
		currMarioInfo.collisionBottom = false;
		currMarioInfo.collisionLeft = false;
		currMarioInfo.wallSlide = false;
		currMarioInfo.type = MiniMario;
		currMarioInfo.state = MarioState::Still;
		prevMarioInfo = currMarioInfo;
		initMarioInfo = currMarioInfo;
		totalDisplacement_X = 0.0f;
		totalDisplacement_Y = 0.0f;
		smallStep_X = 0.0f;
		smallStep_Y = 0.0f;
	}
	~MARIO(){}
	void initMario(ID3D11Device* dev);
	void initMarioShaders(ID3D11Device* dev);
	void initMarioVertexBuffer(ID3D11Device* dev);
	void initMarioIndexBuffer(ID3D11Device* dev);
	void initMarioShaderResourceView(ID3D11Device* dev);
	void updateMario(ID3D11DeviceContext* devCon, float frame_time, std::shared_ptr<IGrid> const grid,
		std::vector<std::shared_ptr<IGameObjects>> const IgameObjects);
	void renderMario(ID3D11DeviceContext* devCon);
	void cleanMario();

private:
	ID3D11VertexShader* marioVertexShader;
	ID3D11PixelShader* marioPixelShader;
	ID3D11InputLayout* marioInputLayout;
	ID3D11Buffer* marioVertexBuffer;
	ID3D11Buffer* marioIndexBuffer;
	ID3D11ShaderResourceView* marioShaderResourceView;
	ID3D11SamplerState* marioSamplerState;

	struct marioVertexStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	};
	marioVertexStruct marioVertices[4];

private:
	enum MarioType {
		MiniMario,
		NormalMario,
		FireFlowerMario,
	};

	enum MarioState {
		Still,
		Running,
		Jumping,
		WallSlide,
	};

	struct marioInfoStruct {
		DirectX::XMFLOAT3 center, topLeft, bottomRight;
		DirectX::XMVECTOR Vx, Vy;
		bool onGround;
		bool facingRight;
		int spriteNumber;
		bool collisionTop, collisionRight, collisionBottom, collisionLeft;
		bool wallSlide;
		MarioType type;
		MarioState state;
	};
	DirectX::XMMATRIX marioWorld;
	marioInfoStruct currMarioInfo, prevMarioInfo, initMarioInfo;
	float totalDisplacement_X, totalDisplacement_Y, smallStep_X, smallStep_Y;

	//Movement and collisions
	void resetCollisions();
	bool getInput();
	void moveOnXAxis(float frame_time);
	void moveOnYAxis(float frame_time);
	void handleCollision(ID3D11DeviceContext* devCon, std::shared_ptr<IGrid> const grid,
		std::vector<std::shared_ptr<IGameObjects>> const IGameObjects);
	bool checkCollision(DirectX::XMFLOAT3* objectPosition);
	void hitLeftSideScreen();
	void solveTopFaceCollision(DirectX::XMFLOAT3 objectPosition[4]);
	void solveRightFaceCollision(DirectX::XMFLOAT3 objectPosition[4]);
	void solveBottomFaceCollision(DirectX::XMFLOAT3 objectPosition[4]);
	void solveLeftFaceCollision(DirectX::XMFLOAT3 objectPosition[4]);
	float timeOfCollision(float interpolatedAxis, float currPoint, float prevPoint);
	float LERP(float currPoint, float prevPoint, float timeOfCollision);
	void applyWallSlide();

	//State
	void updateMarioState();
	
	//Animation
	void animateMario(ID3D11DeviceContext* devCon);
	void animateMovingMario(ID3D11DeviceContext *devCon);
	void animateStillMario(ID3D11DeviceContext* devCon);
	void animateJumpingMario(ID3D11DeviceContext* devCon);
	void animateWallSlideMario(ID3D11DeviceContext* devCon);
};

#endif // !MARIO_H_