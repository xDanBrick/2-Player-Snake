#include "GameState.h"

GameState::GameState(const NetworkState& state) : NetworkState(state)
{
	tickTime_ = sf::milliseconds(300);
	gameClock_->restart();
	gameTime_.Zero;
	//I tried taking the lag offset make when the clocks start more accurate but
	//it seemed to make it worse
	if (serverState_ == SERVER)
	{
		gameTime_ += *lagOffset_;
	}
	killsText_.setFont(*font_);
	killsText_.setPosition(700.0f, 20.0f);
	killsText_.setCharacterSize(50);
	killsText_.setString("Kills" + std::to_string(player_->kills_));
	packetSent_ = false;
	inputMessageSize_ = 5;
}


GameState::~GameState()
{
}

void GameState::Update()
{
	//Adds the time onto the last and restarts the clock
	gameTime_ += gameClock_->restart();
	//Updates the Player and Enemy
	UpdatePlayer();
	UpdateEnemy();
	killsText_.setString("Kills " + std::to_string(player_->kills_));
	//Locks the input half way through the update
	if (gameTime_.asMilliseconds() >= 150)
	{
		player_->SetButtonChange(false);
		//If a packet has not been sent
		if (!packetSent_)
		{
			//Sends a NULL PACKET
			char nullPacket[5] = { 'n', 'n', 'n', 'n', 'n'};
			if (player_->inputMessage_[4] == 'k')
			{
				nullPacket[4] = 'k';
			}
			if (enemySocket_->send(&nullPacket, inputMessageSize_) != sf::Socket::Done)
			{
				// error...
			}
			packetSent_ = true;
		}
	}
	//If the game time as done a tick
	if (gameTime_.asMilliseconds() >= tickTime_.asMilliseconds())
	{
		gameTime_ -= tickTime_;
		player_->Move();
		enemy_->Prediction();
		enemy_->Move();
		packetSent_ = false;
		enemy_->SetPacketRecieved(false);
	}
}

void GameState::Render()
{
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
	window_->draw(killsText_);
}

NetworkState* GameState::HandleInput()
{
	return NULL;
}

void GameState::UpdateEnemy()
{
	std::size_t received;
	char recievePacket[5];
	//Checks if there is any input to recieve
	if (enemySocket_->receive(&recievePacket, inputMessageSize_, received) == sf::Socket::Done)
	{
		if (recievePacket[0] != 'n')
		{
			for (int i = 0; i < inputMessageSize_; i++)
			{
				enemy_->inputMessage_[i] = recievePacket[i];
			}
			//Checks to see whether the directions are the same, if not kills the player
			if (enemy_->inputMessage_[2] != enemy_->pieces_[head]->GetDirection() ||
				enemy_->inputMessage_[3] != enemy_->pieces_[head]->GetPrevDirection())
			{
				//Kill next move
				player_->inputMessage_[4] = 'k';
				enemy_->KillInTwoMoves();
			}
			//If there is update the move or an attack
			enemy_->UserMovement();
			enemy_->UserAttack();
		}
		if (recievePacket[4] == 'k')
		{
			player_->KillNextMove();
		}
		enemy_->SetPacketRecieved(true);
	}
	//Update Enemy
	enemy_->Update(player_);
}
void GameState::UpdatePlayer()
{
	//If there are any new input commands
	if (player_->Controller(serverState_))
	{
		//Update the players movement
		player_->UserMovement();
		//Update the players attack
		player_->UserAttack();
		//Send the players movement to the other player
		if (enemySocket_->send(&player_->inputMessage_, inputMessageSize_) != sf::Socket::Done)
		{
		}
		//Resets the input message
		player_->inputMessage_[4] = 'n';
		packetSent_ = true;
	}
	//Update Player
	player_->Update(enemy_);
}

