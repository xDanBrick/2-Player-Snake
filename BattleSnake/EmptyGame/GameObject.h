#pragma once
#include <SFML\Graphics.hpp>

using sf::Sprite;
enum ID{PIECE, HEALTH, BULLET};

class GameObject : public sf::RectangleShape
{
	public:
		GameObject(float x, float y, float width, float height, sf::Color color, int id = PIECE);
		~GameObject();
		sf::Texture* texture_;
		inline void RandBlock(){ setPosition(((rand() % 35) * 32.0f) + 64.0f, ((rand() % 14) * 32.0f) + 96.0f); };
		inline void MoveX(float dis){ float xVel = dis + getPosition().x; setPosition(xVel, getPosition().y); };
		inline void MoveY(float dis){ float yVel = dis + getPosition().y; setPosition(getPosition().x, yVel); };
		inline void SetDirection(char dir){ direction_ = dir; };
		inline char GetDirection(){ return direction_; };
		inline void SetPrevDirection(char dir){ prevDirection_ = dir; };
		inline char GetPrevDirection(){ return prevDirection_; }
		int id_;
		char positionX_, positionY_;
		bool IsOn(GameObject& object);

	private:
		char prevDirection_, direction_;
};

