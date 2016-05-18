#include "WaitState.h"


WaitState::WaitState(const NetworkState& state) : NetworkState(state)
{
	connected_ = false;
	lagOffset_->Zero;
	waitingText_.setFont(*font_);
	waitingText_.setPosition(500.0f, 290.0f);
	waitingText_.setCharacterSize(50);
	waitingText_.setString("Waiting To Connect To Player");
}


WaitState::~WaitState()
{
}
void WaitState::Update()
{
	
}

void WaitState::Render()
{
	if (connected_)
	{
		waitingText_.setString("Press H to start");
	}
	//Draws the waiting text
	window_->draw(waitingText_);
	//Render health and bullets
	for (int i = 0; i < levelObjects_->size(); i++)
	{
		window_->draw(*levelObjects_->at(i));
	}
	//Render outer edge
	window_->draw(walls_);
	//Render players
	player_->Render();
	enemy_->Render();
	//Render hud for the player you are
	for (int i = 0; i < player_->playerBullets_.size(); i++)
	{
		window_->draw(*player_->playerBullets_[i]);
	}
	//window_->draw(killsText_);
}

NetworkState* WaitState::HandleInput()
{
	std::size_t received;
	char startMessage;
	if (serverState_ == SERVER)
	{
		//If the server is not connected
		if (!connected_)
		{
			//Listens fo someone tring to connect
			if (listener_->accept(*enemySocket_) == sf::Socket::Done)
			{
				connected_ = true;
				char message = 'o';
				gameClock_->restart();
				//Sends a message to the client to calculate the lag offset
				if (enemySocket_->send(&message, 1) != sf::Socket::Done)
				{
				}
			}
		}
		else
		{
			char message;
			//Waits to recieve a message from the client to calculate the lag offset
			if (enemySocket_->receive(&message, 1, received) == sf::Socket::Done)
			{
				if (message == 'o')
				{
					//The offset is half of the amount of time that has passes since the message was sent
					*lagOffset_ = gameClock_->getElapsedTime() * 0.5f;
				}
			}
			//If H is pressed and the lag offset is calculated
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && lagOffset_->asMilliseconds() > 0)
			{
				startMessage = 's';
				gameClock_->restart();
				if (enemySocket_->send(&startMessage, 1) != sf::Socket::Done)
				{
					// error...
				}
				return new GameState(*this);
			}
		}
	}
	else if (serverState_ == CLIENT)
	{
		//If the client is not connected
		if (!connected_)
		{
			//Tries to connect to a server
			sf::Socket::Status status = enemySocket_->connect(sf::IpAddress::getLocalAddress(), SERVERPORT);
			if (status == sf::Socket::Done)
			{
				connected_ = true;
			}
		}
		else
		{
			//Waits to recieve a message to calculate the lag offset or start game
			if (enemySocket_->receive(&startMessage, 1, received) == sf::Socket::Done)
			{
				if (startMessage == 'o')
				{
					char message = 'o';
					//Sends a message to the sever to calcualate the lag offset
					if (enemySocket_->send(&message, 1) != sf::Socket::Done)
					{
						// error...
					}
				}
				if (startMessage == 's')
				{
					//If the connection is succesfull it is allowed to move on
					return new GameState(*this);
					char message = 'g';
				}

			}
		}
	}
	return NULL;
}
