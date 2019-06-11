#include <utility>

//
// Created by Eben on 05/06/2019.
//

#include "GameScene.hpp"
#include "../screen/Screen.hpp"
#include "../Exceptions.hpp"

Irrlicht::GameScene::GameScene(Screen &window, const std::string &name, unsigned id) :
	_window(window),
	sceneName(name),
	id(id),
	_entitiesId(0),
	_eventReceiver(window.getEventReceiver())
{
	this->_window.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(320, 500, -320), irr::core::vector3df(320, 0, -319));
}

bool Irrlicht::GameScene::isKeyPressed(irr::EKEY_CODE key)
{
	return (this->_eventReceiver.isKeyPressed(key));
}

unsigned int Irrlicht::GameScene::registerEntity(const std::string &name)
{
	this->_entities.emplace_back(
		new IrrEntity{
			name,
			this->_entitiesId,
			this->_window.getSmgr(),
			this->_window.getDriver()
		}
	);
	return(this->_entitiesId++);
}

void Irrlicht::GameScene::deleteEntity(unsigned id) {
	for (auto it = this->_entities.begin(); it < this->_entities.end(); it++)
		while (it < this->_entities.end() && (*it)->id == id)
			this->_entities.erase(it);
}

void Irrlicht::GameScene::setAnimation(unsigned entity_id, Animations anim) {
	for (auto &ent : this->_entities)
		if (ent->id == entity_id)
			ent->anim = anim;
}

void Irrlicht::GameScene::setPosition(unsigned entity, float x, float z) {
	for (auto &ent : this->_entities)
		if (ent->id == entity)
			ent->setPos(x, -z);
}

void Irrlicht::GameScene::setScale(unsigned entity, float x, float z) {
	for (auto &ent : this->_entities)
		if (ent->id == entity)
			ent->setPos(x, z);
}

void Irrlicht::GameScene::setSize(unsigned entity, float x, float z)
{
	for (auto &ent : this->_entities)
		if (ent->id == entity)
			ent->setSize(x, z);
}

ECS::Vector2<float> Irrlicht::GameScene::getSize(unsigned entity) {
	for (auto &ent : this->_entities)
		if (ent->id == entity)
			return ent->getSize();
	throw NoSuchEntityException("Cannot find entity with id " + std::to_string(entity));
}

bool Irrlicht::GameScene::areColliding(unsigned entity1, unsigned entity2)
{
	return false;
}

bool Irrlicht::GameScene::isJoystickButtonPressed(unsigned button)
{
//	this->_eventReceiver.displayAxes();
	return (this->_eventReceiver.isJoystickKeyPressed(button));
}

float Irrlicht::GameScene::getJoystickAxisPosition(unsigned axis)
{
	return (this->_eventReceiver.getJoystickAxisPosition(axis));
}

bool Irrlicht::GameScene::isJoystickAxisPressed(ControllerAxisGS button)
{
	float value = 0;

	switch (button) {
	case LEFT_JOYSTICK_UP:
	case LEFT_JOYSTICK_DOWN:
		value = this->getJoystickAxisPosition(1);
		break;
	case LEFT_JOYSTICK_LEFT:
	case LEFT_JOYSTICK_RIGHT:
		value = this->getJoystickAxisPosition(0);
		break;
	case RIGHT_JOYSTICK_UP:
	case RIGHT_JOYSTICK_DOWN:
		value = this->getJoystickAxisPosition(4);
		break;
	case RIGHT_JOYSTICK_LEFT:
	case RIGHT_JOYSTICK_RIGHT:
		value = this->getJoystickAxisPosition(3);
		break;
	case RT:
		value = this->getJoystickAxisPosition(2);
		break;
	case LT:
		value = this->getJoystickAxisPosition(5);
		break;

	default :
		return (false);
	}
	
	if (value < 0)
		value *= -1;
	if (value > 16384)
		return (true);
	return (false);
}