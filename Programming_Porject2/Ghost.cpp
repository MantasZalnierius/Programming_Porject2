#include "Ghost.h"

Ghost::Ghost()
{
	setUpSprite();
	randomDirection = rand() % 4 + 1;
	m_isAlive = true;
	m_speed = 32;
	m_velocity = { 0.0, 0.0 };
	m_direction = GhostDirection::Left;
	m_row = 0;
	m_col = 0;
	cooldown = 0;
	m_texture;
	m_sprite;
	cooldown = 15;
	ghostCooldown = 5;
}

Ghost::~Ghost()
{

}

void Ghost::setUpSprite()
{
}

void Ghost::move(Cell t_cellType[][MAX_COLS], int t_rows, int t_cols)
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
			m_velocity = { 0.0, 0.0 };

			if (m_direction == GhostDirection::Left)
			{
				if (t_cellType[m_row][m_col - 1].getCell() != TypeOfCell::Wall || !m_row == t_rows && m_col == t_cols - 1)
				{
					m_velocity = { -m_speed, 0.0 };
					m_sprite.setTextureRect(sf::IntRect{ 0, 32, 32, 32 });
					m_sprite.move(m_velocity);
				}
				else
				{
					randomDirection = (rand() % 4) + 1;
				}
			}

			else if (m_direction == GhostDirection::Right)
			{
				if (t_cellType[m_row][m_col + 1].getCell() != TypeOfCell::Wall || !m_row == t_rows && m_col == t_cols + 1)
				{
					m_velocity = { m_speed, 0.0 };
					m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
					m_sprite.move(m_velocity);
				}
				else
				{
					randomDirection = (rand() % 4) + 1;
				}
			}

			else if (m_direction == GhostDirection::Up)
			{
				if (t_cellType[m_row - 1][m_col].getCell() != TypeOfCell::Wall || !m_row == t_rows - 1 && m_col == t_cols)
				{
					m_velocity = { 0.0f, -m_speed };
					m_sprite.setTextureRect(sf::IntRect{ 0, 96, 32, 32 });
					m_sprite.move(m_velocity);
				}
				else
				{
					randomDirection = (rand() % 4) + 1;
				}
			}

			else if (m_direction == GhostDirection::Down)
			{
				if (t_cellType[m_row + 1][m_col].getCell() != TypeOfCell::Wall || !m_row == t_rows + 1 && m_col == t_cols)
				{
					m_velocity = { 0.0f, m_speed };
					m_sprite.setTextureRect(sf::IntRect{ 0, 64, 32, 32 });
					m_sprite.move(m_velocity);
				}
				else
				{
					randomDirection = (rand() % 4) + 1;
				}
			}

			m_direction = GhostDirection::None;
			cooldown = 15;
		}
	}
	else
	{
		cooldown--;
	}

	if (ghostCooldown <= 0)
	{
		ghostCooldown = 5 * 60;
		randomDirection = (rand() % 4) + 1;
	}
	else
	{
		ghostCooldown--;
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

void Ghost::setPosition(int row, int col)
{
	m_sprite.setPosition(col * 32, row * 32);
}

void Ghost::setTextureForPurpleGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/purpleghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void Ghost::setTextureForRedGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/redghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void Ghost::setTextureForGreenGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/greenghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void Ghost::setTextureForBlueGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/blueghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void Ghost::setUpPositionForGhostForHelpScreen()
{
	m_sprite.setPosition(50, 100);
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
