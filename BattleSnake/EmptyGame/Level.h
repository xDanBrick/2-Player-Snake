#pragma once
#include "State.h"
#include "InitNetworkState.h"

class Level : public State
{
	public:
		Level(const State& state);
		~Level();
		void Update(const sf::Time& dt);
		void Render();
		State* HandleInput();

	private:
		void CheckPlayerPosition();
		NetworkState* currentNetworkState_;
};

