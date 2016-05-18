#pragma once
#include "NetworkState.h"
#include "WaitState.h"
class GetHostState : public NetworkState
{
	public:
		GetHostState(const NetworkState& state);
		~GetHostState();
		void Update();
		void Render();
		NetworkState* HandleInput();
		sf::RectangleShape clientBox_, serverBox_;
		sf::Text serverText_, clientText_;
		void InitPlayers();
};

