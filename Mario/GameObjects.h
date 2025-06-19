#ifndef GAMEOBJECTS_H_
#define GAMEOBJECTS_H_

#include "AllHeaderFiles.h"

enum class ObjectTypes {
	Block,
	PowerUps,
	Enemies,
};

class IGrid;

class GameObjects {
public:
	GameObjects(){}
	~GameObjects(){}
	virtual void initObject(ID3D11Device* dev){}
	virtual void updateObject(ID3D11DeviceContext* devCon, std::shared_ptr<IGrid> const IGridsToUse){}
	virtual void renderObject(ID3D11DeviceContext* devCon){}
};

#endif // !GAMEOBJECTS_H_