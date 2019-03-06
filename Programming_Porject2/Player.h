#ifndef PLAYER
#define PLAYER

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"

class Player
{
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int m_speed;
	bool m_isAlive;
	int row;
	int col;
	int direction;
	sf::Vector2f m_velocity;
	int speed = 0;
	bool right, left, up, down;

public:
	Player();
	~Player();
	void setUpSprite();
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return row; }
	inline int getCol() { return col; }
	inline void setCol(int t_col) { col = t_col; }
	inline void setRow(int t_row) { row = t_row; }
	void move(int t_levelDate[][MAX_COLS]);
	void setDirection();
};

#endif
