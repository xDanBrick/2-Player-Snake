#include "Player.h"

Player::Player(sf::Vector2f position, sf::Color color, std::vector<GameObject* >* levelObjects, sf::RenderWindow* window)
{
	//Set up the snake
	SetSnake(position, color);
	inputMessage_[0] = 'r';
	inputMessage_[1] = 'n';
	inputMessage_[2] = 'r';
	inputMessage_[3] = 'r';
	inputMessage_[4] = 'n';
	levelObjects_ = levelObjects;
	window_ = window;
	color_ = color;
	//Set up how many bullets the player has
	for (int i = 0; i < 3; i++)
	{
		playerBullets_.push_back(new GameObject(200.0f + (50.0f * i), 20.0f, 30.0f, 30.0f, sf::Color::Red));
	}
}

Player::~Player()
{
}

void Player::Update(Snake* snake)
{
	EnemyCollision(snake);
	Snake::Update();
}

void Player::UserAttack()
{
	if (!isAttacking_ && !playerBullets_.empty() && inputMessage_[1] == 's')
	{
		bullet_ = new GameObject(pieces_[head]->getPosition().x, pieces_[0]->getPosition().y, pieceSize_, pieceSize_, sf::Color::Red);
		isAttacking_ = true;
		SetShootDirection();
		playerBullets_.pop_back();
	}
}

void Player::UserMovement()
{
	//If Down is pressed
	if (inputMessage_[0] == 'd')
	{
		pieces_[head]->SetDirection('d');
		buttonChange_ = false;
	}
	//If Up is pressed
	if (inputMessage_[0] == 'u')
	{
		pieces_[head]->SetDirection('u');
		buttonChange_ = false;
	}
	//If Right is pressed
	if (inputMessage_[0] == 'r')
	{
		pieces_[head]->SetDirection('r');
		buttonChange_ = false;
	}
	//If Left is pressed
	if (inputMessage_[0] == 'l')
	{
		pieces_[head]->SetDirection('l');
		buttonChange_ = false;
	}
}

void Player::Render()
{
	//Render snake
	for (int i = 0; i < GetSnakeLength(); i++)
	{
		window_->draw(*pieces_[i]);
	}
	//Render bullet
	if (bullet_ != NULL)
	{
		window_->draw(*bullet_);
	}
}

bool Player::Controller(int state)
{
	if (buttonChange_)
	{
		//Whether its a client or a server
		if (state == 0)
		{
			//If Down is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && pieces_[0]->GetDirection() != 'u'  && pieces_[0]->GetDirection() != 'd')
			{
				inputMessage_[0] = 'd';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Up is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && pieces_[0]->GetDirection() != 'd' && pieces_[0]->GetDirection() != 'u')
			{
				inputMessage_[0] = 'u';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Right is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && pieces_[0]->GetDirection() != 'l' &&  pieces_[0]->GetDirection() != 'r')
			{
				inputMessage_[0] = 'r';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Left is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && pieces_[0]->GetDirection() != 'r' && pieces_[0]->GetDirection() != 'l')
			{
				inputMessage_[0] = 'l';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Enter is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !playerBullets_.empty())
			{
				inputMessage_[1] = 's';
				return true;
			}
		}
		else
		{
			//If Down is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && pieces_[0]->GetDirection() != 'u'  && pieces_[0]->GetDirection() != 'd')
			{
				inputMessage_[0] = 'd';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Up is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && pieces_[0]->GetDirection() != 'd' && pieces_[0]->GetDirection() != 'u')
			{
				inputMessage_[0] = 'u';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Right is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && pieces_[0]->GetDirection() != 'l' && pieces_[0]->GetDirection() != 'r')
			{
				inputMessage_[0] = 'r';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If Left is pressed
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && pieces_[0]->GetDirection() != 'r' && pieces_[0]->GetDirection() != 'l')
			{
				inputMessage_[0] = 'l';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
			//If E is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && !playerBullets_.empty())
			{
				inputMessage_[1] = 's';
				//Sets the input messege to the directions
				inputMessage_[2] = pieces_[0]->GetDirection();
				inputMessage_[3] = pieces_[0]->GetPrevDirection();
				return true;
			}
		}
	}
	return false;
}

void Player::EnemyCollision(Snake* snake)
{
	//For the length of the other snake
	for (int i = 0; i < snake->GetSnakeLength(); i++)
	{
		//Check if the head of the player hits the other snake
		if (pieces_[0]->IsOn(*snake->pieces_[i]))
		{
			alive_ = false;
		}
		//If there is a bullet being shot
		if (bullet_ != NULL)
		{
			if (bullet_->getGlobalBounds().intersects(snake->pieces_[i]->getGlobalBounds()))
			{
				snake->SetSnakeLength(i);
				//If the bullet hits the other snakes head
				if (i == 0)
				{
					snake->SetAlive(false);
					kills_++;
				}
				BoxCollide();
			}
		}
	}
}

void Player::Prediction()
{
	//If a packet has not been recieved
	if (!packetRecieved_)
	{
		//Check for both collectable blocks
		for (int i = 0; i < levelObjects_->size(); i++)
		{
			//If the snakes heads x position is equal to a collectable block
			if (pieces_[head]->getPosition().x == levelObjects_->at(i)->getPosition().x)
			{
				if (pieces_[head]->getPosition().y > levelObjects_->at(i)->getPosition().y && pieces_[head]->GetDirection() != 'd')
				{
					pieces_[head]->SetDirection('u');
				}
				else if (pieces_[head]->GetDirection() != 'u')
				{
					pieces_[head]->SetDirection('d');
				}
			}
			//If the snakes heads y position is equal to a collectable block
			if (pieces_[head]->getPosition().y == levelObjects_->at(i)->getPosition().y)
			{
				if (pieces_[head]->getPosition().x < levelObjects_->at(i)->getPosition().x && pieces_[head]->GetDirection() != 'l')
				{					
					pieces_[head]->SetDirection('r');	
				}
				else if (pieces_[head]->GetDirection() != 'r')
				{
					pieces_[head]->SetDirection('l');
				}
			}
		}
	}
}