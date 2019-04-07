/// <summary>
/// @author = Mantas Zalnierius
/// @date = 7th of April 2019
/// 
/// Time Taken: 33 hours
/// 
/// Description: This is a 2d pacman game, where you will be able to move either down, left, right or up. Your goal of the is to get all the pellets
/// before you lose all of your health by the ghosts.
/// Known bugs: The ghosts can still walk into each other, I've spent some time, on trying to make it work. but I didn't have the time to do so.
/// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif
// This adds all the SFML libaries.


#include "Game.h"


int main()
{
	srand(static_cast<unsigned int>(time(NULL))); // This is the random seed.
	Game game; // This makes an instance of the game class.
	game.loadContent();
	game.run();
	return 0;
}


Game::Game() : m_window(sf::VideoMode(static_cast<int>(800), static_cast<int>(800)), "Joint Project Game", sf::Style::Default),
m_gameExit{ false }
// Default constructor
{
	// This sets up the game.
	setUpGame();

	if (!backgroundMusic.openFromFile("ASSETS/SOUND/pacman_beginning.wav")) std::cout << "Error opening a sound file. ";
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(VOLUME_NUMBER);
	backgroundMusic.play();

	if (!backgroundTexture.loadFromFile("ASSETS/IMAGES/rsz_wallpaper-ms-pacman-screen-game-1280x800.jpg")) std::cout << "Error loading a texture ";
	backgroundSprite.setTexture(backgroundTexture);
}
/// <summary>
/// This function loads the game data from a .txt file and sets up the level using that data.
/// </summary>
void Game::setUpGame()
{
	// This sets up the level, by loading a .txt file.

	int setUpArray[MAX_ROWS][MAX_COLS]{};

	std::string line = "";
	std::string item = "";
	int row{}, col{};
	bool dataOK = true;
	std::ifstream myfile("ASSETS/SAVE_DATA/LevelData.txt");

	if (myfile.is_open())
	{

			row = 0;
			while (std::getline(myfile, line) && dataOK)
			{
				std::stringstream line_ss(line);
				col = 0;
				while (std::getline(line_ss, item, ',') && dataOK) // Looks at each line and sees what's between all the commas.
				{
					if (item == "0") setUpArray[row][col] = 0;
					if (item == "1") setUpArray[row][col] = 1;
					if (item == "2") setUpArray[row][col] = 2;
					if (item == "3") setUpArray[row][col] = 3;
					if (item == "4") setUpArray[row][col] = 4;
					if (item == "5") setUpArray[row][col] = 5;
					if (item == "6") setUpArray[row][col] = 6;
					if (item == "7") setUpArray[row][col] = 7;

					cellType[row][col].setUpSprites(setUpArray[row][col], row, col);

					col++;
					if (col > MAX_COLS)
					{
						std::cout << "too many cols" << "\n";
						dataOK = false;
					}
				}
				row++;
				if (row > MAX_ROWS)
				{
					std::cout << "too many rows" << "\n";
					dataOK = false;
				}
			}
	}
	else
	{
		std::cout << "can't open the level file" << "\n";
	}

	score = 0;
	highestScore = score;
}

/// <summary>
/// This function sets up all the text that is needed for the game.
/// </summary>
void Game::loadContent()
{
	// This sets all the text and font for the game 

	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf")) std::cout << "Error ";

	playerInput = "Enter your name: ";
	userInput = "";

	SetupText(enterNameText, sf::Vector2f(250.0f, 370.0f), playerInput);
	SetupText(playerScoreTextGameplay, sf::Vector2f(20.0f, 750.0f), (userInput + " Score: " + std::to_string(score)));
	SetupText(playerScoreTextGameOver, sf::Vector2f(300.0f, 400.0f), (userInput + " Score: " + std::to_string(score)));
	SetupText(highestScoreText, sf::Vector2f(300.0f, 450.0f), (userInput + " highest score: " + std::to_string(highestScore)));
	SetupText(playerHealthText, sf::Vector2f(550.0f, 750.0f), (userInput + " Health: " + std::to_string(player.getHealth())));
	SetupText(MainMenuText, sf::Vector2f(350.0f, 300.0f), "(1) New Game \n\n (2) Controls \n\n (3) Exit ");
	SetupText(helpGhostText, sf::Vector2f(100.0f, 100.0f), "These are ghosts, they are your eneimes. \n Stay away from them and you'll be fine \n they will navigate through the level looking for you.");
	SetupText(helpPacmanText, sf::Vector2f(100.0f, 600.0f), "You are Pacman, You can move using the arrow or the WASD keys\n your goal is to get every single pellet before the ghosts kill you. \n When a ghost collides with you, you lose 1 live. \n You only have three lives in the game.");
	SetupText(helpPelletText, sf::Vector2f(100.0f, 350.0f), "These are pellets \n when you eat one of these pellets you will get 2 two points.\n Your goal is to get all of these pellets. ");
	SetupText(returnToMainMenuText, sf::Vector2f(230.0f, 750.0f), "Press 4 to go back to the main menu ");
	SetupText(youLostText, sf::Vector2f(300.0f, 350.0f), "You Lost The Game ");
	SetupText(youWonText, sf::Vector2f(300.0f, 350.0f), "You Won The Game ");

	// This sets all the text and font for the game 
}

/// <summary>
/// This sets up text one by one, by passing the sf::text(by reference) and the position and the exact string
/// assoicated with that sf::text.
/// </summary>
/// <param name="t_text"></param>
/// <param name="t_position"></param>
/// <param name="t_sentence"></param>
void Game::SetupText(sf::Text &t_text, sf::Vector2f t_position, std::string t_sentence)
{
	t_text.setFont(font);  // set the font for the text
	t_text.setCharacterSize(MAX_CHARACTER_SIZE); // set the text size
	t_text.setFillColor(WHITE); // set the text colour
	t_text.setPosition(t_position);  // its position on the screen
	t_text.setString(t_sentence); // This sets the string to the text.
}


Game::~Game()
{
}

/// <summary>
/// This function runs the game, until it's closed.
/// </summary>
void Game::run()
{
	sf::Clock clock; // This initialize's the Clock object into memory.
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // This lets the Time object equal to Zero.
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

	// This sets the starting position and texture for all the ghosts.

	for (int i = 0; i < 4; i++)
	{
		ghost[i].setPosition(ghostRows[i], ghostCols[i]);
	}

	ghost[0].setTextureForBlueGhost();
	ghost[1].setTextureForGreenGhost();
	ghost[2].setTextureForPurpleGhost();
	ghost[3].setTextureForRedGhost();


	helpGhost.setTextureForBlueGhost();
	helpGhost.setUpPositionForGhostForHelpScreen();
	helpPellet.setUpPelletForHelpScreen();
	helpPlayer.setUpPlayerForHelpScreen();

	// This sets the starting position and texture for all the ghosts.

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart(); // This adds zero to the Time object.
		while (timeSinceLastUpdate > timePerFrame)  // This while loop will run every time, the times update is greater than the time per frame of the program.
		{
			timeSinceLastUpdate -= timePerFrame; // This substracts the time per frame, from the last update of time for this program.
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// This function updates the game every 60th of a second.
/// </summary>
/// <param name="t_deltaTime"></param>
void Game::update(sf::Time t_deltaTime)
{
	// This updates everything in the game.

	if (m_gameExit) m_window.close(); // This closes the window.
	updateMainMenuScreen();
	updateHelpScreen();
	updateGamePlayScreen();
	updateYouLoseScreen();
	updateYouWinScreen();

	// This updates everything in the game.
}

/// <summary>
/// This function updates the game play screen every 60th of a second.
/// </summary>
void Game::updateGamePlayScreen()
{
	if (gameStates == GameScreens::GamePlay)
	{
		updatePlayer();
		updateGhosts();
	}
}

/// <summary>
/// This function updates the player every 60th of a second.
/// </summary>
void Game::updatePlayer()
{
	// Updates the player every 60th of a second.

	if (player.getHealth() <= LOWEST_HEALTH) // If the health is lower than or equal to zero, it changes the game state.
	{
		playerScoreTextGameOver.setString(userInput + " Score: " + std::to_string(score));
		gameStates = GameScreens::YouLost;
		backgroundMusic.play();
	}
	 
	if (score >= MAX_SCORE) // If the health is greater than or equal to 590, it changes the game state.
	{
		gameStates = GameScreens::YouWon;
		backgroundMusic.play();
	}

	playerScoreTextGameplay.setString(userInput + " Score: " + std::to_string(score));
	playerHealthText.setString(userInput + " Health: " + std::to_string(player.getHealth()));

	player.move(cellType, score);

	// Updates the player every 60th of a second.
}

/// <summary>
/// This function updates the ghosts every 60th of a second.
/// </summary>
void Game::updateGhosts()
{

	// Updates the ghosts every 60th of a second.

	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghost[i].move(cellType);
	}
		

	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		if (ghost[i].getCol() == player.getCol() && ghost[i].getRow() == player.getRow()) // If the player is in the ghost row and col, then they have collided.
		{
			for (int j = 0; j < MAX_GHOSTS; j++)
			{
				ghost[j].setPosition(ghostRows[j], ghostCols[j]); // Sets every ghost back to thier starting position.
			}
			player.ghostCollisions();
		}
	}

	// Saves everything related to the ghosts and player.

	saveData.open("ASSETS/SAVE_DATA/GameData.txt");

	if (saveData.is_open())
	{
		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			saveData << "Ghost Number " << std::to_string(i);
			saveData << std::endl;
			saveData << std::endl;
			ghost[i].saveDataToFile(saveData);
			saveData << std::endl;
			saveData << std::endl;
		}

		saveData << "Player Data ";
		saveData << std::endl;
		saveData << std::endl;
		player.saveDataToFile(saveData);
		saveData << std::endl;

		saveData.close();
	}
	else
	{
		std::cout << "Error - unable to open the txt file. \n";
	}

	// Saves everything related to the ghosts and player.

	// Updates the ghosts every 60th of a second.
}

/// <summary>
/// This function updates the main menu every 60th of a second.
/// </summary>
void Game::updateMainMenuScreen()
{
	// Updates the main menu screen every 60th of a second.

	if (gameStates == GameScreens::MainMenu)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			gameStates = GameScreens::EnterName;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			gameStates = GameScreens::Help;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			backgroundMusic.stop();
			m_gameExit = true;
		}
	}

	// Updates the main menu screen every 60th of a second.
}

/// <summary>
/// This function updates the help screen every 60th of a second.
/// </summary>
void Game::updateHelpScreen()
{
	// Updates the help screen every 60th of a second.

	if (gameStates == GameScreens::Help)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) gameStates = GameScreens::MainMenu;
	}

	// Updates the help screen every 60th of a second.
}

/// <summary>
/// This function updates the you lose screen every 60th of a second.
/// </summary>
void Game::updateYouLoseScreen()
{
	// Updates the you lose screen every 60th of a second.

	if (gameStates == GameScreens::YouLost)
	{
		playerScoreTextGameOver.setString(userInput + " Score: " + std::to_string(score));
		highestScoreText.setString(userInput + " highest score: " + std::to_string(highestScore));
		if (score > highestScore)
		{
			highestScore = score;
		}
		else
		{
			highestScore = highestScore;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			player.setUpSprite();
			setUpGame();
			loadContent();
			for (int i = 0; i < MAX_GHOSTS; i++)
			{
				ghost[i].setUpSprite();
				ghost[i].setPosition(ghostRows[i], ghostCols[i]);
			}
			gameStates = GameScreens::MainMenu;
		}
	}

	// Updates the you lose screen every 60th of a second.
}

/// <summary>
/// This function updates the you win screen every 60th of a second.
/// </summary>
void Game::updateYouWinScreen()
{
	// Updates the you win screen every 60th of a second.

	highestScoreText.setString(userInput + " highest score: " + std::to_string(highestScore));
	playerScoreTextGameOver.setString(userInput + " Score: " + std::to_string(score));
	if (highestScore < score)
	{
		highestScore = score;
	}
	else
	{
		highestScore = highestScore;
	}
	if (gameStates == GameScreens::YouWon)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			player.setUpSprite();
			setUpGame();
			loadContent();
			for (int i = 0; i < MAX_GHOSTS; i++)
			{
				ghost[i].setUpSprite();
				ghost[i].setPosition(ghostRows[i], ghostCols[i]);
			}
			gameStates = GameScreens::MainMenu;
		}
	}

	// Updates the you win screen every 60th of a second.
}

/// <summary>
/// This function displays everything on screen.
/// </summary>
void Game::render()
{
	// This draws everything on screen.

	m_window.clear(); // This clears all the screen.

	if (gameStates == GameScreens::GamePlay)
	{
		drawGameplayScreen();
	}
	
	if (gameStates == GameScreens::EnterName)
	{
		m_window.draw(backgroundSprite);
		m_window.draw(enterNameText);
	}

	if (gameStates == GameScreens::MainMenu)
	{
		m_window.draw(backgroundSprite);
		m_window.draw(MainMenuText);
	}

	if (gameStates == GameScreens::Help)
	{
		drawHelpScreen();
	}

	if (gameStates == GameScreens::YouLost)
	{
		drawYouLoseScreen();
	}

	if (gameStates == GameScreens::YouWon)
	{
		drawYouWinScreen();
	}

	m_window.display(); // This displays everything.

	// This draws everything on screen.
}

/// <summary>
/// This function draws everything for the help screen.
/// </summary>
void Game::drawHelpScreen()
{
	// Draws everything related with the help screen.

	m_window.draw(helpGhostText);
	m_window.draw(helpPacmanText);
	m_window.draw(helpPelletText);
	m_window.draw(helpGhost.getBody());
	m_window.draw(helpPellet.getBody());
	m_window.draw(helpPlayer.getBody());
	m_window.draw(returnToMainMenuText);

	// Draws everything related with the help screen.
}

/// <summary>
/// This function draws everything for the gameplay screen.
/// </summary>
void Game::drawGameplayScreen()
{
	// Draws everything related with the gameplay screen.

	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (cellType[row][col].getStatus())
			{
				m_window.draw(cellType[row][col].getBody());
			}
		}
	}

	m_window.draw(player.getBody());

	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		m_window.draw(ghost[i].getBody());
	}

	m_window.draw(playerScoreTextGameplay);
	m_window.draw(playerHealthText);

	// Draws everything related with the gameplay screen.
}

/// <summary>
/// This function draws everything for the you win screen.
/// </summary>
void Game::drawYouWinScreen()
{
	// Draws everything related with the you win screen.

	m_window.draw(backgroundSprite);
	m_window.draw(youWonText);
	m_window.draw(playerScoreTextGameOver);
	m_window.draw(highestScoreText);
	m_window.draw(returnToMainMenuText);

	// Draws everything related with the you win screen.
}

/// <summary>
/// This function draws everything for the you lose screen.
/// </summary>
void Game::drawYouLoseScreen()
{
	// Draws everything related with the you lose screen.

	m_window.draw(backgroundSprite);
	m_window.draw(youLostText);
	m_window.draw(highestScoreText);
	m_window.draw(playerScoreTextGameOver);
	m_window.draw(returnToMainMenuText);

	// Draws everything related with the you lose screen.
}

/// <summary>
/// This function handles all user created events.
/// </summary>
void Game::processEvents()
{
	sf::Event event; // This initialize's, the Event object into memory.
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close(); // This closes the window.
		}
		
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code) // This checks if the user escaped the game.
			{
				m_gameExit = true;// This sets the bool to true.
			}

			if (gameStates == GameScreens::GamePlay)
			{
				if (player.getDirection() == Direction::None)
				{
					player.setDirection(event);
				}
			}
		}

		if (gameStates == GameScreens::EnterName)
		{
			UserEnterText(event);
		}
	}
}

/// <summary>
/// This function handles if the user presses anything on the keyboard for thier name.
/// </summary>
/// <param name="t_event"></param>
void Game::UserEnterText(sf::Event t_event)
{
	if (t_event.type == sf::Event::TextEntered) // If the user pressed something on the keyboard.
	{
		if (t_event.text.unicode == 8) // if the press backspace on the keyboard.
		{
			if (userInput != "") // If the string is not empty.
			{
				userInput.erase(userInput.end() - 1); // delete a the last char on the string.
				enterNameText.setString(playerInput + " " + userInput);
			}
		}
		if ((t_event.text.unicode >= 'a' && t_event.text.unicode <= 'z' || t_event.text.unicode >= 'A' && t_event.text.unicode <= 'Z') || t_event.text.unicode == ' ')
		{
			if (userInput.length() <= MAX_NUMBER_OF_CHARACTERS) // Can only enter 10 characters.
			{
				userInput += t_event.text.unicode;
				enterNameText.setString(playerInput + " " + userInput);
			}
		}
	}
	if (userInput != "") // If it's not empty, start the game
	{
		if (sf::Event::KeyPressed == t_event.type) //user key press
		{
			if (sf::Keyboard::Enter == t_event.key.code)
			{
				backgroundMusic.stop();
				gameStates = GameScreens::GamePlay;
			}
		}
	}
	else // else don't.
	{
		if (sf::Event::KeyPressed == t_event.type)
		{
			if (sf::Keyboard::Enter == t_event.key.code)
			{
				playerInput = "Enter your name: ";
				enterNameText.setString(playerInput);
			}
		}
	}
}
