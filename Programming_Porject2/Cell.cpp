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
		typeOfCell = TypeOfCell::None;
		m_sprite.setTexture(m_emptyCellTexture);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 1:
		typeOfCell = TypeOfCell::Wall;
		m_sprite.setTexture(m_wallTexture);
		m_sprite.setPosition(sf::Vector2f{ static_cast<float>(t_col * 32.0f), static_cast<float>(t_row * 32.0f) });
		isAlive = true;
		break;

	case 2:
		typeOfCell = TypeOfCell::Pellet;
		m_sprite.setTexture(m_pelletTexture);
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

	if (!m_emptyCellTexture.loadFromFile("ASSETS/IMAGES/emptyCell.png"))
	{
		std::cout << "Error ";
	}

	if (!m_wallTexture.loadFromFile("ASSETS/IMAGES/wallCell.jpg"))
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


void Cell::draw(sf::RenderWindow &t_window, int t_CellType)
{
	if (t_CellType == 0)
	{
		t_window.draw(m_sprite);
	}

	if (t_CellType == 1)
	{
		t_window.draw(m_sprite);
	}

	if (t_CellType == 2)
	{
		t_window.draw(m_sprite);
	}
}