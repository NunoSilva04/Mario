#include "Mario.h"
#include "InputManager.h"
#include "Camera.h"

//Test
#include "IGrid.h"
#include "IGameObjects.h"

void MARIO::resetCollisions() {
	currMarioInfo.collisionTop = false;
	currMarioInfo.collisionRight = false;
	currMarioInfo.collisionBottom = false;
	currMarioInfo.collisionLeft = false;
	currMarioInfo.onGround = false;
	currMarioInfo.wallSlide = false;
}

bool MARIO::getInput() {
	bool pressedAKey = false;
	if (inputManager.keyPressed['D'] == true) {
		float Vx = 0.05f;
		currMarioInfo.Vx = DirectX::XMVectorSet(DirectX::XMVectorGetX(prevMarioInfo.Vx) + Vx, 0.0f, 0.0f, 0.0f);
		currMarioInfo.facingRight = true;
		if (prevMarioInfo.facingRight == false) {
			currMarioInfo.spriteNumber = 1;
		}
		if (DirectX::XMVectorGetX(currMarioInfo.Vx) >= 5.0f) {
			currMarioInfo.Vx = DirectX::XMVectorSet(5.0f, 0.0f, 0.0f, 0.0f);
		}
		pressedAKey = true;
	}
	if (inputManager.keyPressed['A'] == true) {
		float Vx = -0.05f;
		currMarioInfo.Vx = DirectX::XMVectorSet(DirectX::XMVectorGetX(prevMarioInfo.Vx) + Vx, 0.0f, 0.0f, 0.0f);
		currMarioInfo.facingRight = false;
		if (prevMarioInfo.facingRight == true) {
			currMarioInfo.spriteNumber = 7;
		}
		if (DirectX::XMVectorGetX(currMarioInfo.Vx) <= -5.0f) {
			currMarioInfo.Vx = DirectX::XMVectorSet(-5.0f, 0.0f, 0.0f, 0.0f);
		}
		pressedAKey = true;
	}
	//if (inputManager.keyPressed['A'] == true && inputManager.keyPressed['D'] == true) {
	//	currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//	pressedAKey = true;
	//}
	if (inputManager.keyPressed['W'] == true && prevMarioInfo.onGround == true) {
		currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 5.5f, 0.0f, 0.0f);
		prevMarioInfo.Vy = currMarioInfo.Vy;
		currMarioInfo.onGround = false;
		pressedAKey = true;
	}
	if (inputManager.keyPressed['S'] == true && currMarioInfo.onGround == true) {

	}

	return pressedAKey;
}

void MARIO::moveOnXAxis(float frame_time) {
	smallStep_X = DirectX::XMVectorGetX(currMarioInfo.Vx) * frame_time;
	currMarioInfo.center.x = prevMarioInfo.center.x + smallStep_X;
	currMarioInfo.bottomRight.x = prevMarioInfo.bottomRight.x + smallStep_X;
	currMarioInfo.topLeft.x = prevMarioInfo.topLeft.x + smallStep_X;
}

void MARIO::moveOnYAxis(float frame_time) {
	float currMarioInfoVy = DirectX::XMVectorGetY(prevMarioInfo.Vy) + GRAVITY * frame_time;
	currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, currMarioInfoVy, 0.0f, 0.0f);
	smallStep_Y = DirectX::XMVectorGetY(currMarioInfo.Vy) * frame_time + (0.5f * GRAVITY * pow(frame_time, 2));
	currMarioInfo.center.y = prevMarioInfo.center.y + smallStep_Y;
	currMarioInfo.topLeft.y = prevMarioInfo.topLeft.y + smallStep_Y;
	currMarioInfo.bottomRight.y = prevMarioInfo.bottomRight.y + smallStep_Y;
}

void MARIO::handleCollision(ID3D11DeviceContext *devCon, std::shared_ptr<IGrid> const grid, 
	std::vector<std::shared_ptr<IGameObjects>> const IGameObjects) {
	if (currMarioInfo.topLeft.x < Camera.screenLeftSide) {
		currMarioInfo.collisionLeft = true;
		hitLeftSideScreen();
	}

	int numGridsToRender = grid->getNumGridsRendered();
	for (int currGrid = 0; currGrid < numGridsToRender; currGrid++) {
		int numObjcectsInGrid = grid->getCurrGridNumObjects(currGrid);
		for (int currObject = 0; currObject < numObjcectsInGrid; currObject++) {
			DirectX::XMFLOAT3 objectPosition[4];
			grid->getCurrObjectPosition(currGrid, currObject, objectPosition);
			if (checkCollision(objectPosition)) {
				int objectType = grid->getObjectType(currGrid, currObject);
				int objectSubType = grid->getObjectSubType(currGrid, currObject);
				switch (objectType){
				//Blocks
				case 0:
					//FloorTile
					switch (objectSubType){
					case 0:
						if (currMarioInfo.collisionBottom == true) {
							solveBottomFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							currMarioInfo.onGround = true;
						}
						else if (currMarioInfo.collisionRight == true && currMarioInfo.onGround == false) {
							solveRightFaceCollision(objectPosition);
							currMarioInfo.wallSlide = true;
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, -0.75f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionLeft == true && currMarioInfo.onGround == false) {
							solveLeftFaceCollision(objectPosition);
							currMarioInfo.wallSlide = true;
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, -0.75f, 0.0f, 0.0f);
						}
						break;

					//DarkFloorTile
					case 1:
						break;

					//Brick
					case 2:
						if (currMarioInfo.collisionRight == true) {
							solveRightFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionLeft == true) {
							solveLeftFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionTop == true) {
							solveTopFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							if (currMarioInfo.type == MarioType::NormalMario) {
								grid->removeObject(currGrid, currObject);
								currObject -= 1;
								numObjcectsInGrid -= 1;
							}
						}
						else if (currMarioInfo.collisionBottom == true) {
							solveBottomFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							currMarioInfo.onGround = true;
						}
						break;
					
					//DarkBrick
					case 3:
						break;

					//MysteryBlock and empty MysteryBlock
					case 4:
						if (currMarioInfo.collisionRight == true) {
							solveRightFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionLeft == true) {
							solveLeftFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionTop == true) {
							solveTopFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionBottom == true) {
							solveBottomFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							currMarioInfo.onGround = true;
						}
						break;
					
					//UnbreakableBrick
					case 5:
						if (currMarioInfo.collisionRight == true) {
							solveRightFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionLeft == true) {
							solveLeftFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionTop == true) {
							solveTopFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionBottom == true) {
							solveBottomFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							currMarioInfo.onGround = true;
						}
						break;

					//Pipe
					case 6:
						if (currMarioInfo.collisionRight == true) {
							solveRightFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionLeft == true) {
							solveLeftFaceCollision(objectPosition);
							currMarioInfo.Vx = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionTop == true) {
							solveTopFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						}
						else if (currMarioInfo.collisionBottom == true) {
							solveBottomFaceCollision(objectPosition);
							currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
							currMarioInfo.onGround = true;
						}
						break;

					default:
						break;
					}
					break;

				default:
					break;
				}
			}
		}
	}
	/*
	
	Wall Slide functionalities to implement on collisio. The rest is already done
	currMarioInfo.wallSlide = true;
	currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, -0.75f, 0.0f, 0.0f);
	
	*/
}

bool MARIO::checkCollision(DirectX::XMFLOAT3* objectPosition) {
	if (currMarioInfo.bottomRight.x > objectPosition[0].x && currMarioInfo.topLeft.x < objectPosition[3].x &&
		currMarioInfo.bottomRight.y < objectPosition[0].y && currMarioInfo.topLeft.y > objectPosition[3].y) {
		std::vector<float> absSides;
		absSides.push_back(std::fabs(currMarioInfo.bottomRight.x - objectPosition[0].x));	//Right
		absSides.push_back(std::fabs(currMarioInfo.topLeft.x - objectPosition[3].x));		//Left
		absSides.push_back(std::fabs(currMarioInfo.topLeft.y - objectPosition[3].y));		//Top
		absSides.push_back(std::fabs(currMarioInfo.bottomRight.y - objectPosition[0].y));	//Bottom
		float smallestSide = absSides[0];

		for (int i = 0; i < absSides.size(); i++) {
			if (smallestSide > absSides[i]) {
				smallestSide = absSides[i];
			}
		}

		if (smallestSide == absSides[0]) {
			currMarioInfo.collisionRight = true;
		}
		else if (smallestSide == absSides[1]) {
			currMarioInfo.collisionLeft = true;
		}
		else if (smallestSide == absSides[2]) {
			currMarioInfo.collisionTop = true;
		}
		else if (smallestSide == absSides[3]) {
			currMarioInfo.collisionBottom = true;
		}

		return true;
	}
	return false;
}

void MARIO::hitLeftSideScreen() {
	//X position
	float timeOfColX = timeOfCollision(Camera.screenLeftSide, currMarioInfo.topLeft.x, prevMarioInfo.topLeft.x);
	float newTopLeftPositionX = LERP(currMarioInfo.topLeft.x, prevMarioInfo.topLeft.x, timeOfColX);
	float diffInPositionX = newTopLeftPositionX - currMarioInfo.topLeft.x;
	currMarioInfo.topLeft.x = newTopLeftPositionX;
	currMarioInfo.center.x += diffInPositionX;
	currMarioInfo.bottomRight.x += diffInPositionX;
	//Y position
	if (timeOfColX > 0.0f) {
		float newTopLeftPositionY = LERP(currMarioInfo.topLeft.y, prevMarioInfo.topLeft.y, timeOfColX);
		float diffInPositionY = newTopLeftPositionY - currMarioInfo.topLeft.y;
		currMarioInfo.topLeft.y = newTopLeftPositionY;
		currMarioInfo.center.y += diffInPositionY;
		currMarioInfo.bottomRight.y += diffInPositionY;
	}
}

void MARIO::solveTopFaceCollision(DirectX::XMFLOAT3 objectPosition[4]) {
	//Y coordinate
	float timeOfColl = timeOfCollision(objectPosition[3].y, currMarioInfo.topLeft.y, prevMarioInfo.topLeft.y);
	float newBottomPositionY = LERP(currMarioInfo.topLeft.y, prevMarioInfo.topLeft.y, timeOfColl);
	float diffInPositionY = newBottomPositionY - currMarioInfo.topLeft.y;
	currMarioInfo.topLeft.y = newBottomPositionY;
	currMarioInfo.center.y += diffInPositionY;
	currMarioInfo.bottomRight.y += diffInPositionY;
	//X coordinate
	if (timeOfColl > 0.0f) {
		float newBottomPositionX = LERP(currMarioInfo.topLeft.x, prevMarioInfo.topLeft.x, timeOfColl);
		float diffInPositionX = newBottomPositionX - currMarioInfo.topLeft.x;
		currMarioInfo.topLeft.x = newBottomPositionX;
		currMarioInfo.center.x += diffInPositionX;
		currMarioInfo.bottomRight.x += diffInPositionX;
	}
}

void MARIO::solveRightFaceCollision(DirectX::XMFLOAT3 objectPosition[4]){
	//X coordinate
	float timeOfColl = timeOfCollision(objectPosition[0].x, currMarioInfo.bottomRight.x, prevMarioInfo.bottomRight.x);
	float newBottomPositionX = LERP(currMarioInfo.bottomRight.x, prevMarioInfo.bottomRight.x, timeOfColl);
	float diffInPositionX = newBottomPositionX - currMarioInfo.bottomRight.x;
	currMarioInfo.bottomRight.x = newBottomPositionX;
	currMarioInfo.center.x += diffInPositionX;
	currMarioInfo.topLeft.x += diffInPositionX;

	//Y coordinate
	if (timeOfColl > 0.0f) {
		float newBottomPositionY = LERP(currMarioInfo.bottomRight.y, prevMarioInfo.bottomRight.y, timeOfColl);
		float diffInPositionY = newBottomPositionY - currMarioInfo.bottomRight.y;
		currMarioInfo.bottomRight.y = newBottomPositionY;
		currMarioInfo.center.y += diffInPositionY;
		currMarioInfo.topLeft.y += diffInPositionY;
	}
}

void MARIO::solveBottomFaceCollision(DirectX::XMFLOAT3 objectPosition[4]) {
	//Y coordinate
	float timeOfColl = timeOfCollision(objectPosition[0].y, currMarioInfo.bottomRight.y, prevMarioInfo.bottomRight.y);
	float newBottomPositionY = LERP(currMarioInfo.bottomRight.y, prevMarioInfo.bottomRight.y, timeOfColl);
	float diffInPositionY = newBottomPositionY - currMarioInfo.bottomRight.y;
	currMarioInfo.bottomRight.y = newBottomPositionY;
	currMarioInfo.center.y += diffInPositionY;
	currMarioInfo.topLeft.y += diffInPositionY;
	//X coordinate
	if (timeOfColl > 0.0f) {
		float newBottomPositionX = LERP(currMarioInfo.bottomRight.x, prevMarioInfo.bottomRight.x, timeOfColl);
		float diffInPositionX = newBottomPositionX - currMarioInfo.bottomRight.x;
		currMarioInfo.bottomRight.x = newBottomPositionX;
		currMarioInfo.center.x += diffInPositionX;
		currMarioInfo.topLeft.x += diffInPositionX;
	}
}

void MARIO::solveLeftFaceCollision(DirectX::XMFLOAT3 objectPosition[4]) {
	//X coordinate
	float timeOfColl = timeOfCollision(objectPosition[3].x, currMarioInfo.topLeft.x, prevMarioInfo.topLeft.x);
	float newTopLeftPositionX = LERP(currMarioInfo.topLeft.x, prevMarioInfo.topLeft.x, timeOfColl);
	float diffInPositionX = newTopLeftPositionX - currMarioInfo.topLeft.x;
	currMarioInfo.topLeft.x = newTopLeftPositionX;
	currMarioInfo.center.x += diffInPositionX;
	currMarioInfo.bottomRight.x += diffInPositionX;

	//Y coordinate
	if (timeOfColl > 0.0f) {
		float newTopLeftPositionY = LERP(currMarioInfo.topLeft.y, prevMarioInfo.topLeft.y, timeOfColl);
		float diffInPositionY = newTopLeftPositionY - currMarioInfo.topLeft.y;
		currMarioInfo.topLeft.y = newTopLeftPositionY;
		currMarioInfo.center.y += diffInPositionY;
		currMarioInfo.bottomRight.y += diffInPositionY;
	}
}

float MARIO::timeOfCollision(float interpolatedAxis, float currPoint, float prevPoint) {
	return ((interpolatedAxis - prevPoint) / (currPoint - prevPoint));
}

float MARIO::LERP(float currPoint, float prevPoint, float timeOfCollision) {
	return ((currPoint * timeOfCollision) + (prevPoint * (1 - timeOfCollision)));
}

void MARIO::applyWallSlide() {
	if (prevMarioInfo.wallSlide == true && inputManager.keyPressed['A'] == true && prevMarioInfo.collisionRight == true) {
		currMarioInfo.Vx = DirectX::XMVectorSet(-5.0f, 0.0f, 0.0f, 0.0f);
		currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 5.0f, 0.0f, 0.0f);
	}
	if (prevMarioInfo.wallSlide == true && inputManager.keyPressed['D'] == true && prevMarioInfo.collisionLeft == true) {
		currMarioInfo.Vx = DirectX::XMVectorSet(5.0f, 0.0f, 0.0f, 0.0f);
		currMarioInfo.Vy = DirectX::XMVectorSet(0.0f, 5.0f, 0.0f, 0.0f);
	}
}

void MARIO::updateMarioState() {
	if (currMarioInfo.wallSlide == true) {
		currMarioInfo.state = MarioState::WallSlide;
	}else if (currMarioInfo.onGround == false) {
		currMarioInfo.state = MarioState::Jumping;
	}
	else if (std::fabs(DirectX::XMVectorGetX(currMarioInfo.Vx)) > 0.0f) {
		currMarioInfo.state = MarioState::Running;
	}
	else {
		currMarioInfo.state = MarioState::Still;
	}
}

void MARIO::animateMario(ID3D11DeviceContext* devCon) {
	switch (currMarioInfo.state) {
	case MarioState::Still:
		animateStillMario(devCon);
		break;
	case MarioState::Running:
		animateMovingMario(devCon);
		break;
	case MarioState::Jumping:
		animateJumpingMario(devCon);
		break;
	case MarioState::WallSlide:
		animateWallSlideMario(devCon);
		break;
	default:
		animateStillMario(devCon);
		break;
	}
}

void MARIO::animateMovingMario(ID3D11DeviceContext* devCon) {
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	if (currMarioInfo.facingRight == true) {
		hr = devCon->Map(marioVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResource);
		if (SUCCEEDED(hr)) {
			currMarioInfo.spriteNumber++;
			if (currMarioInfo.spriteNumber > 4) {
				currMarioInfo.spriteNumber = 2;
			}
			float spriteSize = 0.0833f;
			float rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize;
			float leftTexCoord = currMarioInfo.spriteNumber * spriteSize;
			marioVertices[0].texCoord = DirectX::XMFLOAT2(rightTexCoord, 0.0f);
			marioVertices[1].texCoord = DirectX::XMFLOAT2(leftTexCoord, 0.0f);
			marioVertices[2].texCoord = DirectX::XMFLOAT2(rightTexCoord, 1.0f);
			marioVertices[3].texCoord = DirectX::XMFLOAT2(leftTexCoord, 1.0f);

			memcpy(mappedSubResource.pData, &marioVertices, sizeof(marioVertices[0]) * 4);
			devCon->Unmap(marioVertexBuffer, 0);
		}
		else {
			OutputDebugString(L"Couldn't map mario subresource\n");
			PostQuitMessage(0);
		}
	}
	else {
		hr = devCon->Map(marioVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResource);
		if (SUCCEEDED(hr)) {
			currMarioInfo.spriteNumber++;
			if (currMarioInfo.spriteNumber > 10) {
				currMarioInfo.spriteNumber = 8;
			}
			float spriteSize = 0.0833f;
			float rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize;
			float leftTexCoord = currMarioInfo.spriteNumber * spriteSize;
			marioVertices[0].texCoord = DirectX::XMFLOAT2(rightTexCoord, 0.0f);
			marioVertices[1].texCoord = DirectX::XMFLOAT2(leftTexCoord, 0.0f);
			marioVertices[2].texCoord = DirectX::XMFLOAT2(rightTexCoord, 1.0f);
			marioVertices[3].texCoord = DirectX::XMFLOAT2(leftTexCoord, 1.0f);

			memcpy(mappedSubResource.pData, &marioVertices, sizeof(marioVertices[0]) * 4);
			devCon->Unmap(marioVertexBuffer, 0);
		}
		else {
			OutputDebugString(L"Couldn't map mario vertex buffer\n");
			PostQuitMessage(0);
		}
	}
}

void MARIO::animateStillMario(ID3D11DeviceContext* devCon) {
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	hr = devCon->Map(marioVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResource);
	if (SUCCEEDED(hr)) {
		if (currMarioInfo.facingRight == true) {
			currMarioInfo.spriteNumber = 1;
		}
		else {
			currMarioInfo.spriteNumber = 7;
		}
		float rightTexCoord;
		float spriteSize = 0.0833f;
		if (currMarioInfo.facingRight == true) {
			rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize;
		}
		else {
			rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize + 0.001f;
		}
		float leftTexCoord = currMarioInfo.spriteNumber * spriteSize;
		marioVertices[0].texCoord = DirectX::XMFLOAT2(rightTexCoord, 0.0f);
		marioVertices[1].texCoord = DirectX::XMFLOAT2(leftTexCoord, 0.0f);
		marioVertices[2].texCoord = DirectX::XMFLOAT2(rightTexCoord, 1.0f);
		marioVertices[3].texCoord = DirectX::XMFLOAT2(leftTexCoord, 1.0f);

		memcpy(mappedSubResource.pData, &marioVertices, sizeof(marioVertices[0]) * 4);
		devCon->Unmap(marioVertexBuffer, 0);
	}
	else {
		OutputDebugString(L"Couldn't map mario vertex buffer\n");
		PostQuitMessage(0);
	}
}

void MARIO::animateJumpingMario(ID3D11DeviceContext* devCon) {
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	hr = devCon->Map(marioVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResource);
	if (SUCCEEDED(hr)) {
		if (currMarioInfo.facingRight == true) {
			currMarioInfo.spriteNumber = 6;
		}
		else {
			currMarioInfo.spriteNumber = 12;
		}
		float spriteSize = 0.0833f;
		float rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize;
		float leftTexCoord = currMarioInfo.spriteNumber * spriteSize;
		marioVertices[0].texCoord = DirectX::XMFLOAT2(rightTexCoord, 0.0f);
		marioVertices[1].texCoord = DirectX::XMFLOAT2(leftTexCoord, 0.0f);
		marioVertices[2].texCoord = DirectX::XMFLOAT2(rightTexCoord, 1.0f);
		marioVertices[3].texCoord = DirectX::XMFLOAT2(leftTexCoord, 1.0f);

		memcpy(mappedSubResource.pData, &marioVertices, sizeof(marioVertices[0]) * 4);
		devCon->Unmap(marioVertexBuffer, 0);
	}
	else {
		OutputDebugString(L"Couldn't map mario vertex buffer\n");
		PostQuitMessage(0);
	}
}

void MARIO::animateWallSlideMario(ID3D11DeviceContext* devCon) {
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	hr = devCon->Map(marioVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResource);
	if (SUCCEEDED(hr)) {
		if (currMarioInfo.collisionRight == true) {
			currMarioInfo.spriteNumber = 11;
		}
		else {
			currMarioInfo.spriteNumber = 5;
		}

		float spriteSize = 0.0833f;
		float rightTexCoord = (currMarioInfo.spriteNumber * spriteSize) - spriteSize;
		float leftTexCoord = currMarioInfo.spriteNumber * 0.0817f;
		marioVertices[0].texCoord = DirectX::XMFLOAT2(rightTexCoord, 0.0f);
		marioVertices[1].texCoord = DirectX::XMFLOAT2(leftTexCoord, 0.0f);
		marioVertices[2].texCoord = DirectX::XMFLOAT2(rightTexCoord, 1.0f);
		marioVertices[3].texCoord = DirectX::XMFLOAT2(leftTexCoord, 1.0f);

		memcpy(mappedSubResource.pData, &marioVertices[0], sizeof(marioVertices[0]) * 4);
		devCon->Unmap(marioVertexBuffer, 0);
	}
	else {
		OutputDebugString(L"Couldn't map mario vertex buffer wall slide\n");
		PostQuitMessage(0);
	}
}