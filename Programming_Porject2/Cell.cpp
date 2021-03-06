#include "Cell.h"

Cell::Cell()
{
	setUpTexture();
}


Cell::~Cell()
{
}

/// <summary>
/// This functions sets up all the objects in the cellType array, by 
/// setting the texture and position of each object.
/// </summary>
/// <param name="t_cellType"></param>
/// <param name="t_row"></param>
/// <param name="t_col"></param>
void Cell::setUpSprites(int t_cellType, int t_row, int t_col)
{
	switch (t_cellType)
	{

	case 0: // This sets the a wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture1);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) } );
		isAlive = true;
		break;

	case 1: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture2);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) } );
		isAlive = true;
		break;

	case 2:
		typeOfCell = TypeOfCell::Pellet;
		m_sprite.setTexture(m_pelletTexture);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) } );
		isAlive = true;
		break;
	case 3: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture3);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) } );
		isAlive = true;
		break;

	case 4: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture4);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) });
		isAlive = true;
		break;

	case 5: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture5);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) });
		isAlive = true;
		break;

	case 6: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture6);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) });
		isAlive = true;
		break;

	case 7: // This sets the a different wall texture in the game.
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture7);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * BIT_SIZE), static_cast<float>(t_row * BIT_SIZE) });
		isAlive = true;
		break;

	default:
			break;
	}
}

/// <summary>
/// This function loads all the textures that are needed for the cellType array.
/// </summary>
void Cell::setUpTexture()
{
	// These load all the different textures needed for the wall and pellet.

	if (!m_pelletTexture.loadFromFile("ASSETS/IMAGES/smallpill.png")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture1.loadFromFile("ASSETS/IMAGES/wall6Right.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture2.loadFromFile("ASSETS/IMAGES/wall3Horizontal.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture3.loadFromFile("ASSETS/IMAGES/wall3Vertical.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture4.loadFromFile("ASSETS/IMAGES/wall6Up.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture5.loadFromFile("ASSETS/IMAGES/wall6Left.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture6.loadFromFile("ASSETS/IMAGES/wall6Down.jpg")) std::cout << "Error in loading a texture ";
	if (!m_wallTexture7.loadFromFile("ASSETS/IMAGES/wallCell.jpg")) std::cout << "Error in loading a texture ";

	// These load all the different textures needed for the wall and pellet.
}

/// <summary>
/// This function handles player collision between the player and the pellet. 
/// </summary>
void Cell::playerCollision()
{
	isAlive = false;
}

/// <summary>
/// This sets up the pellet for the help screen.
/// </summary>
void Cell::setUpPelletForHelpScreen()
{
	m_sprite.setTexture(m_pelletTexture);
	m_sprite.setPosition(PELLET_FOR_HELP_SCREEN_POSITION);
}
