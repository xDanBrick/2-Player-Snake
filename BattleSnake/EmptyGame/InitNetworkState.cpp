#include "InitNetworkState.h"


InitNetworkState::InitNetworkState(sf::RenderWindow* window, sf::Font* font)
{
	window_ = window;
	font_ = font;
	listener_ = new sf::TcpListener;
	enemySocket_ = new sf::TcpSocket;

	//Setting the sockets to non blocking
	listener_->setBlocking(false);
	enemySocket_->setBlocking(false);

	//Add health and bullets
	levelObjects_ = new std::vector < GameObject* >;
	levelObjects_->push_back(new GameObject(256.0f, 256.0f, 32.0f, 32.0f, sf::Color::White, HEALTH));
	levelObjects_->push_back(new GameObject(512.0f, 512.0f, 32.0f, 32.0f, sf::Color::Red, BULLET));

	//Setting up the wall
	walls_.setPosition(64.0f, 96.0f);
	walls_.setFillColor(sf::Color::Transparent);
	walls_.setOutlineColor(sf::Color::White);
	walls_.setOutlineThickness(5.0f);
	walls_.setSize(sf::Vector2f(1152.0f, 512.0f));

	gameClock_ = new sf::Clock;
	lagOffset_ = new sf::Time;
}


InitNetworkState::~InitNetworkState()
{
}

void InitNetworkState::Update()
{

}

void InitNetworkState::Render()
{

}

NetworkState* InitNetworkState::HandleInput()
{
	return new GetHostState(*this);
}
