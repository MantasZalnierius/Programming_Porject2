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

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 31, 35 });
	m_sprite.setPosition(400, 700);

	m_velocity = { 0.0f, 0.0f };
}

void Player::move()
{
	m_velocity = sf::Vector2f{ 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = -5.0f; // This sets the X velocity to -5.0.
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = 5.0f; // This sets the X velocity to 5.0.
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = -5.0f; // This sets the Y velocity to -5.0.
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = 5.0f; // This sets the Y velocity to 5.0.
	}

	m_sprite.move(m_velocity);
}
