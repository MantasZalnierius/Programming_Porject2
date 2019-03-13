#include "Ghost.h"

Ghost::Ghost()
{
	setUpSprite();
	randomDirection = 0;
	m_isAlive = true;
	m_speed = 32;
	m_velocity = { 0.0, 0.0 };
}

Ghost::~Ghost()
{

}

void Ghost::setUpSprite()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/greenghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
	m_row = 10;
	m_col = 19;
	m_sprite.setPosition(m_col * 32, m_row * 32);
}

void Ghost::move(Cell t_cellType[][MAX_COLS])
{
	m_velocity = { 0.0, 0.0 };
	
	if (m_direction == GhostDirection::Left)
	{
		if (t_cellType[m_row][m_col - 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { -m_speed, 0.0 };
			m_sprite.move(m_velocity);
		}
		else
		{
			randomDirection = (rand() % 4) + 1;
		}
	}

	else if (m_direction == GhostDirection::Right)
	{
		if (t_cellType[m_row][m_col + 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { m_speed, 0.0 };
			m_sprite.move(m_velocity);
		}
		else
		{
			randomDirection = (rand() % 4) + 1;
		}
	}

	else if (m_direction == GhostDirection::Up)
	{
		if (t_cellType[m_row - 1][m_col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, -m_speed };
			m_sprite.move(m_velocity);
		}
		else
		{
			randomDirection = (rand() % 4) + 1;
		}
	}

	else if (m_direction == GhostDirection::Down)
	{
		if (t_cellType[m_row + 1][m_col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, m_speed };
			m_sprite.move(m_velocity);
		}
		else
		{
			randomDirection = (rand() % 4) + 1;
		}
	}
}

void Ghost::setDirection()
{
	if (randomDirection == 1)
	{
		m_direction = GhostDirection::Left;
	}
	else if (randomDirection == 2)
	{
		m_direction = GhostDirection::Right;
	}
	else if (randomDirection == 3)
	{
		m_direction = GhostDirection::Up;
	}
	else if (randomDirection == 4)
	{
		m_direction = GhostDirection::Down;
	}
}
