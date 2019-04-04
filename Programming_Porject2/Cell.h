#ifndef CELL
#define CELL

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <iostream>

enum class TypeOfCell
{
	Wall,
	Pellet,
	None
};

class Cell
{
	TypeOfCell typeOfCell = TypeOfCell::None;
	sf::Sprite m_sprite;
	sf::Texture m_wallTexture1;
	sf::Texture m_pelletTexture;
	sf::Texture m_wallTexture2;
	sf::Texture m_wallTexture3;
	sf::Texture m_wallTexture4;
	sf::Texture m_wallTexture5;
	sf::Texture m_wallTexture6;
	sf::Texture m_wallTexture7;
	int m_cellType;
	bool isAlive;

public:
	   Cell();
	  ~Cell();
		void  setUpSprites(int t_cellType, int t_row, int t_col);
		void  setUpTexture();
		inline sf::Sprite getBody() { return m_sprite; }
		inline TypeOfCell getCell() { return typeOfCell; }
		inline bool getStatus() { return isAlive; }
		void playerCollision();
		void setUpPelletForHelpScreen();

};


#endif
