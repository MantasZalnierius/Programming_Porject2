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
	m_row = 22;
	m_col = 2;
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
	m_sprite.setPosition(m_col * 32.0f, m_row * 32.0f);
	m_velocity = { 0.0f, 0.0f };
	m_speed = 32.0f;
	
}

void Player::move(Cell t_typeOfCell[][MAX_COLS])
{
	m_velocity = { 0.0, 0.0 };

	if (m_playerDirecrtions == Direction::Left)
	{
		if (t_typeOfCell[m_row][m_col - 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { -m_speed, 0.0 };
		}
	}

	else if (m_playerDirecrtions == Direction::Right)
	{
		if (t_typeOfCell[m_row][m_col + 1].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { m_speed, 0.0 };
		}
	}

	else if (m_playerDirecrtions == Direction::Up)
	{
		if (t_typeOfCell[m_row - 1][m_col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, -m_speed };
		}
	}

	else if (m_playerDirecrtions == Direction::Down)
	{
		if (t_typeOfCell[m_row + 1][m_col].getCell() != TypeOfCell::Wall)
		{
			m_velocity = { 0.0f, m_speed };
		}
	}

	m_sprite.move(m_velocity);
}

void Player::setDirection(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		m_playerDirecrtions = Direction::Left;
	}

	if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		m_playerDirecrtions = Direction::Right;
	}

	if (t_event.key.code == sf::Keyboard::Up || t_event.key.code == sf::Keyboard::W)
	{
		m_playerDirecrtions = Direction::Up;
	}

	if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		m_playerDirecrtions = Direction::Down;
	}
}
