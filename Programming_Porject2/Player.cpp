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
	m_sprite.setPosition(col * 32.0f, row * 32.0f);
	m_velocity = { 0.0f, 0.0f };
	speed = 32;
}

void Player::move(int t_levelDate[][MAX_COLS])
{
	if (playerDirecrtions == Direction::Left)
	{
		if (t_levelDate[row][col - 1] != 1)
		{
			speed = 32;
			m_sprite.move(-speed, 0);
		}
		else
		{
			speed = 0;
		}
	}

	else if (playerDirecrtions == Direction::Right)
	{
		if (t_levelDate[row][col + 1] != 1)
		{
			speed = 32;
			m_sprite.move(speed, 0);
		}
		else
		{
			speed = 0;
		}
	}

	else if (playerDirecrtions == Direction::Up)
	{
		if (t_levelDate[row - 1][col] != 1)
		{
			speed = 32;
			m_sprite.move(0, -speed);
		}
		else
		{
			speed = 0;
		}
	}

	if (playerDirecrtions == Direction::Down)
	{
		if (t_levelDate[row + 1][col] != 1)
		{
			speed = 32;
			m_sprite.move(0, speed);
		}
		else
		{
			speed = 0;
		}
	}
}

void Player::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerDirecrtions = Direction::Left;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerDirecrtions = Direction::Right;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerDirecrtions = Direction::Up;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerDirecrtions = Direction::Down;
	}
}
