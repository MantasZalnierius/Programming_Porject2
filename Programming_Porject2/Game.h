#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <string>
#include "Ghost.h"
#include "Player.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <sstream>

enum class GameScreens // Enum class for all the gamescreens in the game.
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
	// Member variables

	std::string playerInput;
	std::string userInput; // Stores the user names for the game.

	bool m_gameExit; // controls if the game is turned off.

	int score; // Stores the current score of the player
	int highestScore; // Stores the highest score the player has achived.
	int ghostRows[MAX_GHOSTS]{ 2, 10, 15, 22 }; // This is the starting Y position of all the ghosts.
	int ghostCols[MAX_GHOSTS]{ 2, 7, 19, 22 }; // This is the starting X position of all the ghosts.


	sf::RenderWindow m_window;
	
	// Intiate all the objects in the game. 
	Cell cellType[MAX_ROWS][MAX_COLS];
	Player player;
	Ghost ghost[MAX_GHOSTS];
	Ghost helpGhost;
	Player helpPlayer;
	Cell  helpPellet;
	// Intiate all the objects in the game. 

	GameScreens gameStates = GameScreens::MainMenu;

	sf::Font font;
	sf::Text enterNameText;
	sf::Text playerScoreTextGameplay;
	sf::Text playerScoreTextGameOver;
	sf::Text playerHealthText;
	sf::Text MainMenuText;
	sf::Text helpPacmanText;
	sf::Text helpGhostText;
	sf::Text helpPelletText;
	sf::Text returnToMainMenuText;
	sf::Text youLostText;
	sf::Text youWonText;
	sf::Text highestScoreText;

	std::ofstream saveData; 

	sf::Music backgroundMusic;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	// Member variables

public:
	// Member functions

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

	// Member functions

};


#endif
