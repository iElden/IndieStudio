/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** EventReceiver.hpp
*/

#ifndef BOMBERMAN_EVENTRECEIVER_HPP
#define BOMBERMAN_EVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#define MAX_BUTTON_ON_SCREEN 25

namespace Irrlicht
{
	class EventReceiver : public irr::IEventReceiver
	{
	public:
		explicit EventReceiver();
		~EventReceiver() = default;

		//MEMBER FUNCTIONS
		virtual bool OnEvent(const irr::SEvent &event) override;
//		void addContext();
		virtual bool isKeyPressed(irr::EKEY_CODE keyCode) const;
		const irr::SEvent::SJoystickEvent &GetJoystickState(unsigned id) const;
		bool isGuiButtonPressed(unsigned id);
		bool isJoystickKeyPressed(unsigned id, irr::u32 key) const;
		float getJoystickAxisPosition(unsigned id, irr::s16 axis) const;

	private:
		//PROPERTIES
		std::vector<bool> _keys;
		std::vector<irr::SEvent::SJoystickEvent> _joystickState{4};
		std::vector<bool> _buttonState;
	};
}


#endif //BOMBERMAN_EVENTRECEIVER_HPP
