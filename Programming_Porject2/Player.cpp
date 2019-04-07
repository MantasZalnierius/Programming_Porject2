#include "Player.h"

Player::Player()
{
	setUpSprite();
}

Player::~Player()
{
}

/// <summary>
/// This function sets up the player
/// </summary>
void Player::setUpSprite()
{
	// This sets up the player.

	if (!m_texture.loadFromFile("ASSETS/IMAGES/mspacman32.png")) std::cout << "Error ";

	m_row = START_ROW_FOR_PLAYER;
	m_col = START_COL_FOR_PLAYER;
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, BIT_SIZE, BIT_SIZE });
	m_sprite.setPosition(static_cast<float>(m_col * BIT_SIZE), static_cast<float>(m_row * BIT_SIZE));
	m_velocity = NULL_VELOCITY;
	m_speed = MAX_SPEED;
	health = MAX_HEALTH;
	cooldown = MAX_COOLDOWN_FOR_MOVEMENT;

	if (!eattingSoundBuffer.loadFromFile("ASSETS/SOUND/pacman_chomp.wav")) std::cout << "Error loading the sound file. ";
	eattingSound.setBuffer(eattingSoundBuffer);
	eattingSound.setVolume(VOLUME_NUMBER);

	if (!hittingGhostSoundBuffer.loadFromFile("ASSETS/SOUND/pacman_death.wav")) std::cout << "Error loading the sound file. ";
	hittingGhostSound.setBuffer(hittingGhostSoundBuffer);
	hittingGhostSound.setVolume(VOLUME_NUMBER);

	// This sets up the player.
}

/// <summary>
/// This function does the collision between the player and the pellet.
/// </summary>
/// <param name="t_score"></param>
void Player::pelletCollision(int &t_score)
{
	t_score += SCORE_INCREMENT;
}

/// <summary>
/// This function handles the movement of the player,
/// it moves the player in the direction they are facing/going at.
/// </summary>
/// <param name="t_typeOfCell"></param>
/// <param name="t_score"></param>
void Player::move(Cell t_typeOfCell[][MAX_COLS], int &t_score)
{
	// Updates the row and col of the player.

	m_col = (static_cast<int>(m_sprite.getPosition().x / BIT_SIZE));
	m_row = (static_cast<int>(m_sprite.getPosition().y / BIT_SIZE));

	// Updates the row and col of the player.


	// This moves the player in the direction he wants to go into.

	if (cooldown <= NULL_COOLDOWN)
	{
		if (m_playerDirecrtions != Direction::None)
		{
			m_velocity = NULL_VELOCITY;

			if (m_playerDirecrtions == Direction::Left)
			{
				if (t_typeOfCell[m_row][m_col - 1].getCell() != TypeOfCell::Wall) // This checks if there is a wall in the leftmost col.
				{
					m_velocity = { -m_speed, 0.0 }; // If there ins't wall, the player can move, else they can't.
				}
			}

			else if (m_playerDirecrtions == Direction::Right)
			{
				if (t_typeOfCell[m_row][m_col + 1].getCell() != TypeOfCell::Wall) // This checks if there is a wall in the rightmost col.
				{
					m_velocity = { m_speed, 0.0 }; // If there ins't wall, the player can move, else they can't.
				}
			}

			else if (m_playerDirecrtions == Direction::Up)
			{
				if (t_typeOfCell[m_row - 1][m_col].getCell() != TypeOfCell::Wall) // This checks if there is a wall in the upawards row.
				{
					m_velocity = { 0.0f, -m_speed }; // If there ins't wall, the player can move, else they can't.
				}
			}

			else if (m_playerDirecrtions == Direction::Down)
			{
				if (t_typeOfCell[m_row + 1][m_col].getCell() != TypeOfCell::Wall) // This checks if there is a wall in the downwards row.
				{
					m_velocity = { 0.0f, m_speed }; // If there ins't wall, the player can move, else they can't.
				}
			}

			m_sprite.move(m_velocity);
			m_playerDirecrtions = Direction::None;
			cooldown = MAX_COOLDOWN_FOR_MOVEMENT;
		}
	}
	else
	{
		cooldown -= 2;
	}
	
	// This moves the player in the direction he wants to go into.

	// This checks for collision between the pellets and the player.
	
	if (t_typeOfCell[m_row][m_col].getStatus() && t_typeOfCell[m_row][m_col].getCell() == TypeOfCell::Pellet) // If a player is in the row and col of a pellet.
	{
		// Do collisions, else don't

		pelletCollision(t_score);
		t_typeOfCell[m_row][m_col].playerCollision();
		eattingSound.play();

		// Do collisions, else don't
	}

	// This checks for collision between the pellets and the player.

}

/// <summary>
/// This function sets the direction of the player that the user wants to go in.
/// </summary>
/// <param name="t_event"></param>
void Player::setDirection(sf::Event t_event)
{
	// This sets the direction the player wants to go in, and changes the animation on the player.

	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames) // If total time is greater than the time between frames (0.2f) seconds.
		{
			if (pacManFrame.top <= 215 || pacManFrame.top > 285) // If it's not in the correct animation.
			{
				pacManFrame.top = 285; // Then make change to make it correct.
			}
			else
			{
				pacManFrame.top -= BIT_SIZE_FOR_ANIMATION; // else update the animation.
			}
		}
		m_playerDirecrtions = Direction::Left;
	}

	if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames) // If total time is greater than the time between frames (0.2f) seconds.
		{
			if (pacManFrame.top >= 70) // If it's not in the correct animation.
			{
				pacManFrame.top = 0; // Then make change to make it correct.
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION; // else update the animation.
			}
		}

		m_playerDirecrtions = Direction::Right;
	}

	if (t_event.key.code == sf::Keyboard::Up || t_event.key.code == sf::Keyboard::W)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames) // If total time is greater than the time between frames (0.2f) seconds.
		{
			if (pacManFrame.top >= 390 || pacManFrame.top < 320.0f) // If it's not in the correct animation.
			{
				pacManFrame.top = 320; // Then make change to make it correct.
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION; // else update the animation.
			}
		}
		m_playerDirecrtions = Direction::Up;
	}

	if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		if (TimeClock.getElapsedTime() >= timeBetweenFrames) // If total time is greater than the time between frames (0.2f) seconds.
		{
			if (pacManFrame.top >= 175 || pacManFrame.top < 105.0f) // If it's not in the correct animation.
			{
				pacManFrame.top = 105; // Then make change to make it correct.
			}
			else
			{
				pacManFrame.top += BIT_SIZE_FOR_ANIMATION; // else update the animation.
			}
		}

		m_playerDirecrtions = Direction::Down;
	}

	m_sprite.setTextureRect(pacManFrame);

	// This sets the direction the player wants to go in, and changes the animation on the player.
}

/// <summary>
/// This function sets the player for the help screen.
/// </summary>
void Player::setUpPlayerForHelpScreen()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(PLAYER_FOR_HELP_SCREEN_POSITION);
}

/// <summary>
/// This function saves all the data related to the player to a .txt file.
/// </summary>
/// <param name="t_outputFile"></param>
void Player::saveDataToFile(std::ofstream & t_outputFile)
{
	// Saves everything related with the player. 

	t_outputFile << m_sprite.getPosition().x << " Pacman's X position,";
	t_outputFile << std::endl;
	t_outputFile << m_sprite.getPosition().y << " Pacman's Y position,";
	t_outputFile << std::endl;
	t_outputFile << health << " Pacman's current health,";
	t_outputFile << std::endl;
	t_outputFile << m_speed << " Pacman's current movement speed,";

	// Saves everything related with the player. 
}

/// <summary>
/// This function handles the ghost collision.
/// </summary>
void Player::ghostCollisions()
{
	// This does the collision between the ghost and the player.

	m_col = (static_cast<int>(START_COL_FOR_PLAYER)); // Move the player back to it's start col.
	m_row = (static_cast<int>(START_ROW_FOR_PLAYER)); // Move the player back to it's start row.
	resetPosition(m_col, m_row); 
	health--;
	hittingGhostSound.play();

	// This does the collision between the ghost and the player.
}
