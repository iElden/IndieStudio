/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** ControlledByAISystem.hpp
*/

#ifndef BOMBERMAN_CONTROLLEDBYAISYSTEM_HPP
#define BOMBERMAN_CONTROLLEDBYAISYSTEM_HPP


#include "../System.hpp"
#include "../../input/Input.hpp"
#include "../components/MovableComponent.hpp"

namespace ECS
{
    class ControlledByAISystem : public System {
    public:
        ControlledByAISystem(ECSCore &core);
        void updateEntity(Entity &entity) override;
        std::vector<Input::Action> AIBrain(Entity &entity, MovableComponent &movable);
    };
}

#endif //BOMBERMAN_CONTROLLEDBYAISYSTEM_HPP
