#include "Ghost.h"

Ghost::Ghost()
{
	setUpSprite();
}

Ghost::~Ghost()
{

}

/// <summary>
/// This function sets up every ghost for the game.
/// </summary>
void Ghost::setUpSprite()
{
	// sets up every ghost.

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
	cooldown = MAX_COOLDOWN_FOR_MOVEMENT;
	ghostCooldown = 5;

	// sets up every ghost.
}

/// <summary>
/// This function moves the ghost in the direction they are going in.
/// </summary>
/// <param name="t_cellType"></param>
void Ghost::move(Cell t_cellType[][MAX_COLS])
{
	// Update the row and col of each ghost.
	m_col = (static_cast<int>(m_sprite.getPosition().x / 32));
	m_row = (static_cast<int>(m_sprite.getPosition().y / 32));

	if (m_direction == GhostDirection::None) setDirection();

	// Move a ghost in the direction they are going in.

	if (cooldown <= NULL_COOLDOWN)
	{
		if (m_direction != GhostDirection::None)
		{
			m_velocity = NULL_VELOCITY;

			if (m_direction == GhostDirection::Left)
			{
				if (t_cellType[m_row][m_col - 1].getCell() != TypeOfCell::Wall) // checks if there is no wall in the next leftmost col.
				{
					m_velocity = { -m_speed, 0.0 };
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE, BIT_SIZE, BIT_SIZE });
					m_sprite.move(m_velocity); // If there ins't wall, the ghost can move, else they can't.
				}
				else
				{
					randomDirection = (rand() % 4) + 1; // If there is wall choose a random direction instead.
				}
			}

			else if (m_direction == GhostDirection::Right)
			{
				if (t_cellType[m_row][m_col + 1].getCell() != TypeOfCell::Wall) // checks if there is no wall in the next rightnmost col.
				{
					m_velocity = { m_speed, 0.0 };
					m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
					m_sprite.move(m_velocity); // If there ins't wall, the ghost can move, else they can't.
				}
				else
				{
					randomDirection = (rand() % 4) + 1; // If there is wall choose a random direction instead.
				}
			}

			else if (m_direction == GhostDirection::Up)
			{
				if (t_cellType[m_row - 1][m_col].getCell() != TypeOfCell::Wall) // checks if there is no wall in the next upwards row.
				{
					m_velocity = { 0.0f, -m_speed };
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE * 3, BIT_SIZE, BIT_SIZE });
					m_sprite.move(m_velocity); // If there ins't wall, the ghost can move, else they can't.
				}
				else
				{
					randomDirection = (rand() % 4) + 1; // If there is wall choose a random direction instead.
				}
			}

			else if (m_direction == GhostDirection::Down)
			{
				if (t_cellType[m_row + 1][m_col].getCell() != TypeOfCell::Wall) // checks if there is no wall in the next downwards row.
				{
					m_velocity = { 0.0f, m_speed };
					m_sprite.setTextureRect(sf::IntRect{ 0, BIT_SIZE * 2, BIT_SIZE, BIT_SIZE });
					m_sprite.move(m_velocity); // If there ins't wall, the ghost can move, else they can't.
				}
				else
				{
					randomDirection = (rand() % 4) + 1; // If there is wall choose a random direction instead.
				}
			}

			m_direction = GhostDirection::None;
			cooldown = MAX_COOLDOWN_FOR_MOVEMENT;
		}
	}
	else
	{
		cooldown--;
	}

	// Move a ghost in the direction they are going in.


	// This will make the ghost choose a random direction while they are moving.

	if (ghostCooldown <= NULL_COOLDOWN) 
	{
		ghostCooldown = 5 * 40;
		randomDirection = (rand() % 4) + 1;
	}
	else
	{
		ghostCooldown--;
	}

	// This will make the ghost choose a random direction while they are moving.
}

/// <summary>
/// This function sets the direction the ghosts want to go in.
/// </summary>
void Ghost::setDirection()
{
	// This sets the direction of the ghosts.

	if (randomDirection == LEFT) m_direction = GhostDirection::Left;
	else if (randomDirection == RIGHT) m_direction = GhostDirection::Right;
	else if (randomDirection == UP) m_direction = GhostDirection::Up;
	else if (randomDirection == DOWN) m_direction = GhostDirection::Down;

	// This sets the direction of the ghosts.
}

/// <summary>
/// This sets the position of the ghosts to thier starting position.
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
void Ghost::setPosition(int row, int col)
{
	m_sprite.setPosition(static_cast<float>(col * BIT_SIZE), static_cast<float>(row * BIT_SIZE));
}

/// <summary>
/// This function sets the texture for the purple ghost.
/// </summary>
void Ghost::setTextureForPurpleGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/purpleghost32.png")) std::cout << "Error loading texture ";

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

/// <summary>
/// This function sets the texture for the red ghost.
/// </summary>
void Ghost::setTextureForRedGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/redghost32.png")) std::cout << "Error loading texture ";

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

/// <summary>
/// This function sets the texture for the green ghost.
/// </summary>
void Ghost::setTextureForGreenGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/greenghost32.png")) std::cout << "Error loading texture ";

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

/// <summary>
/// This function sets the texture for the blue ghost.
/// </summary>
void Ghost::setTextureForBlueGhost()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/blueghost32.png")) std::cout << "Error loading texture ";

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
}

/// <summary>
/// This function sets the position of a ghost for the help screen.
/// </summary>
void Ghost::setUpPositionForGhostForHelpScreen()
{
	m_sprite.setPosition(GHOST_FOR_HELP_SCREEN_POSITION);
}

/// <summary>
/// This function saves everything related to the ghosts to a .txt file.
/// </summary>
/// <param name="t_outputFile"></param>
void Ghost::saveDataToFile(std::ofstream & t_outputFile)
{
	// Saves all the data that the ghost has. 

	t_outputFile << m_sprite.getPosition().x << " Ghost's X position,";
	t_outputFile << std::endl;
	t_outputFile << m_sprite.getPosition().y << " Ghost's Y position,";
	t_outputFile << std::endl;
	t_outputFile << m_isAlive << " Ghost's status (Boolean),";
	t_outputFile << std::endl;
	t_outputFile << randomDirection << " Ghost's current direction,";
	t_outputFile << std::endl;

	// Saves all the data that the ghost has. 
}
