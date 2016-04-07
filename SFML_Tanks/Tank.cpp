#include "Tank.h"




Tank::Tank()
	: m_sprite(NULL)
	, m_position(sf::Vector2f(0, 0))
	, m_move(500)
	, m_moveDirection(sf::Vector2f(0, 0))
	, m_boundingBox(sf::Vector2f(30, 30)) //trying to set the rect on the tank
{
	
}
Tank::~Tank()
{

}

void Tank::Update(float dt)
{
	m_position += m_moveDirection * m_move * dt;
	m_sprite->setPosition(m_position);
	m_moveDirection = sf::Vector2f(0, 0);
	m_boundingBox.setPosition(m_position.x, m_position.y);
}


float Tank::MoveSpeed()
{
	return m_move;
}


// Accessors
sf::Drawable* Tank::GetDrawable()
{
	return m_sprite;
}

void Tank::Draw(sf::RenderWindow* window)
{
	if (window == NULL)
	{
		return;
	}
	// references can't pass in null so can put onus on creator
	//sf::Drawable* test = NULL;
	//window->draw(*test);

	if (m_sprite != NULL)
	{
		window->draw(*m_sprite);
	}
	window->draw(m_boundingBox);
}

void Tank::SetSprite(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

void Tank::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

const sf::Vector2f Tank::GetPosition()
{
	return m_position;
}

const sf::RectangleShape Tank::getBounds()
{
	return m_boundingBox;
}


void Tank::Init()
{
	m_boundingBox.setFillColor(sf::Color::Transparent);
	m_boundingBox.setOutlineColor(sf::Color::Magenta);
	m_boundingBox.setOutlineThickness(2.0f);
	m_boundingBox.setSize(sf::Vector2f(50, 50));
	m_boundingBox.setOrigin(25, 25);
}



//Movement
void Tank::MoveRight()
{
	m_moveDirection = sf::Vector2f(1, 0);
	m_sprite->setRotation(-90);
}

void Tank::MoveLeft()
{
	m_moveDirection = sf::Vector2f(-1, 0);
	m_sprite->setRotation(90);
}

void Tank::MoveUp()
{
	m_moveDirection = sf::Vector2f(0, -1);
	m_sprite->setRotation(180);
}


void Tank::MoveDown()
{
	m_moveDirection = sf::Vector2f(0, 1);
	m_sprite->setRotation(0);
}



//float* luz = NULL;
//float* lol = new float(1);

//	sf::Drawable& temp = *m_sprite;
//	window->draw(temp);