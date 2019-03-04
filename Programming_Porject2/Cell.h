#ifndef CELL
#define CELL

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>

class Cell
{
	sf::Sprite m_sprite;
	sf::Texture m_emptyCellTexture;
	sf::Texture m_pelletTexture;
	sf::Texture m_wallTexture;
	int m_cellType;

public:
	   Cell();
	  ~Cell();
 void  draw(sf::RenderWindow &t_window, int t_CellType);
 void  setUpSprites(int t_cellType, int t_row, int t_col);
 void  setUpTexture();
 inline sf::Sprite getBody() { return m_sprite; }

};


#endif
