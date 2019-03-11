#include "Ghost.h"

Ghost::Ghost()
{
	setUpSprite();
}

Ghost::~Ghost()
{

}

void Ghost::setUpSprite()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/greenghost32.png"))
	{
		std::cout << "Error loading texture ";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
	m_row = 10;
	m_col = 19;
	m_sprite.setPosition(m_col * 32, m_row * 32);
}
