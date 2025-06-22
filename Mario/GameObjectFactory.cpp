#include "GameObjectFactory.h"
#include "Block.h"

std::shared_ptr<GameObjects> GameObjectFactory::createGameObject(ObjectTypes objectType, const std::string specificType) {
	switch (objectType) {
	case ObjectTypes::Block:
		return Block::createBlockType(specificType);
		break;

	case ObjectTypes::PowerUps:
		break;

	case ObjectTypes::Enemies:
		break;

	default:
		return nullptr;
	}
}