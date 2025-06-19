#ifndef IGRID_H_
#define IGRID_H_

#include "AllHeaderFiles.h"

class IGrid {
public:
	virtual ~IGrid() = 0;
	virtual int getNumGridsRendered() const = 0;
	virtual int getCurrGridNumObjects(int currGrid) const = 0;
	virtual bool isCorrectObjectType(int currGrid, int currObject, int ObjectType) const = 0;
	virtual int getObjectSubType(int currGrid, int currObject) const = 0;
	virtual int getObjectSubTypeInstanceID(int currGrid, int currObject) const = 0;
	virtual void getCurrObjectPosition(int currGrid, int currObject, DirectX::XMFLOAT3 objectPosition[4]) const = 0;
	virtual int getObjectType(int currGrid, int currObject) const = 0;
	virtual void removeObject(int currGrid, int currObject) = 0;
};

#endif // !IGRID_H_