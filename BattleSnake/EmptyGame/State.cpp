#include "State.h"

State::~State()
{
}

sf::Text State::SetText(float x, float y, int size)
{
	sf::Text text;
	text.setPosition(x, y);
	text.setFont(*font_);
	text.setCharacterSize(size);
	return text;
}

