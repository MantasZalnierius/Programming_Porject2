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
	cooldown = 0;

}

void Game::setUpGame()
{

	int setUpArray[MAX_ROWS][MAX_COLS]{};

	std::string line;
	std::string item;
	int i, j;
	bool dataOK = true;
	std::ifstream myfile("LevelData.txt");

	if (myfile.is_open())
	{

			i = 0;
			while (std::getline(myfile, line) && dataOK)
			{
				std::stringstream line_ss(line);
				j = 0;
				while (std::getline(line_ss, item, ',') && dataOK)
				{
					std::cout << item << '\n';
					if (item == "1")
						setUpArray[i][j] = 1;
					if (item == "2")
						setUpArray[i][j] = 2;
					j++;
					if (j > MAX_COLS)
					{
						std::cout << "too many cols" << "\n";
						dataOK = false;
					}
				}
				i++;
				if (i > MAX_ROWS)
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

	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			cellType[row][col].setUpSprites(setUpArray[row][col], row, col);
		}
	}
}

void Game::loadContent()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error ";
	}

	playerInput = "Enter your name: ";
	userInput = "";

	SetupText(enterNameText, sf::Vector2f(250.0f, 370.0f), playerInput);
	SetupText(playerScoreText, sf::Vector2f(20.0f, 750.0f), (userInput + " Score: " + std::to_string(score)));
	SetupText(playerHealthText, sf::Vector2f(640.0f, 750.0f), (userInput + " Health: " + std::to_string(player.getHealth())));
	SetupText(MainMenuText, sf::Vector2f(350.0f, 300.0f), "(1) New Game \n\n (2) Controls \n\n (3) Exit ");
	SetupText(helpGhostText, sf::Vector2f(100.0f, 100.0f), "These are ghosts, they are your eneimes. \n Stay away from them and you'll be fine \n they will navigate through the level looking for you.");
	SetupText(helpPacmanText, sf::Vector2f(100.0f, 600.0f), "You are Pacman \n your goal is to get every single pellet before the ghosts kill you. \n When a ghost collides with you, you lose 1 live. \n You only have three lives in the game.");
	SetupText(helpPelletText, sf::Vector2f(100.0f, 350.0f), "These are pellets \n when you eat one of these pellets you will get 2 two points.\n Your goal is to get all of these pellets. ");
	SetupText(returnToMainMenuText, sf::Vector2f(230.0f, 750.0f), "Press 4 to go back to the main menu ");
	SetupText(youLostText, sf::Vector2f(300.0f, 350.0f), "You Lost The Game ");
	SetupText(youWonText, sf::Vector2f(300.0f, 350.0f), "You Lost The Game ");
}

void Game::SetupText(sf::Text &t_text, sf::Vector2f t_position, std::string t_sentence)
{
	t_text.setFont(font);  // set the font for the text
	t_text.setCharacterSize(30); // set the text size
	t_text.setFillColor(sf::Color::White); // set the text colour
	t_text.setPosition(t_position);  // its position on the screen
	t_text.setString(t_sentence); // This sets the string to the text.
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock; // This initialize's the Clock object into memory.
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // This lets the Time object equal to Zero.
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

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


void Game::update(sf::Time t_deltaTime)
{
	if (m_gameExit)
	{
		m_window.close(); // This closes the window.
	}
	updateMainMenuScreen();
	updateHelpScreen();
	updateGamePlayScreen();
	updateYouLoseScreen();
	updateYouWinScreen();
	std::ofstream outputFile;
}

void Game::updateGamePlayScreen()
{
	if (gameStates == GameScreens::GamePlay)
	{
		updatePlayer();
		updateGhosts();
	}
}

void Game::updatePlayer()
{
	if (player.getHealth() <= 0)
	{
		gameStates = GameScreens::YouLost;
	}

	if (score >= 356)
	{
		gameStates = GameScreens::YouWon;
	}

	playerScoreText.setString(userInput + " Score: " + std::to_string(score));
	playerHealthText.setString(userInput + " Health: " + std::to_string(player.getHealth()));

	player.move(cellType);

	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (cellType[row][col].getStatus() && cellType[row][col].getCell() == TypeOfCell::Pellet)
			{
				cellType[row][col].playerCollision(player.getBody());
				player.pelletCollision(cellType[row][col].getBody(), score);
			}
		}
	}
}

void Game::updateGhosts()
{

	for (int i = 0; i < 4; i++)
	{
		ghost[i].move(cellType, ghost[i + 1].getRow(), (ghost[i + 1].getCol()));
		inputFile.open("GhostData.txt");

		if (inputFile.is_open())
		{
			ghost[i].saveDataToFile(inputFile);
			inputFile << std::endl;

		}
		else
		{
			std::cout << "Error - unable to open the txt file. \n";
		}
	}

	inputFile.close();

	for (int i = 0; i < 4; i++)
	{
		if (ghost[i].getCol() == player.getCol() && ghost[i].getRow() == player.getRow())
		{
			for (int j = 0; j < 4; j++)
			{
				ghost[j].setPosition(ghostRows[j], ghostCols[j]);
			}
			player.collisions();
		}
	}
}

void Game::updateMainMenuScreen()
{
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
			m_gameExit = true;
		}
	}
}

void Game::updateHelpScreen()
{
	if (gameStates == GameScreens::Help)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			gameStates = GameScreens::MainMenu;
		}
	}
}

void Game::updateYouLoseScreen()
{
	if (gameStates == GameScreens::YouLost)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			player.setUpSprite();
			setUpGame();
			loadContent();
			for (int i = 0; i < 4; i++)
			{
				ghost[i].setUpSprite();
				ghost[i].setPosition(ghostRows[i], ghostCols[i]);
			}
			gameStates = GameScreens::MainMenu;
		}
	}
}

void Game::updateYouWinScreen()
{
	if (gameStates == GameScreens::YouWon)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			player.setUpSprite();
			setUpGame();
			loadContent();
			for (int i = 0; i < 4; i++)
			{
				ghost[i].setUpSprite();
				ghost[i].setPosition(ghostRows[i], ghostCols[i]);
			}
			gameStates = GameScreens::MainMenu;
		}
	}
}


void Game::render()
{
	m_window.clear(); // This clears all the screen.

	if (gameStates == GameScreens::GamePlay)
	{
		drawGameplayScreen();
	}
	
	if (gameStates == GameScreens::EnterName)
	{
		m_window.draw(enterNameText);
	}

	if (gameStates == GameScreens::MainMenu)
	{
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
}

void Game::drawHelpScreen()
{
	m_window.draw(helpGhostText);
	m_window.draw(helpPacmanText);
	m_window.draw(helpPelletText);
	m_window.draw(helpGhost.getBody());
	m_window.draw(helpPellet.getBody());
	m_window.draw(helpPlayer.getBody());
	m_window.draw(returnToMainMenuText);
}

void Game::drawGameplayScreen()
{
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

	for (int i = 0; i < 4; i++)
	{
		m_window.draw(ghost[i].getBody());
	}

	m_window.draw(playerScoreText);
	m_window.draw(playerHealthText);
}

void Game::drawYouWinScreen()
{
	m_window.draw(youWonText);
	m_window.draw(playerScoreText);
	m_window.draw(returnToMainMenuText);
}

void Game::drawYouLoseScreen()
{
	m_window.draw(youLostText);
	m_window.draw(playerScoreText);
	m_window.draw(returnToMainMenuText);
}

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

void Game::UserEnterText(sf::Event t_event)
{
	if (t_event.type == sf::Event::TextEntered)
	{
		if (t_event.text.unicode == 8)
		{
			if (userInput != "")
			{
				userInput.erase(userInput.end() - 1);
				enterNameText.setString(playerInput + " " + userInput);
			}
		}
		if ((t_event.text.unicode >= 'a' && t_event.text.unicode <= 'z' || t_event.text.unicode >= 'A' && t_event.text.unicode <= 'Z') || t_event.text.unicode == ' ')
		{
			userInput += t_event.text.unicode;
			enterNameText.setString(playerInput + " " + userInput);
		}
	}
	if (userInput != "")
	{
		if (sf::Event::KeyPressed == t_event.type) //user key press
		{
			if (sf::Keyboard::Enter == t_event.key.code)
			{
				gameStates = GameScreens::GamePlay;
			}
		}
	}
	else
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
