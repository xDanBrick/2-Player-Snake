#include "PauseState.h"


PauseState::PauseState(const State& state) : State(state)
{
}

PauseState::~PauseState()
{
}

void PauseState::Update(const sf::Time& dt)
{

}

void PauseState::Render()
{

}

State* PauseState::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		return new Level(*this);
	}
	return NULL;
}
