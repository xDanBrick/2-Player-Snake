#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height, sf::Color color, int id)
{
	//Set Position and Dimentions
	setPosition(x, y);
	setSize(sf::Vector2f(width, height));
	setFillColor(color);
	id_ = id;
	direction_ = 'r';
	prevDirection_ = 'r';
	positionX_ = 'k';
	positionY_ = 'k';
}

GameObject::~GameObject()
{
}

bool GameObject::IsOn(GameObject& object)
{
	if (getPosition().x == object.getPosition().x && getPosition().y == object.getPosition().y)
	{
		return true;
	}
	return false;
}