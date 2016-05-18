#pragma once
#include "NetworkState.h"
class GameState : public NetworkState
{
	public:
		GameState(const NetworkState& state);
		~GameState();
		void Update();
		void Render();
		NetworkState* HandleInput();
		void UpdatePlayer();
		void UpdateEnemy();
		sf::Time tickTime_, gameTime_;
		sf::Text killsText_;
		void CheckPlayerPosition();
		int gameTicks_;
		int inputMessageSize_;
		bool packetSent_;
};

