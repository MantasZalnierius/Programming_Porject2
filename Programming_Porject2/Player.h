#ifndef PLAYER
#define PLAYER

#include <SFML\Graphics.hpp>
#include <iostream>

class Player
{
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int m_speed;
	bool m_isAlive;
	sf::Vector2f m_velocity;

public:
	 Player();
	 ~Player();
void setUpSprite();
inline sf::Sprite getBody() { return m_sprite; }
void move();
};

#endif
