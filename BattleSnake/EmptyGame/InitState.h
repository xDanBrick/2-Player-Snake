#pragma once
#include "State.h"
#include "StartScreenState.h"

class InitState : public State
{
	public:
		InitState(sf::RenderWindow* window);
		~InitState();

		void Update(const sf::Time& dt);
		void Render();
		State* HandleInput();
};

