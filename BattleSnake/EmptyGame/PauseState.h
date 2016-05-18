#pragma once
#include "State.h"
#include "Level.h"

class PauseState : public State
{
	public:
		PauseState(const State& state);
		~PauseState();

		void Update(const sf::Time& dt);
		void Render();
		State* HandleInput();
};

