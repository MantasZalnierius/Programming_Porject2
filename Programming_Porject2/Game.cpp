
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
	setUpText();
	cooldown = 0;

}


void Game::setUpGame()
{
	int setUpArray[MAX_ROWS][MAX_COLS] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,1,1,1,1,1,1,2,2,1,1,1,1,1,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,2,1,1 },
	{ 1,1,2,2,2,2,1,2,1,1,1,1,1,1,1,1,1,2,1,2,2,2,2,1,1 },
	{ 1,1,2,1,1,2,1,2,1,1,1,1,1,1,1,1,1,2,1,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,1,1,1,1,1,1,2,2,1,1,1,1,1,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,1,1 },
	{ 1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			cellType[row][col].setUpSprites(setUpArray[row][col], row, col);
		}
	}
}

void Game::setUpText()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error ";
	}

	playerInput = "Enter your name: ";
	userInput = "";

	enterNameText.setFont(font);
	enterNameText.setCharacterSize(40);
	enterNameText.setString(playerInput);
	enterNameText.setPosition(250.0f, 370.0f);
	score = 0;

	playerScore.setFont(font);
	playerScore.setCharacterSize(30);
	playerScore.setString(userInput + " Score: " + std::to_string(score));
	playerScore.setPosition(20.0f, 750.0f);
}




Game::~Game()
{
}


void Game::loadContent()
{
}


void Game::run()
{
	sf::Clock clock; // This initialize's the Clock object into memory.
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // This lets the Time object equal to Zero.
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	int ghostRows[4]{ 2, 10, 15, 22 };
	int ghostCols[4]{ 2, 7, 19, 22 };
	for (int i = 0; i < 4; i++)
	{
		ghost[i].setPosition(ghostRows[i], ghostCols[i]);
	}

	ghost[0].setTextureForBlueGhost();
	ghost[1].setTextureForGreenGhost();
	ghost[2].setTextureForPurpleGhost();
	ghost[3].setTextureForRedGhost();

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
	if (gameStates == GameScreens::GamePlay)
	{
		playerScore.setString(userInput + " Score: " + std::to_string(score));

		player.setCol(static_cast<int>(player.getBody().getPosition().x) / 32);
		player.setRow(static_cast<int>(player.getBody().getPosition().y) / 32);

		for (int i = 0; i < 4; i++)
		{
			ghost[i].setCol(static_cast<int>(ghost[i].getBody().getPosition().x) / 32);
			ghost[i].setRow(static_cast<int>(ghost[i].getBody().getPosition().y) / 32);

			if (ghost[i].getDirection() == GhostDirection::None)
			{
				ghost[i].setDirection();
			}

			if (ghost[i].getDirection() != GhostDirection::None)
			{
				if (ghost[i].getCooldown() <= 0)
				{
					ghost[i].move(cellType);
					ghost[i].sets(GhostDirection::None);
					ghost[i].setCooldown(15);
				}
				else
				{
					ghost[i].setCooldown(ghost[i].getCooldown() - 1);
				}
			}

			if (ghostCooldown <= 0)
			{
				ghostCooldown = 5 * 60;
				ghost[i].setdir(rand() % 4 + 1);
			}
			else
			{
				ghostCooldown--;
			}

		}

		if (player.getDirection() != Direction::None)
		{
			player.move(cellType);
			player.sets(Direction::None);
		}

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
	

}


void Game::render()
{
	m_window.clear(); // This clears all the screen.
	if (gameStates == GameScreens::GamePlay)
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

		m_window.draw(playerScore);
		
	}
	
	if (gameStates == GameScreens::EnterName)
	{
		m_window.draw(enterNameText);
	}
	m_window.display(); // This displays everything.
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
		UserEnterText(event);
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
				{
					gameStates = GameScreens::GamePlay;
				}
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