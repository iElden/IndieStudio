#include <iostream>
#include <fstream>
#include "irrlicht/Keycodes.h"
#include "../irrlicht/screen/Screen.hpp"
#include "../irrlicht/game-scene/GameScene.hpp"
#include "../map/Map.hpp"
#include "../input/Keyboard.hpp"
#include "../ecs/Exceptions.hpp"

Map::Map *loadMap(ECS::Ressources &res, std::string path)
{
	std::ifstream stream(path);

	try {
		if (stream.is_open())
			return new Map::Map{res, stream};
	} catch (std::exception &e) {
		std::cerr << "The saved map is invalid " << e.what() << std::endl;
	}

	auto map = new Map::Map{res};

	map->generateMap({20, 20}, 70);
	return map;
}

int main()
{
	try {
		Irrlicht::Screen screen(640, 640, 32, false, false);
		screen.addGameScene("Game");
		std::vector<std::unique_ptr<Input::Input>> inputs;
		if (!screen.setCurrentGameScene("Game"))
			return EXIT_FAILURE;
		inputs.emplace_back(
			new Input::Keyboard(screen.getCurrentGameScene(), {
				irr::KEY_KEY_Z,
				irr::KEY_KEY_Q,
				irr::KEY_KEY_S,
				irr::KEY_KEY_D,
				irr::KEY_SPACE,
				irr::KEY_KEY_A,
			})
		);
		ECS::Ressources res{screen.getCurrentGameScene(), inputs};
		Map::Map *map = loadMap(res, "save.txt");

		for (auto &sound_name : sound_to_load)
			res.soundSystem.loadSound(sound_name);

		res.soundSystem.setBackgroundMusic("battle_music", 45); // tmp
		while (screen.display())
			map->update();

		std::ofstream stream("save.txt");

		stream << *map << std::endl;
		delete map;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}