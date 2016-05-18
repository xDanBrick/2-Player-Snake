#pragma once
#include "NetworkState.h"
#include "GetHostState.h"

class InitNetworkState : public NetworkState
{
	public:
		InitNetworkState(sf::RenderWindow* window, sf::Font* font);
		~InitNetworkState();

		void Render();
		void Update();
		NetworkState* HandleInput();
};

