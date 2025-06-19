#ifndef IGAMEOBJECTS_H_
#define IGAMEOBJECTS_H_

#include "AllHeaderFiles.h"

class IGameObjects {
public:
	virtual ~IGameObjects() = 0;
	//Parent
	virtual int getNumObjectSubType() const = 0;
	virtual int getObjectSubTypeNumInstances(int currObjectSubType) const = 0;
	virtual void getObjectSubTypePosition(int currObjectSubType, DirectX::XMFLOAT3* positions, int currInstance) const = 0;
};

#endif // !IGAMEOBJECTS_H_
