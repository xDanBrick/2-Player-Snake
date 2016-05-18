#include "GetHostState.h"


GetHostState::GetHostState(const NetworkState& state) : NetworkState(state)
{
	//Set uo for the join and host box
	serverBox_.setPosition(300.0f, 200.0f);
	serverBox_.setSize(sf::Vector2f(200.0f, 200.0f));
	serverBox_.setFillColor(sf::Color::Red);
	clientBox_.setPosition(sf::Vector2f(700.0f, 200.0f));
	clientBox_.setSize(sf::Vector2f(200.0f, 200.0f));
	clientBox_.setFillColor(sf::Color::Red);
	//Set up the text for host and join box
	serverText_.setFont(*font_);
	serverText_.setPosition(375.0f, 275.0f);
	serverText_.setCharacterSize(50);
	serverText_.setString("Host");
	clientText_.setFont(*font_);
	clientText_.setPosition(775.0f, 275.0f);
	clientText_.setCharacterSize(50);
	clientText_.setString("Join");

}


GetHostState::~GetHostState()
{
}
void GetHostState::Update()
{

}

void GetHostState::Render()
{
	//Renders the boxes and the text
	window_->draw(serverBox_);
	window_->draw(clientBox_);
	window_->draw(clientText_);
	window_->draw(serverText_);
}

NetworkState* GetHostState::HandleInput()
{
	//If the Host button is pressed
	if (clientBox_.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		serverState_ = CLIENT;
		InitPlayers();
		return new WaitState(*this);
	}
	//If the join button is pressed
	if (serverBox_.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		serverState_ = SERVER;
		InitPlayers();
		listener_->listen(SERVERPORT);
		return new WaitState(*this);
	}
	return NULL;
}

void GetHostState::InitPlayers()
{
	if (serverState_ == SERVER)
	{
		//Add players
		player_ = new Player(sf::Vector2f(256.0f, 128.0f), sf::Color::Green, levelObjects_, window_);
		enemy_ = new Player(sf::Vector2f(1024.0f, 128.0f), sf::Color::Blue, levelObjects_, window_);
	}
	else if (serverState_ == CLIENT)
	{
		//Add players
		player_ = new Player(sf::Vector2f(1024.0f, 128.0f), sf::Color::Blue, levelObjects_, window_);
		enemy_ = new Player(sf::Vector2f(256.0f, 128.0f), sf::Color::Green, levelObjects_, window_);
	}
}
