#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Ghost.h"
#include "Pellet.h"
#include "Player.h"
#include "Cell.h"
#include "PowerUp.h"


class Game
{
	bool m_gameExit;
	sf::RenderWindow m_window;
	int levelData[MAX_ROWS][MAX_COLS];
	Cell cellType[MAX_ROWS][MAX_COLS];
	Player player;

public:	  // declaration of member functions	
	Game(); // This is the default constructor for the game class.
	~Game(); // This is the default destructor for the game class.
	void	loadContent(); // This is the default constructor for the game class.

	void	update(sf::Time t_deltaTime); // This member function updates the game every 60th a second.
	void	run(); // This member function runs the game.
	void	render(); // This member function renders the game.
	void	processEvents(); // This member function process user created events.
	void	setUpGame();
};


#endif
