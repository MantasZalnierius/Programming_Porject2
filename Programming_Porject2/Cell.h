#ifndef CELL
#define CELL

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <iostream>

enum class TypeOfCell // Enum class to for all the objects in game.
{
	Wall,
	Pellet,
	None
};

class Cell
{
	// Member variables

	TypeOfCell typeOfCell = TypeOfCell::None; // Type of object in game, wall pellet ect.
	sf::Sprite m_sprite; // Sprites for all the objects in game.
	sf::Texture m_pelletTexture; // Texture for the pellet in the game.
	sf::Texture m_wallTexture1; // Textures for the walls in the game.
	sf::Texture m_wallTexture2;
	sf::Texture m_wallTexture3;
	sf::Texture m_wallTexture4;
	sf::Texture m_wallTexture5;
	sf::Texture m_wallTexture6;
	sf::Texture m_wallTexture7;
	int m_cellType; // To see what type of cell it is.
	bool isAlive; // To see if the object is avtive in the game.

	// Member variables

public:
		// Member functions

	   Cell();
	  ~Cell();
		void   setUpTexture();
		void   playerCollision();
		void   setUpPelletForHelpScreen();
		void   setUpSprites(int t_cellType, int t_row, int t_col);
		inline sf::Sprite getBody() { return m_sprite; }
		inline TypeOfCell getCell() { return typeOfCell; }
		inline bool getStatus() { return isAlive; }

		// Member functions

};


#endif
