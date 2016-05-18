#pragma once
#include <vector>
#include "GameObject.h"

enum Direction{ right = 0, left, up, down };
#define head 0

class Snake
{
	public:
		Snake();
		~Snake();

		void Move();
		inline void SetShootDirection(){ shootDirection_ = pieces_[head]->GetDirection(); };
		inline void SetButtonChange(bool change){ buttonChange_ = change; };
		inline void SetSnakeLength(int add){ snakeLength_ = add; };
		inline void SetPacketRecieved(bool change){ packetRecieved_ = change; };
		inline void KillNextMove(){ killNextMove_ = true; };
		inline void KillInTwoMoves(){ killInTwoMoves_ = true; };
		inline int GetSnakeLength(){ return snakeLength_; };
		inline void SetAlive(bool change){ alive_ = change; };
		inline void KillPlayer(){ Reset(); SetSnake(startPoint_, color_); };
		void Reset();
		void Collision();
		void SetSnake(sf::Vector2f position, sf::Color color);
		void Shoot();
		void BoxCollide();
		std::vector<GameObject* > pieces_;
		std::vector<GameObject* > playerBullets_;
		char inputMessage_[5];

	protected:
		float screenR_, screenL_, screenU_, screenD_;
		float pieceSize_;
		bool buttonChange_, alive_;
		bool isAttacking_;
		bool killNextMove_, killInTwoMoves_;
		bool packetRecieved_;
		int  snakeLength_, snakeMax_;
		int respawnCounter_;
		int killNextMoveCounter_;
		
		char shootDirection_;
		GameObject* bullet_;
		sf::Vector2f startPoint_;
		std::vector<GameObject*>* levelObjects_;
		sf::Color color_;

		void Update();
		void SnakeCollision();
};

