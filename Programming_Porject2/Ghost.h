#ifndef GHOST
#define GHOST

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"

enum class GhostDirection
{
	Left,
	Right,
	Up,
	Down,
	None

};

class Ghost
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	GhostDirection m_direction = GhostDirection::None;
	float m_speed;
	bool m_isAlive;
	int m_row;
	int m_col;
	sf::Vector2f m_velocity;

public:
	Ghost();
	~Ghost();
	void setUpSprite();
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return m_row; }
	inline int getCol() { return m_col; }
	inline void setCol(int t_col) { m_col = t_col; }
	inline void setRow(int t_row) { m_row = t_row; }

};

#endif
