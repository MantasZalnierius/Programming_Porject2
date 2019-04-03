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
	m_sprite.setTextureRect(sf::IntRect{ 1, 32, 32, 32 });
	m_sprite.setPosition(m_col * 32.0f, m_row * 32.0f);
	m_velocity = { 0.0f, 0.0f };
	m_speed = 32.0f;
	health = 3;
	
}

void Player::pelletCollision(sf::Sprite t_pellet, int &t_score)
{
	if (t_pellet.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
	{
		t_score += 2;
	}
}

void Player::move(Cell t_typeOfCell[][MAX_COLS])
{
	m_col = (static_cast<int>(m_sprite.getPosition().x / 32));
	m_row = (static_cast<int>(m_sprite.getPosition().y / 32));

	
	if (m_playerDirecrtions != Direction::None)
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

		m_playerDirecrtions = Direction::None;
	}
	
}

void Player::setDirection(sf::Event t_event)
{
	m_sprite.setTextureRect(pacManFrame);

	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		if (TimeClock.getElapsedTime() >= tv)
		{
			pacManFrame.top = 0.0f;
		}
		else
		{
			pacManFrame.top += 32.0f;
		}
		m_playerDirecrtions = Direction::Left;
	}

	if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		if (TimeClock.getElapsedTime() >= tv)
		{
			if(pacManFrame.top >  m_texture.getSize().y / 12)
			{ 
				pacManFrame.top = 0.0f;
			}
			else
			{
				pacManFrame.top += m_texture.getSize().y / 12;
			}
		}
		
		m_playerDirecrtions = Direction::Right;
	}

	if (t_event.key.code == sf::Keyboard::Up || t_event.key.code == sf::Keyboard::W)
	{
		m_playerDirecrtions = Direction::Up;
		m_sprite.setTextureRect(sf::IntRect{ 0, 395, 35, 35 });
	}

	if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		m_playerDirecrtions = Direction::Down;
		m_sprite.setTextureRect(sf::IntRect{ 0, 140, 35, 35});
	}
}

void Player::setUpPlayerForHelpScreen()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(50, 600);
}

void Player::saveDataToFile(std::ofstream & t_outputFile)
{
	t_outputFile << m_sprite.getPosition().x << " Pacman's X position,";
	t_outputFile << std::endl;
	t_outputFile << m_sprite.getPosition().y << " Pacman's Y position,";
	t_outputFile << std::endl;
	t_outputFile << health << " Pacman's current health,";
	t_outputFile << std::endl;
	t_outputFile << m_speed << " Pacman's current movement speed,";
}

void Player::playerCollisions()
{
	m_col = (static_cast<int>(2));
	m_row = (static_cast<int>(22));
	resetPosition(2, 22);
	health--;
}
