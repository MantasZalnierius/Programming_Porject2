#ifndef GHOST
#define GHOST

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"

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
	GhostDirection m_direction = GhostDirection::Left;
	float m_speed;
	bool m_isAlive;
	int m_row;
	int m_col;
	int randomDirection;
	sf::Vector2f m_velocity;

public:
	Ghost();
	~Ghost();
	void setUpSprite();
	void move(Cell t_cellType[][MAX_COLS]);
	void setDirection();
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return m_row; }
	inline int getCol() { return m_col; }
	inline void setCol(int t_col) { m_col = t_col; }
	inline void setRow(int t_row) { m_row = t_row; }
	inline void sets(GhostDirection t_playerDirection) { m_direction = t_playerDirection; }
	inline GhostDirection getDirection() { return m_direction; }

};

#endif
