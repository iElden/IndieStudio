/*
** EPITECH PROJECT, 2019
** IndieStudio
** File description:
** option-menu.hpp
*/

#ifndef OPTION_MENU_HPP
#define OPTION_MENU_HPP

#include <vector>
#include <memory>
#include "../GameScene.hpp"
#include "../hud/Button.hpp"

namespace Irrlicht
{
	enum OptionMenuButtonName
	{
		CHANGE_KEYS = 0,
		BACK_OPTIONS,
		VOLUME_LESS,
		VOLUME_MORE,
		VOLUME_MUTE
	};

	class OptionsMenu : public GameScene
	{
		public:
			OptionsMenu(Screen &screen, const std::string &name, unsigned id);
			~OptionsMenu() = default;
			void changeCurrentGameScene(std::string sceneName);
			bool update() override;

		private:
			//PROPERTIES
			std::vector<std::unique_ptr<Button>> _buttons;
	};
}

#endif