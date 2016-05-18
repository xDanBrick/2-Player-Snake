#include "Level.h"

Level::Level(const State& state) : State(state)
{
	currentNetworkState_ = new InitNetworkState(window_, font_);
}

Level::~Level()
{
}

void Level::Update(const sf::Time& dt)
{
	NetworkState* newState = currentNetworkState_->HandleInput();

	if (newState != NULL)
	{
		delete currentNetworkState_;
		currentNetworkState_ = newState;
	}
	currentNetworkState_->Update();
}

void Level::Render()
{
	currentNetworkState_->Render();
}

State* Level::HandleInput()
{
	return NULL;
}

