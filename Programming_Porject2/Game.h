#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <string>
#include "Ghost.h"
#include "Pellet.h"
#include "Player.h"
#include "Cell.h"
#include "PowerUp.h"
#include <iostream>
#include <fstream>
#include <sstream>

enum class GameScreens
{
	EnterName,
	MainMenu,
	GamePlay,
	Help,
	YouLost,
	YouWon,
};

class Game
{
	std::string playerInput;
	std::string userInput;
	bool m_gameExit;
	int score;
	sf::RenderWindow m_window;
	Cell cellType[MAX_ROWS][MAX_COLS];
	Player player;
	Ghost ghost[4];
	Ghost helpGhost;
	Player helpPlayer;
	Cell  helpPellet;
	GameScreens gameStates = GameScreens::MainMenu;
	sf::Font font;
	sf::Text enterNameText;
	sf::Text playerScoreText;
	sf::Text playerHealthText;
	sf::Text MainMenuText;
	sf::Text helpPacmanText;
	sf::Text helpGhostText;
	sf::Text helpPelletText;
	sf::Text returnToMainMenuText;
	sf::Text youLostText;
	sf::Text youWonText;
	std::ofstream inputFile;
	int cooldown;
	int ghostRows[4]{ 2, 2, 2, 2 };
	int ghostCols[4]{ 2, 3, 4, 5 };
	//int ghostRows[4]{ 2, 10, 15, 22 };
	//int ghostCols[4]{ 2, 7, 19, 22 };

//	std::ofs


public:	  // declaration of member functions	
	Game(); // This is the default constructor for the game class.
	~Game(); // This is the default destructor for the game class.
	void	loadContent(); // This is the default constructor for the game class.

	void	update(sf::Time t_deltaTime); // This member function updates the game every 60th a second.
	void	run(); // This member function runs the game.
	void	render(); // This member function renders the game.
	void	processEvents(); // This member function process user created events.
	void	setUpGame();
	void	SetupText(sf::Text &t_text, sf::Vector2f t_position, std::string t_sentence);
	void	UserEnterText(sf::Event t_event);
	void	updateGamePlayScreen();
	void	updateMainMenuScreen();
	void    updateHelpScreen();
	void    updateYouLoseScreen();
	void    updateYouWinScreen();
	void	updatePlayer();
	void	updateGhosts();
	void	drawHelpScreen();
	void	drawGameplayScreen();
	void	drawYouWinScreen();
	void	drawYouLoseScreen();

};


#endif
