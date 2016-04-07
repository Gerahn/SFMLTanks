#include "Input.h"
#include "Tank.h"

Input::Input()
	: m_attachTank(NULL)
{

}

Input::~Input()
{

}

void Input::Update(float dt)
{
	if (m_attachTank == NULL)
	{
		return; //return will escape the entire method
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		//call move right function
		m_attachTank->MoveRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		//call move left function
		m_attachTank->MoveLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		//call move left function
		m_attachTank->MoveUp();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		//call move left function
		m_attachTank->MoveDown();
	}
}

void Input::AttachTank(Tank* tank)
{
	//could do a fancy message etc here 
	m_attachTank = tank;
}


