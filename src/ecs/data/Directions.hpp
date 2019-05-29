/*
** EPITECH PROJECT, 2019
** IndieStudio
** File description:
** Directions.hpp
*/

#ifndef DIRECTIONS_HPP
#define DIRECTIONS_HPP

namespace ECS
{
    enum Directions
    {
        UP = 0b1,
        LEFT = 0b10,
        DOWN = 0b100,
        RIGHT = 0b1000
    };
}; // namespace ECS

#endif