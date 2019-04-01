#ifndef PLAYER
#define PLAYER

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"
#include <iostream>
#include <fstream>

enum class  Direction
{
	Up,
	Down,
	Left,
	Right,
	None
};

class Player
{
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Direction m_playerDirecrtions = Direction::None;
	float m_speed;
	bool m_isAlive;
	int m_row;
	int m_col;
	sf::Vector2f m_velocity;
	int health;
	std::ofstream inputFile;



public:
	Player();
	~Player();
	void setUpSprite();
	void pelletCollision(sf::Sprite t_pellet, int &t_score);
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return m_row; }
	inline int getCol() { return m_col; }
	inline void setCol(int t_col) { m_col = t_col; }
	inline void setRow(int t_row) { m_row = t_row; }
	void move(Cell t_typeOfCell[][MAX_COLS]);
	inline Direction getDirection() { return m_playerDirecrtions; }
	void setDirection(sf::Event t_event);
	inline void sets(Direction t_playerDirection) { m_playerDirecrtions = t_playerDirection; }
	inline void resetPosition(int t_col, int t_row) { m_sprite.setPosition(sf::Vector2f{ t_col * 32.0f, t_row * 32.0f }); }
	inline void setHealth(int t_healthDamage) { health -= t_healthDamage; }
	inline int getHealth() { return health; }
	void setUpPlayerForHelpScreen();
	void saveDataToFile(std::ofstream &t_outputFile);
	void collisions();
};

#endif
