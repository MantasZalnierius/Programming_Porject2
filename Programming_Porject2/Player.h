#ifndef PLAYER
#define PLAYER

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"
#include <iostream>
#include <fstream>

enum class  Direction // Enum class for the directions for the player.
{
	Up,
	Down,
	Left,
	Right,
	None
};

class Player
{
	// Member Variables 

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Direction m_playerDirecrtions = Direction::None;
	float m_speed;
	bool m_isAlive;
	sf::Vector2f m_velocity;
	int health;
	int cooldown;
	int m_row;
	int m_col;
	sf::Time timeBetweenFrames = sf::seconds(0.25f); // Controls how fast the animation is for pacman.
	sf::Clock TimeClock;
	sf::IntRect pacManFrame = sf::IntRect{0, 0,  BIT_SIZE_FOR_ANIMATION -2 ,  BIT_SIZE_FOR_ANIMATION - 2 }; // This is the starting frame for pacman
	sf::Sound eattingSound;
	sf::SoundBuffer eattingSoundBuffer;
	sf::Sound hittingGhostSound;
	sf::SoundBuffer hittingGhostSoundBuffer;

	// Member Variables


public:
	// Member Functions

	Player();
	~Player();
	void setUpSprite();
	void pelletCollision(int &t_score);
	inline sf::Sprite getBody() { return m_sprite; }
	inline int getRow() { return m_row; }
	inline int getCol() { return m_col; }
	inline void setCol(int t_col) { m_col = t_col; }
	inline void setRow(int t_row) { m_row = t_row; }
	void move(Cell t_typeOfCell[][MAX_COLS], int &t_score);
	inline Direction getDirection() { return m_playerDirecrtions; }
	void setDirection(sf::Event t_event);
	inline void sets(Direction t_playerDirection) { m_playerDirecrtions = t_playerDirection; }
	inline void resetPosition(int t_col, int t_row) { m_sprite.setPosition(sf::Vector2f{ t_col * 32.0f, t_row * 32.0f }); }
	inline void setHealth(int t_healthDamage) { health -= t_healthDamage; }
	inline int getHealth() { return health; }
	void setUpPlayerForHelpScreen();
	void saveDataToFile(std::ofstream &t_outputFile);
	void ghostCollisions();

	// Member Functions
};

#endif
