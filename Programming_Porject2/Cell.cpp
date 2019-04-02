#include "Cell.h"

Cell::Cell()
{
	setUpTexture();
}


Cell::~Cell()
{
}


void Cell::setUpSprites(int t_cellType, int t_row, int t_col)
{
	switch (t_cellType)
	{

	case 0:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture1);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 1:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture2);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 2:
		typeOfCell = TypeOfCell::Pellet;
		m_sprite.setTexture(m_pelletTexture);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;
	case 3:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture3);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 4:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture4);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 5:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture5);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 6:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture6);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;
	default:
			break;
	}
}

void Cell::setUpTexture()
{
	if (!m_pelletTexture.loadFromFile("ASSETS/IMAGES/bigpill.png"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture1.loadFromFile("ASSETS/IMAGES/wall6Right.jpg"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture2.loadFromFile("ASSETS/IMAGES/wall3Horizontal.jpg"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture3.loadFromFile("ASSETS/IMAGES/wall3Vertical.jpg"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture4.loadFromFile("ASSETS/IMAGES/wall6Up.jpg"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture5.loadFromFile("ASSETS/IMAGES/wall6Left.jpg"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture6.loadFromFile("ASSETS/IMAGES/wall6Down.jpg"))
	{
		std::cout << "Error ";
	}
}

void Cell::playerCollision(sf::Sprite t_playerSprite)
{
	if (t_playerSprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
	{
		isAlive = false;
	}
}

void Cell::setUpPelletForHelpScreen()
{
	m_sprite.setTexture(m_pelletTexture);
	m_sprite.setPosition(50, 350);
}
