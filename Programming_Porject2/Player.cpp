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
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
	m_sprite.setPosition(col * 32.0f, row * 32.0f);
	m_velocity = { 0.0f, 0.0f };
	speed = 32;
}

void Player::move(Cell t_typeOfCell[][MAX_COLS])
{
	m_velocity = { 0.0, 0.0 };
	if (playerDirecrtions == Direction::Left)
	{
		if (t_typeOfCell[row][col - 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { -32.0f, 0.0 };
		}
	}

	else if (playerDirecrtions == Direction::Right)
	{
		if (t_typeOfCell[row][col + 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 32.0f, 0.0 };
		}
	}

	else if (playerDirecrtions == Direction::Up)
	{
		if (t_typeOfCell[row - 1][col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, -32.0 };
		}
	}

	else if (playerDirecrtions == Direction::Down)
	{
		if (t_typeOfCell[row + 1][col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, 32.0 };
		}
	}

	m_sprite.move(m_velocity);
}

void Player::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerDirecrtions = Direction::Left;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerDirecrtions = Direction::Right;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerDirecrtions = Direction::Up;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerDirecrtions = Direction::Down;
	}
}
