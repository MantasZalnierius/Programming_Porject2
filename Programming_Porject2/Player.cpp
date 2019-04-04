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
	m_row = START_ROW_FOR_PLAYER;
	m_col = START_COL_FOR_PLAYER;
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
	m_sprite.setPosition(m_col * BIT_SIZE, m_row * BIT_SIZE);
	m_velocity = NULL_VELOCITY;
	m_speed = MAX_SPEED;
	health = MAX_HEALTH;
	
}

void Player::pelletCollision(int &t_score)
{
	t_score += 2;
}

void Player::move(Cell t_typeOfCell[][MAX_COLS], int &t_score)
{
	m_col = (static_cast<int>(m_sprite.getPosition().x / BIT_SIZE));
	m_row = (static_cast<int>(m_sprite.getPosition().y / BIT_SIZE));

	
	if (m_playerDirecrtions != Direction::None)
	{
		m_velocity = NULL_VELOCITY;

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
	
	if (t_typeOfCell[m_row][m_col].getStatus() && t_typeOfCell[m_row][m_col].getCell() == TypeOfCell::Pellet)
	{
		pelletCollision(t_score);
		t_typeOfCell[m_row][m_col].playerCollision();
	}
}

void Player::setDirection(sf::Event t_event)
{

	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames)
		{
			if (pacManFrame.top <= 215 || pacManFrame.top > 285)
			{
				pacManFrame.top = 285.0f;
			}
			else
			{
				pacManFrame.top -= BIT_SIZE_FOR_ANIMATION;
			}
		}
		m_playerDirecrtions = Direction::Left;
	}

	if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames)
		{
			if (pacManFrame.top >= 70)
			{
				pacManFrame.top = 0.0f;
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION;
			}
		}

		m_playerDirecrtions = Direction::Right;
	}

	if (t_event.key.code == sf::Keyboard::Up || t_event.key.code == sf::Keyboard::W)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames)
		{
			if (pacManFrame.top >= 390 || pacManFrame.top < 320.0f)
			{
				pacManFrame.top = 320.0f;
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION;
			}
		}
		m_playerDirecrtions = Direction::Up;
	}

	if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames)
		{
			if (pacManFrame.top >= 175 || pacManFrame.top < 105.0f)
			{
				pacManFrame.top = 105.0f;
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION;
			}
		}

		m_playerDirecrtions = Direction::Down;
	}

	m_sprite.setTextureRect(pacManFrame);
}

void Player::setUpPlayerForHelpScreen()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(PLAYER_FOR_HELP_SCREEN_POSITION);
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
	m_col = (static_cast<int>(START_COL_FOR_PLAYER));
	m_row = (static_cast<int>(START_ROW_FOR_PLAYER));
	resetPosition(m_col, m_row);
	health--;
}
