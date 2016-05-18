#pragma once
#include "Snake.h"
#include "SFML\Network.hpp"
#include <string>
using std::string;

class Player : public Snake
{
	public:
		Player(sf::Vector2f position, sf::Color color, std::vector<GameObject* >* levelObjects, sf::RenderWindow* window);
		~Player();
		void Update(Snake* snake);
		void UserMovement();
		void UserAttack();
		void Render();
		sf::RenderWindow* window_;
		bool Controller(int state);
		void EnemyCollision(Snake* snake);
		int kills_;
		void Prediction();
};

