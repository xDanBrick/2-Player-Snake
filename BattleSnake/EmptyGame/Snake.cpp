#include "Snake.h"

Snake::Snake()
{
	screenR_ = 1216.0f;
	screenU_ = 96.0f;
	screenD_ = 608.0f;
	screenL_ = 64.0f;
	snakeMax_ = 20;
	pieceSize_ = 32.0f;
	Reset();
}

Snake::~Snake()
{

}

void Snake::Reset()
{
	bullet_ = NULL;
	alive_ = true;
	isAttacking_ = false;
	snakeLength_ = 5;
	respawnCounter_ = 0;
	pieces_.clear();
	packetRecieved_ = false;
	killNextMove_ = false;
	killInTwoMoves_ = false;
	killNextMoveCounter_ = 0;
}

void Snake::Collision()
{
	//Checking collision between the level objects
	for (int i = 0; i < levelObjects_->size(); i++)
	{
		if (pieces_[head]->IsOn(*levelObjects_->at(i)))
		{
			//If the player collides with a health
			if (levelObjects_->at(i)->id_ == HEALTH && snakeLength_ < snakeMax_ - 1)
			{
				snakeLength_++;
				levelObjects_->at(i)->RandBlock();
			}
			//If the player collides with a bullet
			if (levelObjects_->at(i)->id_ == BULLET && playerBullets_.size() < 10)
			{
				playerBullets_.push_back(new GameObject(200.0f + (50.0f * playerBullets_.size()), 20.0f, 30.0f, 30.0f, sf::Color::Red));
				levelObjects_->at(i)->RandBlock();
			}
		}
	}
	//Checks if the snake collides with itself
	for (int i = 1; i < snakeLength_; i++)
	{
		if (pieces_[0]->IsOn(*pieces_[i]))
		{
			alive_ = false;
		}
	}
}

void Snake::SetSnake(sf::Vector2f position, sf::Color color)
{
	startPoint_ = position;
	for (int snakePiece = head; snakePiece < snakeMax_; snakePiece++)
	{
		pieces_.push_back(new GameObject(position.x - (pieceSize_ * snakePiece), position.y, pieceSize_, pieceSize_, color));
	}
}

void Snake::Shoot()
{
	if (isAttacking_)
	{
		switch (shootDirection_)
		{
			case 'r':
			{
				bullet_->MoveX(5.0f);
				break;
			}
			case 'l':
			{
				bullet_->MoveX(-5.0f);
				break;
			}
			case 'u':
			{
				bullet_->MoveY(-5.0f);
				break;
			}
			case 'd':
			{
				bullet_->MoveY(5.0f);
				break;
			}
		}
		if (bullet_->getPosition().x + bullet_->getSize().x > screenR_ || bullet_->getPosition().x < screenL_ ||
			bullet_->getPosition().y < screenU_|| bullet_->getPosition().y + bullet_->getSize().y > screenD_)
		{
			BoxCollide();
		}
	}
}

void Snake::BoxCollide()
{
	isAttacking_ = false;
	inputMessage_[1] = 'n';
	delete bullet_;
	bullet_ = NULL;
}

void Snake::Move()
{
	//Only move when its alive
	if (killNextMove_)
	{
		killNextMove_ = false;
		inputMessage_[4] = 'n';
	}
	if (killInTwoMoves_)
	{
		if (killNextMoveCounter_ == 1)
		{
			killNextMoveCounter_ = 0;
			killInTwoMoves_ = false;
			inputMessage_[4] = 'n';
		}
		else killNextMoveCounter_++;
	}
	if (alive_)
	{
		//For how many Snake peices there are
		for (int snakePiece = head; snakePiece < snakeMax_ - 1; snakePiece++)
		{
			//Depening on which direction the head goes and they all follow
			switch (pieces_[snakePiece]->GetDirection())
			{
				case 'r':
				{
					pieces_[snakePiece]->MoveX(pieceSize_);
					pieces_[snakePiece]->positionX_++;
					pieces_[snakePiece + 1]->SetDirection(pieces_[snakePiece]->GetPrevDirection());
					//If it hits the right wall
					if (pieces_[snakePiece]->getPosition().x == screenR_)
					{
						pieces_[snakePiece]->setPosition(screenL_, pieces_[snakePiece]->getPosition().y);
					}
					break;
				}
				case 'l':
				{
					pieces_[snakePiece]->MoveX(-pieceSize_);
					pieces_[snakePiece]->positionX_--;
					pieces_[snakePiece + 1]->SetDirection(pieces_[snakePiece]->GetPrevDirection());
					//If it hits the left wall
					if (pieces_[snakePiece]->getPosition().x == screenL_ - pieceSize_)
					{
						pieces_[snakePiece]->setPosition(screenR_ - pieceSize_, pieces_[snakePiece]->getPosition().y);
					}
					break;
				}
				case 'u':
				{
					pieces_[snakePiece]->MoveY(-pieceSize_);
					pieces_[snakePiece]->positionY_--;
					pieces_[snakePiece + 1]->SetDirection(pieces_[snakePiece]->GetPrevDirection());
					//If it hits the up wall
					if (pieces_[snakePiece]->getPosition().y == screenU_ - pieceSize_)
					{
						pieces_[snakePiece]->setPosition(pieces_[snakePiece]->getPosition().x, screenD_ - pieceSize_);
					}
					break;
				}
				case 'd':
				{
					pieces_[snakePiece]->MoveY(pieceSize_);
					pieces_[snakePiece]->positionY_++;
					pieces_[snakePiece + 1]->SetDirection(pieces_[snakePiece]->GetPrevDirection());
					//If it hits the down wall
					if (pieces_[snakePiece]->getPosition().y == screenD_)
					{
						pieces_[snakePiece]->setPosition(pieces_[snakePiece]->getPosition().x, screenU_);
					}
					break;
				}
			}
			pieces_[snakePiece]->SetPrevDirection(pieces_[snakePiece]->GetDirection());
		}
		buttonChange_ = true;
	}
}

void Snake::Update()
{
	if (alive_)
	{
		Shoot();
		Collision();
	}
	else
	{
		respawnCounter_++;
		if (respawnCounter_ == 100)
		{
			KillPlayer();
		}
	}
}