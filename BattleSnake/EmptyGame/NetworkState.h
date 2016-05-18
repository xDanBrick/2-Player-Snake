#pragma once
#include <SFML/System.hpp>
#include "Player.h"
#include "SFML\Graphics.hpp"

#define SERVERPORT 5555

class NetworkState
{
	public:
		NetworkState();
		~NetworkState();
		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual NetworkState* HandleInput() = 0;
		sf::Time* lagOffset_;
		enum SERVERSTATE{ CLIENT, SERVER };
		SERVERSTATE serverState_;
		sf::RenderWindow* window_;
		Player* player_, *enemy_;
		sf::TcpListener* listener_;
		sf::TcpSocket* enemySocket_;
		sf::Clock* gameClock_;
		sf::RectangleShape walls_;
		sf::Font* font_;
		std::vector<GameObject*>* levelObjects_;
};

