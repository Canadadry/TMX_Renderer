/*
 *  Sokoban.h
 *  TMX_Renderer
 *
 *  Created by mooglwy on 07/01/11.
 *
 *  This software is provided 'as-is', without any express or
 *  implied warranty. In no event will the authors be held
 *  liable for any damages arising from the use of this software.
 *  
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute
 *  it freely, subject to the following restrictions:
 *  
 *  1. The origin of this software must not be misrepresented;
 *     you must not claim that you wrote the original software.
 *     If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but
 *     is not required.
 *  
 *  2. Altered source versions must be plainly marked as such,
 *     and must not be misrepresented as being the original software.
 *  
 *  3. This notice may not be removed or altered from any
 *     source distribution.
 *
 */

#ifndef _Sokoban_H_
#define _Sokoban_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "TileSet.h"
#include <vector>
#include <string>

class TMXLoader;
class TileMap;
enum Direction;
enum SokobanTile;

class Sokoban
{
public:
	Sokoban();
	~Sokoban();
	bool loadLevels(const std::string& filename);
	void goNextLevel();
	void handleEvent(sf::Event event);
	void update(double elpasedTime);
	void render(sf::RenderWindow& window) const;

private:
	TMXLoader*         m_loader;
	VectorTileSet      m_tileset;
	TileMap*           m_tilemap;
	std::vector<int>   m_data;
	int                m_nb_objectif;	
	sf::Vector2i       m_pos;
	bool               m_ispressedDir[4];
	int                m_level;
	int                m_max_level;
	sf::Clock          m_tempo;
	SokobanTile        m_oldTile;

	bool loadLevel(int level);
	
	void move(Direction dir);
	bool canMove(const sf::Vector2i pos,Direction dir) const;
	bool isBox(const sf::Vector2i pos,Direction dir) const;
	void moveCaisse(const sf::Vector2i pos,Direction dir);
	void moveJoueur(const sf::Vector2i pos,Direction dir);
	void setTile(SokobanTile tile,const sf::Vector2i pos);
	
	void cleanLevel();
	void cleanAll();
	
};

#endif //end of Sokoban
