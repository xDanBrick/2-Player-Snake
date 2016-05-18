#include "StartScreenState.h"

StartScreenState::StartScreenState(const State& state) : State(state)
{
	startButton_.setPosition(sf::Vector2f(500.0f, 350.0f));
	startButton_.setSize(sf::Vector2f(400.0f, 150.0f));
	startButton_.setOutlineColor(sf::Color::White);
	startButton_.setOutlineThickness(3.0f);
	startButton_.setFillColor(sf::Color::Blue);
	text_ = SetText(665.0f, 390.0f, 50);
	text_.setString("START");
	title_ = SetText(535.0f, 100.0f, 100);
	title_.setString("Battle Snake");
}


StartScreenState::~StartScreenState()
{
}

void StartScreenState::Update(const sf::Time& dt)
{

}

void StartScreenState::Render()
{
	window_->draw(startButton_);
	window_->draw(text_);
	window_->draw(title_);
}

State* StartScreenState::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		return new Level(*this);
	}
	if (startButton_.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return new Level(*this);
	}
	return NULL;
}
