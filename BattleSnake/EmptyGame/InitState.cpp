#include "InitState.h"

InitState::InitState(sf::RenderWindow* window)
{
	window_ = window;
	font_ = new sf::Font;
	font_->loadFromFile("font.ttf");
}


InitState::~InitState()
{
}

void InitState::Update(const sf::Time& dt)
{

}

void InitState::Render()
{

}

State* InitState::HandleInput()
{
	return new StartScreenState(*this);
}