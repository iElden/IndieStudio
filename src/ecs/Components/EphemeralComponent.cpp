/*
** EPITECH PROJECT, 2018
** ECS
** File description:
** EphemeralComponent.cpp
*/

#include "EphemeralComponent.hpp"

namespace ECS
{
	EphemeralComponent::EphemeralComponent(unsigned int timeLeft) : 
		Component("Ephemeral"),
		timeLeft(timeLeft)
	{
	}
}