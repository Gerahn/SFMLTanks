#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Tank.h"
#include "Input.h"
#include "GameState.h"


int main()
{
	srand(time(0));


	//Window
	sf::VideoMode Res = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(Res.width, Res.height), "SFML works!", sf::Style::None | sf::Style::Fullscreen);
	//window.setPosition(sf::Vector2i(Res.width * 0.1, Res.height * 0.1));




	//Creating and loading texture
	sf::Texture texture;
	if (!texture.loadFromFile("ptank.png"))
	{
		printf("no texture");
	}

	sf::Texture titleBack;
	if (!titleBack.loadFromFile("howl2.jpg"))
	{
		printf("no texture");
	}

	sf::Texture titleText;
	if (!titleText.loadFromFile("title.png"))
	{
		printf("no texture");
	}


	sf::Sprite sprTitleBack(titleBack);
	sf::Sprite sprTitleText(titleText);

	//Creating Sprite
	sf::Sprite* sprite = new sf::Sprite(texture);
	sprite->setPosition(30, 30);
	sprite->setOrigin(25.0f, 25.0f);
	Tank playerTank;
	playerTank.SetSprite(sprite);
	
	Input input;
	input.AttachTank(&playerTank);

	playerTank.Init();


	//TEST - Circle
	sf::CircleShape circleTest;
	circleTest.setFillColor(sf::Color::Blue);
	circleTest.setPosition(300, 300);
	circleTest.setRadius(30.f);
	sf::FloatRect circleBounds = circleTest.getGlobalBounds();
	sf::RectangleShape circleColSquare(sf::Vector2f(circleBounds.width, circleBounds.height));
	circleColSquare.setPosition(circleBounds.left, circleBounds.top);
	circleColSquare.setOutlineColor(sf::Color::Green);
	circleColSquare.setOutlineThickness(2.0f);
	circleColSquare.setFillColor(sf::Color::Transparent);
	

	//TankBounds - Temp Bounds
	// C style array and memory copying
	// ===more reading in C++ array memory management====
	//int* array = new int[10];
	//int* temp = array;
	//array = new int[20];
	//memcpy(array, temp, sizeof(int) * 10);
	//delete[] temp;
	//
	//int* shortArray = new int[10];
	//int* shortTemp = shortArray;
	//shortArray = new int[5];
	//memcpy(array, temp, sizeof(int) * 5);
	//delete[] shortTemp;


	//Circles - Creation - Number of 
	const int circlecount = 50;
	Tank tanks[circlecount];

	//const int enemyTankCount = 50;
	//Tank** enemyTanks = new Tank*[enemyTankCount];

	//Second star is like Oprah
	//we don't know this is an array
	//stack (1mb)  vs heap
	// learn about this and not use it

	//Green Circle - tanks[i].GetCircle().setFillColor(sf::Color::Green);
	for (int i = 0; i < circlecount; i++)
	{
		//int = 

		sf::Sprite* newSprite = new sf::Sprite(texture);
		newSprite->setColor(sf::Color(255, 128, 128, 255));
		newSprite->setPosition(30, 30);
		newSprite->setOrigin(25.0f, 25.0f);

		int randomX = rand() % window.getSize().x;
		int randomY = rand() % window.getSize().y;

		tanks[i].SetSprite(newSprite);
		tanks[i].SetPosition(sf::Vector2f(randomX, randomY));
		tanks[i].Init();
		//enemyTanks[i] = new Tank();
		//enemyTanks[i]->SetSprite(newSprite);
		//enemyTanks[i]->SetPosition(sf::Vector2f(randomX, randomY));
		//enemyTanks[i]->Init();
	}

	

	enum GState { Title, Main, Pause, GameOver };

	GState gState;
	gState = Title;
	int a = 0;


	//Delta Time (Clock)
	sf::Clock deltaClock;
	sf::Clock titleFadeIn;
	float tfadein = titleFadeIn.getElapsedTime().asSeconds();
	bool fadeT = false;


	//Main Loop
	while (window.isOpen())
	{
		
		while (gState == Title)
		{
		
			//if (tfadein >= 3)
			//{
			//	fadeT = true;
			//}

			if (/*fadeT == true &&*/ tfadein >= 0.01f)
			{
				if (a < 255)
				{
					a += 1;
				}

				titleFadeIn.restart();
			}


			sprTitleText.setColor(sf::Color(255, 255, 255, a));
			
			window.draw(sprTitleBack);
			window.draw(sprTitleText);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
			{
				gState = Main;
			}

		}


		while (gState == Main)
		{

			float dt = deltaClock.restart().asSeconds();
			//Delta time decouples from frame rate

			if (dt > 1.0f / 60.0f)
				//If the next frame is higher than 1 in 60 - the cap stops it from going further e,g window is held
			{
				dt = 1.0f / 60.0f;
			}

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//Clear Screen
			window.clear();

			input.Update(dt);

			//Red Circle Movement
			for (int i = 0; i < circlecount; i++)
			{
				sf::Vector2f movelose((rand() % 5) - 2, (rand() % 5) - 2);
				sf::Vector2f currentposition(tanks[i].GetPosition());

				tanks[i].SetPosition((movelose * dt * tanks[i].MoveSpeed()) + currentposition);
			}

			// UPDATE LOOP
			for (int i = 0; i < circlecount; ++i)
			{
				tanks[i].Update(dt);
			}
			playerTank.Update(dt);

			//Draw Loop for red circles
			for (int i = 0; i < circlecount; i++)
			{
				if (tanks[i].GetDrawable() != NULL)
				{
					window.draw(*tanks[i].GetDrawable());
					window.draw(tanks[i].getBounds());
				}
			}


			// Draw player
			//window.draw(*playerTank.GetDrawable());
			//window.draw(playerTank.getBounds());
			playerTank.Draw(&window);
			window.draw(circleTest);
			window.draw(circleColSquare);

			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{

				window.close();
			}
		}
		//EndMainLoop

	}





	return 0;
}
