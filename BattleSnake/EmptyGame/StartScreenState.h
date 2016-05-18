#pragma once
#include "State.h"
#include "Level.h"

class StartScreenState : public State
{
	public:
		StartScreenState(const State& state);
		~StartScreenState();

		void Update(const sf::Time& dt);
		void Render();
		State* HandleInput();
		sf::RectangleShape startButton_;
		sf::Text text_;
		sf::Text title_;
};

