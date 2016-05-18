#pragma once
#include "Player.h"
#include "GameObject.h"


class State
{
	public:
		~State();
		virtual void Update(const sf::Time& dt) = 0;
		virtual void Render() = 0;
		virtual State* HandleInput() = 0;
		sf::RenderWindow* window_;
		sf::Font* font_;
		sf::Text SetText(float x, float y, int size);
};

