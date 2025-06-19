#ifndef GAMEOBJECTFACTORY_H_
#define GAMEOBJECTFACTORY_H_

#include "GameObjects.h"
#include <iostream>

class GameObjects;

class GameObjectFactory {
public:
	static std::shared_ptr<GameObjects> createGameObject(ObjectTypes objectType, const std::string specificType);
};

#endif // !GAMEOBJECTFACTORY_H_