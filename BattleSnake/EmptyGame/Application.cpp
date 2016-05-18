//Application.cpp

//Includes
#include "Application.h"
#include <SFML\Window\Keyboard.hpp>

//Usings
using sf::Keyboard;

//Constructor
Application::Application() : window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Battle Snakes")
{
	//Initialise everything
	currentState = new InitState(&window);
}

//Handles keyboard input
bool Application::HandleInput()
{
	//Deal with window closing
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return false;
		}
	}

	//If escape key pressed
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		//Exit application
		window.close();
		return false;
	}
	return true;
}

//Updates the game
void Application::Update(const sf::Time& dt)
{
	//Update everything
	State* newState = currentState->HandleInput();
	if (newState != NULL)
	{
		delete currentState;
		currentState = newState;
	}
	currentState->Update(dt);
}

//Renders game to the window
void Application::Render(const float& normalisedLag)
{
	//Clear previous frame
	window.clear();

	//Draw everything
	currentState->Render();

	//Display the frame
	window.display();
}