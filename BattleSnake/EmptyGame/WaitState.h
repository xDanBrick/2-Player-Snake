#pragma once
#include "NetworkState.h"
#include "GameState.h"
class WaitState : public NetworkState
{
	public:
		WaitState(const NetworkState& state);
		~WaitState();
		void Update();
		void Render();
		NetworkState* HandleInput();
		bool connected_;
		sf::Text waitingText_;
};

