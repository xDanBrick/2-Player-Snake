//Application.h

#pragma once

//Includes
#include "InitState.h"

#define SCREENWIDTH 1350
#define SCREENHEIGHT 650
//Usings
using sf::RenderWindow;

//Application which input-handles, updates and renders the game.
class Application
{
	public:
		Application();						//Constructor
		bool HandleInput();					//Handles keyboard input. Returns whether game has exited or not
		void Update(const sf::Time& dt);	//Updates the application
		void Render(const float& normalisedLag);	//Renders application to the window

	private:
		RenderWindow window;	//Window which is drawn to
		State* currentState;
};