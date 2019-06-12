/*
** EPITECH PROJECT, 2018
** IndieStudio
** File description:
** Controller.cpp
*/

#include "Controller.hpp"
#include "../irrlicht/game-scene/GameScene.hpp"

Input::Controller::Controller(Irrlicht::GameScene &scene, std::vector<ControllerButtons> &&keys, unsigned id, unsigned threshold) :
	_scene(scene),
	_keys(keys),
	_id(id),
	_threshold(threshold)
{
    if ((keys.size() != 3 && keys.size() != 6) || (keys.size() == 3 && keys[0] != LEFT_JOYSTICK && keys[0] != RIGHT_JOYSTICK))
        throw ControllerException("Invalid key vector given (size is invalid)");
}

std::vector<Input::Action> Input::Controller::getActions() { //WIP
	std::vector<Action> actions;
	int start = 1;
	float x;
	float y;

	if (this->_keys[0] == LEFT_JOYSTICK || this->_keys[0] == RIGHT_JOYSTICK) {
		x = this->_scene.getJoystickAxisPosition(this->_id, irr::SEvent::SJoystickEvent::AXIS_X + (this->_keys[0] == RIGHT_JOYSTICK) * 3);
		y = this->_scene.getJoystickAxisPosition(this->_id, irr::SEvent::SJoystickEvent::AXIS_Y + (this->_keys[0] == RIGHT_JOYSTICK) * 3);

		if (abs(y) > this->_threshold && y < 0)
			actions.push_back(Action::ACTION_UP);
		else if (abs(y) > this->_threshold)
			actions.push_back(Action::ACTION_DOWN);

		if (abs(x) > this->_threshold && x < 0)
			actions.push_back(Action::ACTION_LEFT);
		else if (abs(x) > this->_threshold)
			actions.push_back(Action::ACTION_RIGHT);
	} else {
		start = 4;
		for (unsigned i = 0; i < 4; i++)
			if (this->_scene.isJoystickButtonPressed(this->_id, this->_keys[i]))
				actions.push_back(static_cast<Action>(i));
	}
	for (unsigned i = 0; i + start < this->_keys.size(); i++) {
		unsigned axis = 0;

		switch (this->_keys[i + start]) {
		case LEFT_JOYSTICK:
			throw ControllerException("Invalid key vector given (LEFT_JOYSTICK is not a valid key)");
		case RIGHT_JOYSTICK:
			throw ControllerException("Invalid key vector given (RIGHT_JOYSTICK is not a valid key)");
		case RT:
			axis = irr::SEvent::SJoystickEvent::AXIS_V;
			break;
		case LT:
			axis = irr::SEvent::SJoystickEvent::AXIS_Z;
			break;
		default:
			if (this->_scene.isJoystickButtonPressed(this->_id, this->_keys[i + start]))
				actions.push_back(static_cast<Action>(i + 4));
			continue;
		}
		if (this->_scene.getJoystickAxisPosition(this->_id, axis) > 0)
			actions.push_back(static_cast<Action>(i + 4));
	}
	return (actions);
}

void Input::Controller::changeKey(Action, unsigned) {}