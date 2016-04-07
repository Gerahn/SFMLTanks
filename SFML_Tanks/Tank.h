#pragma once
#ifndef _TANK_H_
#define _TANK_H_

#include <SFML/Graphics.hpp>

class Tank
{
public:
	// Constructors
	Tank();
	~Tank();

	void Update(float dt);

	//Movement
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();


	// Accessors
	sf::Drawable* GetDrawable();
	void Draw(sf::RenderWindow* window);

	void SetSprite(sf::Sprite* sprite); // a bit of memory with an address to a window that has been allocated elsewhere

	void SetPosition(sf::Vector2f position);
	const sf::Vector2f GetPosition();
	const sf::RectangleShape getBounds();
	void Init();
	float MoveSpeed();

private:
	// Member variables
	sf::Vector2f m_position;
	sf::Vector2f m_moveDirection;
	sf::Sprite* m_sprite;
	float m_move;
	sf::RectangleShape m_boundingBox; 
	
// keeping a window here doesn' tmake sense, what if windodw is sdestoyred 	
	//think, does a tank have a window?

};

#endif