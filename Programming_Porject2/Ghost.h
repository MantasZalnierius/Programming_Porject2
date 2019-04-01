#ifndef GHOST
#define GHOST

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"
#include <iostream>
#include <fstream>


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
	GhostDirection m_direction;
	float m_speed;
	bool m_isAlive;
	int m_row;
	int m_col;
	int randomDirection;
	sf::Vector2f m_velocity;
	int cooldown;
	int ghostCooldown;
	std::ofstream inputFile;

public:
	Ghost();
	~Ghost();
	void setUpSprite();
	void move(Cell t_cellType[][MAX_COLS], int t_rows, int t_cols);
	void setDirection();
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return m_row; }
	inline int getCol() { return m_col; }
	inline void setCol(int t_col) { m_col = t_col; }
	inline void setRow(int t_row) { m_row = t_row; }
	inline void sets(GhostDirection t_playerDirection) { m_direction = t_playerDirection; }
	inline GhostDirection getDirection() { return m_direction; }
	void setPosition(int row, int col);
	inline void setCooldown(int t_cooldown) { cooldown = t_cooldown; }
	inline int getCooldown() { return cooldown; }
	void setTextureForPurpleGhost();
	void setTextureForRedGhost();
	void setTextureForGreenGhost();
	void setTextureForBlueGhost();
	inline void setdir(int t_num) { randomDirection = t_num; }
	inline int getdir() { return randomDirection; }
	void setUpPositionForGhostForHelpScreen();
	void saveDataToFile(std::ofstream &t_outputFile);
};

#endif
