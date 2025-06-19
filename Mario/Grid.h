#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include "AllHeaderFiles.h"
#include "IGrid.h"

class IGameObjects;

class Grid : public IGrid{
public:
	Grid(int numGrids);
	void createGrid(std::vector<std::shared_ptr<IGameObjects>> const gameObject);
	void updateRenderableGrids(const float cameraLeftSide, const float cameraRightSide);

private:
	struct gridStruct {
		int gridCell_ID;
		float minCellSizeX;
		float maxCellSizeX;
		float minCellSizeY;
		float maxCellSizeY;
		struct objectStruct {
			int objectType;
			int objectSubType;
			int instanceID;
			DirectX::XMFLOAT3 position[4];
		};
		std::vector <objectStruct> objects;
	};
	std::vector<gridStruct> gridCells, gridCellsToRender;
	int numGridCells, numGridCellsToRender;

	int getNumGridsRendered() const override;
	int getCurrGridNumObjects(int currGrid) const override;
	bool isCorrectObjectType(int currGrid, int currObject, int ObjectType) const;
	int getObjectSubType(int currGrid, int currObject) const;
	int getObjectSubTypeInstanceID(int currGrid, int currObject) const;
	void getCurrObjectPosition(int currGrid, int currObject, DirectX::XMFLOAT3 objectPosition[4]) const;
	int getObjectType(int currGrid, int currObject) const;
	void removeObject(int currGrid, int currObject);
};

#endif // !GRID_H_
