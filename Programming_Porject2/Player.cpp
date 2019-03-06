#include "Player.h"

Player::Player()
{
	setUpSprite();
}

Player::~Player()
{
}

void Player::setUpSprite()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/mspacman32.png"))
	{
		std::cout << "Error ";
	}
	row = 22;
	col = 2;
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 31, 35 });
	m_sprite.setPosition(col * 32, row * 32);
	m_velocity = { 0.0f, 0.0f };
	speed = 32;
}

void Player::move(int t_levelDate[][MAX_COLS])
{
	speed = 0;

	if (direction == 1)
	{
		if (t_levelDate[row][col - 1] != 1)
		{
			col--;
			speed = 32;
		}
	}

	if (direction == 2)
	{
		if (t_levelDate[row][col + 1] != 1)
		{
			col++;
			speed = 32;
		}
	}

	if (direction == 3)
	{
		if (t_levelDate[row - 1][col] != 1)
		{
			row--;
			speed = 32;
		}
	}

	if (direction == 4)
	{
		if (t_levelDate[row + 1][col] != 1)
		{
			row++;
			speed = 32;
		}
	}

	//m_velocity = sf::Vector2f{ 0.0f, 0.0f };

	//if (direction == 1)
	//{
	//	if (t_levelDate[row][--col] != 1)
	//	{
	//		m_velocity = { -5.0f, 0.0 };
	//	}
	//}

	//if (direction == 2)
	//{
	//	if (t_levelDate[row][++col] != 1)
	//	{
	//		m_velocity = { 5.0f, 0.0 };
	//	}
	//}

	//if (direction == 3)
	//{
	//	if (t_levelDate[--row][col] != 1)
	//	{
	//		m_velocity = { 0.0f, -5.0f };
	//	}
	//}

	//if (direction == 4)
	//{
	//	if (t_levelDate[++row][col] != 1)
	//	{
	//		m_velocity = { 0.0f, 5.0f };
	//	}
	//}

	//m_sprite.move(m_velocity);
}

void Player::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = 1;
		m_sprite.move(-speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = 2;
		m_sprite.move(speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = 3;
		m_sprite.move(0, -speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = 4;
		m_sprite.move(0, speed);
	}
}
