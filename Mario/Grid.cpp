#include "Grid.h"
#include "IGameObjects.h"

IGrid::~IGrid() {

}

Grid::Grid(int numGrids) {
	numGridCells = numGrids;
	numGridCellsToRender = 0;
}

void Grid::createGrid(std::vector<std::shared_ptr<IGameObjects>> const gameObjects) {
	float minGridCell_X = -3.0f, maxGridCell_X = 40.0f;
	float minGridCell_Y = -2.0f, maxGridCell_Y = 10.0f;
	for (int currGridCell = 0; currGridCell < numGridCells; currGridCell++) {
		gridStruct tempGrid;
		tempGrid.gridCell_ID = currGridCell;
		tempGrid.minCellSizeX = minGridCell_X;
		tempGrid.maxCellSizeX = maxGridCell_X;
		tempGrid.minCellSizeY = minGridCell_Y;
		tempGrid.maxCellSizeY = maxGridCell_Y;

		for (int currGameObject = 0; currGameObject < gameObjects.size(); currGameObject++) {
			int numGameSubTypeObjects = gameObjects[currGameObject]->getNumObjectSubType();
			for (int currSubTypeObject = 0; currSubTypeObject < numGameSubTypeObjects; currSubTypeObject++) {
				int numSubTypeInstances = gameObjects[currGameObject]->getObjectSubTypeNumInstances(currSubTypeObject);
				for (int currSubTypeInstance = 0; currSubTypeInstance < numSubTypeInstances; currSubTypeInstance++) {
					DirectX::XMFLOAT3 positions[4];
					gameObjects[currGameObject]->getObjectSubTypePosition(currSubTypeObject, &positions[0], currSubTypeInstance);
					if (minGridCell_X <= positions[0].x && positions[3].x <= maxGridCell_X) {
						gridStruct::objectStruct newObject;
						newObject.objectType = currGameObject;
						newObject.objectSubType = currSubTypeObject;
						newObject.instanceID = currSubTypeInstance;
						newObject.position[0] = positions[0];
						newObject.position[1] = positions[1];
						newObject.position[2] = positions[2];
						newObject.position[3] = positions[3];
						tempGrid.objects.push_back(newObject);
					}
				}
			}
		}

		minGridCell_X = maxGridCell_X;
		maxGridCell_X += 40.0f;
		gridCells.push_back(tempGrid);
	}
}

void Grid::updateRenderableGrids(const float cameraLeftSide, const float cameraRightSide) {
	numGridCellsToRender = 0;
	gridCellsToRender = std::vector<gridStruct>();
	for (int currGrid = 0; currGrid < gridCells.size(); currGrid++) {
		if ((cameraLeftSide <= gridCells[currGrid].minCellSizeX || cameraLeftSide <= gridCells[currGrid].maxCellSizeX) &&
			(gridCells[currGrid].minCellSizeX <= cameraRightSide || gridCells[currGrid].maxCellSizeX <= cameraRightSide)) {
			gridCellsToRender.push_back(gridCells[currGrid]);
			numGridCellsToRender++;
		}
	}
}

int Grid::getNumGridsRendered() const {
	return numGridCellsToRender;
}

int Grid::getCurrGridNumObjects(int currGrid) const{
	return gridCellsToRender[currGrid].objects.size();
}

bool Grid::isCorrectObjectType(int currGrid, int currObject, int ObjectType) const {
	if (gridCellsToRender[currGrid].objects[currObject].objectType == ObjectType) {
		return true;
	}
	else {
		return false;
	}
}

int Grid::getObjectSubType(int currGrid, int currObject) const {
	return gridCellsToRender[currGrid].objects[currObject].objectSubType;
}

int Grid::getObjectSubTypeInstanceID(int currGrid, int currObject) const {
	return gridCellsToRender[currGrid].objects[currObject].instanceID;
}

void Grid::getCurrObjectPosition(int currGrid, int currObject, DirectX::XMFLOAT3 objectPosition[4]) const {
	objectPosition[0] = gridCellsToRender[currGrid].objects[currObject].position[0];
	objectPosition[1] = gridCellsToRender[currGrid].objects[currObject].position[1];
	objectPosition[2] = gridCellsToRender[currGrid].objects[currObject].position[2];
	objectPosition[3] = gridCellsToRender[currGrid].objects[currObject].position[3];
}

int Grid::getObjectType(int currGrid, int currObject) const {
	return gridCellsToRender[currGrid].objects[currObject].objectType;
}

void Grid::removeObject(int currGrid, int currObject) {
	gridCells[currGrid].objects.erase(gridCells[currGrid].objects.begin() + currObject);
	gridCellsToRender[currGrid].objects.erase(gridCellsToRender[currGrid].objects.begin() + currObject);
}