#include <utility>

//
// Created by Eben on 05/06/2019.
//

#include "GameScene.hpp"
#include "../Screen/Screen.hpp"

Irrlicht::GameScene::GameScene(Screen &window, std::string name, unsigned id) :
    _window(window),
    sceneName(name),
    id(id),
    _eventReceiver(window.getEventReceiver())
{
    this->_window.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 100, 0), irr::core::vector3df(20, 0, 0));
}

bool Irrlicht::GameScene::isKeyPressed(irr::EKEY_CODE key) //a changer
{
    return (this->_eventReceiver.isKeyPressed(key));
}

unsigned int Irrlicht::GameScene::registerEntity(const std::string &name)
{
    _entities_id++;
    this->_entities.emplace_back(name, _entities_id, this->_window.getSmgr(), this->_window.getDriver());

    return(_entities_id);
}

void Irrlicht::GameScene::deleteEntity(unsigned id) {
    for (auto it = this->_entities.begin(); it < this->_entities.end(); it++)//delete a special cube here
        if (it->id == id)
            this->_entities.erase(it);
}

void Irrlicht::GameScene::setAnimation(unsigned entity_id, Animations anim) {
    for (auto &ent : this->_entities)
        if (ent.id == entity_id)
            ent.anim = anim;
}

void Irrlicht::GameScene::setPosition(unsigned entity, float x, float y) {
    for (auto &ent : this->_entities)
        if (ent.id == entity) {
            ent.pos = {x, y};
            ent.setPos(ent.pos.x, ent.pos.y);
        }
}

bool Irrlicht::GameScene::areColliding(unsigned entity1, unsigned entity2) {
        std::vector<IrrEntity *> vec;

        for (auto &ent : this->_entities)
            if (ent.id == entity1 || ent.id == entity2)
                vec.push_back(&ent);

        IrrEntity &e1 = *vec.at(0);
        IrrEntity &e2 = *vec.at(1);

        return !(
                e1.pos.x + e1._size.x < e2.pos.x ||
                e2.pos.x + e2._size.x < e1.pos.x ||
                e1.pos.y + e1._size.y < e2.pos.y ||
                e2.pos.y + e2._size.y < e1.pos.y
        );
}

//TODO ZARGITH add to event receiver http://irrlicht.sourceforge.net/docu/example019.html

bool Irrlicht::GameScene::isJoystickButtonPressed(unsigned id, unsigned button)
{
    return (false); //TODO Joystick::isButtonPressed(id, button);
}

float Irrlicht::GameScene::getJoystickAxisPosition(unsigned id, unsigned axis)
{
    return (false); //TODO sf::Joystick::getAxisPosition(id, static_cast<sf::Joystick::Axis>(axis));
}

void Irrlicht::GameScene::update() {
}
