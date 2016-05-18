//main.cpp

//Includes
#include <SFML/Graphics.hpp>
#include "Application.h"

void main()
{
	//Application which updates and draws state of program
	Application application;

	//Clock for calculating delta time
	sf::Clock clock;

	//Record time for first update
	sf::Time previousTime = clock.getElapsedTime();

	//Keeps track of how out of sync application updates are compared to renders
	sf::Time lag = sf::seconds(0);

	//Desired time to update once.
	const sf::Time TIME_PER_UPDATE = sf::seconds(1) / 120.0f;

	//Game Loop
	//HandleInput() returns whether the game is still running
	while (application.HandleInput())
	{
		//Get current time
		sf::Time currentTime = clock.getElapsedTime();
		sf::Time dt = currentTime;
		//Get time since last update
		sf::Time deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		//Work out how much time there is to 
		lag += deltaTime;
		
		//Update until there is enough time to render
		while (lag >= TIME_PER_UPDATE)
		{
			application.Update(dt);
			lag -= TIME_PER_UPDATE;
		}

		//Calculate how far between two updates the frame will be rendered at
		float normalisedlag = lag / TIME_PER_UPDATE;

		//Render between the two updates
		application.Render(normalisedlag);
	}
}