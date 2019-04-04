#include "Ghost.h"

Ghost::Ghost()
{
	setUpSprite();
	randomDirection = rand() % 4 + 1;
	m_isAlive = true;
	m_speed = MAX_SPEED;
	m_velocity = NULL_VELOCITY;
	m_direction = GhostDirection::None;
	m_row = 0;
	m_col = 0;
	cooldown = 0;
	m_texture;
	m_sprite;
	cooldown = MAX_COOLDOWN_FOR_GHOST_MOVEMENT;
	ghostCooldown = 5;
}

Ghost::~Ghost()
{

}

void Ghost::setUpSprite()
{
}

void Ghost::move(Cell t_cellType[][MAX_COLS])
{

	m_col = (static_cast<int>(m_sprite.getPosition().x / 32));
	m_row = (static_cast<int>(m_sprite.getPosition().y / 32));

	if (m_direction == GhostDirection::None)
	{
		setDirection();
	}

	if (cooldown <= 0)
	{
		if (m_direction != GhostDirection::None)
		{
			m_velocity = NULL_VELOCITY;

			if (m_direction == GhostDirection::Left)
			{
				if (t_cellType[m_row][m_col - 1].getCell() != TypeOfCell::Wall)
				{
					m_velocity = { -m_speed, 0.0 };
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE, BIT_SIZE, BIT_SIZE });
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
					m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
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
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE * 3, BIT_SIZE, BIT_SIZE });
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
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE * 2, BIT_SIZE, BIT_SIZE });
					m_sprite.move(m_velocity);
				}
				else
				{
					randomDirection = (rand() % 4) + 1;
				}
			}

			m_direction = GhostDirection::None;
			cooldown = MAX_COOLDOWN_FOR_GHOST_MOVEMENT;
		}
	}
	else
	{
		cooldown--;
	}

	if (ghostCooldown <= NULL_COOLDOWN)
	{
		ghostCooldown = 5 * 40;
		randomDirection = (rand() % 4) + 1;
	}
	else
	{
		ghostCooldown--;
	}
}

void Ghost::setDirection()
{
	if (randomDirection == LEFT)
	{
		m_direction = GhostDirection::Left;
	}
	else if (randomDirection == RIGHT)
	{
		m_direction = GhostDirection::Right;
	}
	else if (randomDirection == UP)
	{
		m_direction = GhostDirection::Up;
	}
	else if (randomDirection == DOWN)
	{
		m_direction = GhostDirection::Down;
	}
}

void Ghost::setPosition(int row, int col)
{
	m_sprite.setPosition(col * BIT_SIZE, row * BIT_SIZE);
}

void Ghost::setTextureForPurpleGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/purpleghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

void Ghost::setTextureForRedGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/redghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

void Ghost::setTextureForGreenGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/greenghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

void Ghost::setTextureForBlueGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/blueghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

void Ghost::setUpPositionForGhostForHelpScreen()
{
	m_sprite.setPosition(GHOST_FOR_HELP_SCREEN_POSITION);
}

void Ghost::saveDataToFile(std::ofstream & t_outputFile)
{
	t_outputFile << m_sprite.getPosition().x << " Ghost's X position,";
	t_outputFile << std::endl;
	t_outputFile << m_sprite.getPosition().y << " Ghost's Y position,";
	t_outputFile << std::endl;
	t_outputFile << m_isAlive << " Ghost's status (Boolean),";
	t_outputFile << std::endl;
	t_outputFile << randomDirection << " Ghost's current direction,";
	t_outputFile << std::endl;
}
