/*
 *  Sokoban.cpp
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
#include "const.h"
#include "Sokoban.h"
#include "TMXLoader.hpp"
#include "TileMap.h"
#include <iostream>
#include <sstream>

struct Delete 
{ 
	template <class T> void operator ()(T*& p) const 
	{ 
		delete p;
		p = NULL;
	} 
};

static std::string toString(int i)
{
	std::ostringstream out;
	out << i;
	return out.str();
}

static void error(std::string message)
{
	std::cerr<< "Error:" << message << std::endl;
}

Sokoban::Sokoban()
: m_loader(NULL)
, m_tileset()
, m_tilemap(NULL)
, m_data()
, m_nb_objectif(0)
, m_pos(-1,-1)
, m_ispressedDir()
, m_level(0)
, m_max_level(0)
{
	m_ispressedDir[HAUT  ] = false;
	m_ispressedDir[BAS   ] = false;
	m_ispressedDir[GAUCHE] = false;
	m_ispressedDir[DROITE] = false;
	m_tempo.Reset();
}

Sokoban::~Sokoban()
{
	if(m_loader!=NULL) delete m_loader;
	if(m_tilemap!=NULL) delete m_tilemap;
}


bool Sokoban::loadLevels(const std::string& filename)
{
	cleanAll();
	
	m_loader = new TMXLoader;
	if(m_loader->LoadFromFile(filename) ==  false)
	{
		error("can't load :" +filename);
		return false;
	}
	
	if(m_loader->ExtractVectorTileSet(m_tileset) != 1)
	{
		error("Must have one tileset");
		return false;
	}
	
	if(m_tileset[0]->getNumberOfTile() != NUMBER_TILES)
	{
		error("Number of Tile don't match there must be: " + toString(NUMBER_TILES) + " and there are :" + toString(m_tileset[0]->getNumberOfTile()));
		return false;
	}
	m_max_level = m_loader->getNbLayer();
	if(m_max_level<=0)
	{
		error("Must have at least one level");
		return false;
	}
	int i=0;
	while ((loadLevel(i++)==false) && (i<m_loader->getNbLayer()));
	if (i==m_loader->getNbLayer())
	{
		error("can't load any levels");
		return false;
	}
	
	return true;
}

void Sokoban::goNextLevel()
{
	if(m_tempo.GetElapsedTime()>0.5)
	{
		int i=m_level;
		while((loadLevel((i++)%m_max_level)==false) && (i<m_max_level));
		m_level = (i++)%m_max_level;
		m_tempo.Reset();
	}
}


void Sokoban::handleEvent(sf::Event event)
{
	if (event.Type == sf::Event::KeyPressed)
	{
		switch(event.Key.Code)
		{
			case sf::Key::Up    : m_ispressedDir[HAUT  ] = true;break;
			case sf::Key::Down  : m_ispressedDir[BAS   ] = true;break;
			case sf::Key::Left  : m_ispressedDir[GAUCHE] = true;break;
			case sf::Key::Right : m_ispressedDir[DROITE] = true;break;
			case sf::Key::Space : goNextLevel();break;
			default: ;//nothing for the rest
		}
	}
	else 	if (event.Type == sf::Event::KeyReleased)
	{
		switch(event.Key.Code)
		{
			case sf::Key::Up    : m_ispressedDir[HAUT  ] = false;break;
			case sf::Key::Down  : m_ispressedDir[BAS   ] = false;break;
			case sf::Key::Left  : m_ispressedDir[GAUCHE] = false;break;
			case sf::Key::Right : m_ispressedDir[DROITE] = false;break;
			default: ;//nothing for the rest
		}
	}
}

void Sokoban::update(double elpasedTime)
{
	if(m_tempo.GetElapsedTime()>0.3)
	{
		if(m_ispressedDir[HAUT])
		{
			move(HAUT);
		}	
		else if(m_ispressedDir[BAS])
		{
			move(BAS);
		}
		else if(m_ispressedDir[GAUCHE])
		{
			move(GAUCHE);
		}
		else if(m_ispressedDir[DROITE])
		{
			move(DROITE);
		}
		
	}
		
}


void Sokoban::render(sf::RenderWindow& window) const
{
	if(m_tilemap != NULL)
		m_tilemap->renderMap(window);
}

bool Sokoban::loadLevel(int level)
{
	cleanLevel();
	
	m_tilemap = m_loader->ExtractLayerAsMap(level);
	if (m_tilemap == NULL)
	{
		error("error while extracting layer");
		return false;
	}
	if (m_loader->ExtractLayerAsData(level,m_data) == false) 
	{
		error("error while extracting data");
		return false;
	}
	
	int nb_caisse = 0;
	for (int i = 0; i< NB_BLOCS_LARGEUR; i++)
	{
		for (int j = 0; j< NB_BLOCS_HAUTEUR; j++)
		{
			switch ((SokobanTile)m_data[i+j*NB_BLOCS_LARGEUR]) 
			{
				case MARIO_BAS    : 
				case MARIO_DROITE : 
				case MARIO_GAUCHE : 
				case MARIO_HAUT   : 
				{
					if(m_pos != sf::Vector2i(-1,-1))
					{
						m_data[m_pos.x+m_pos.y*NB_BLOCS_LARGEUR]=0;
						setTile(VIDE, m_pos.x, m_pos.y);
					}
					m_pos.x = i;
					m_pos.y = j;
					break;
				}
				case CAISSE       : nb_caisse++; break;
				case OBJECTIF     : m_nb_objectif++; break;
					//for other do nothing
				case VIDE:
				case CAISSE_OK:
				case MUR:
				default:;
			}
		}	
	}
	
	if(nb_caisse != m_nb_objectif)
	{
		error("Not the same number of box("+toString(nb_caisse)+") and objectives("+toString(m_nb_objectif)+")");
		return false;
	}
	if(m_pos == sf::Vector2i(-1,-1)) 
	{
		error("No start position found");
		return false;
	}
	return true;
}

void Sokoban::move(Direction dir)
{
	switch (dir)
	{
		case HAUT:
		{
			if(m_pos.y>0)
			{
				if (m_data[m_pos.x+(m_pos.y-1)*NB_BLOCS_LARGEUR] == VIDE)
				{
					m_data[m_pos.x+(m_pos.y-1)*NB_BLOCS_LARGEUR] = MARIO_HAUT;
					m_data[m_pos.x+(m_pos.y  )*NB_BLOCS_LARGEUR] = VIDE;
					setTile(MARIO_HAUT, m_pos.x, m_pos.y-1);
					setTile(VIDE, m_pos.x, m_pos.y);
					m_pos.y--;
				}
			}
			break;
		}
		case BAS:
		{
			if(m_pos.y<(NB_BLOCS_HAUTEUR-1))
			{
				if (m_data[m_pos.x+(m_pos.y+1)*NB_BLOCS_LARGEUR] == VIDE)
				{
					m_data[m_pos.x+(m_pos.y+1)*NB_BLOCS_LARGEUR] = MARIO_BAS;
					m_data[m_pos.x+(m_pos.y  )*NB_BLOCS_LARGEUR] = VIDE;
					setTile(MARIO_BAS, m_pos.x, m_pos.y+1);
					setTile(VIDE, m_pos.x, m_pos.y);
					m_pos.y++;
				}
			}
			break;
		}
		case DROITE:
		{
			if(m_pos.x<(NB_BLOCS_LARGEUR-1))
			{
				if (m_data[m_pos.x+1+m_pos.y*NB_BLOCS_LARGEUR] == VIDE)
				{
					m_data[m_pos.x+1+m_pos.y*NB_BLOCS_LARGEUR] = MARIO_DROITE;
					m_data[m_pos.x  +m_pos.y*NB_BLOCS_LARGEUR] = VIDE;
					setTile(MARIO_DROITE, m_pos.x+1, m_pos.y);
					setTile(VIDE, m_pos.x, m_pos.y);
					m_pos.x++;
				}
			}
			break;
		}
		case GAUCHE:
		{
			if(m_pos.x>0)
			{
				if (m_data[m_pos.x-1+m_pos.y*NB_BLOCS_LARGEUR] == VIDE)
				{
					m_data[m_pos.x-1+m_pos.y*NB_BLOCS_LARGEUR] = MARIO_GAUCHE;
					m_data[m_pos.x  +m_pos.y*NB_BLOCS_LARGEUR] = VIDE;
					setTile(MARIO_GAUCHE, m_pos.x-1, m_pos.y);
					setTile(VIDE, m_pos.x, m_pos.y);
					m_pos.x--;
				}
			}
			break;
		}
	}
	m_tempo.Reset();
}

bool Sokoban::canMove(int x,int y,Direction dir) const
{
	return false;
}

void Sokoban::moveCaisse(int x,int y,Direction dir)
{
	
}

void Sokoban::moveJoueur(int x,int y,Direction dir)
{
	
}

void Sokoban::setTile(SokobanTile tile, int x,int y)
{
	m_tilemap->setTile(x, y, tile, m_tileset,1);
}

void Sokoban::cleanLevel()
{
	m_nb_objectif = 0;
	m_pos = sf::Vector2i(-1,-1);
	m_data.clear();
	if(m_tilemap!=NULL) delete m_tilemap;
	m_tilemap = NULL;
	m_ispressedDir[HAUT  ] = false;
	m_ispressedDir[BAS   ] = false;
	m_ispressedDir[GAUCHE] = false;
	m_ispressedDir[DROITE] = false;
}


void Sokoban::cleanAll()
{
	cleanLevel();
	std::for_each(m_tileset.begin() ,m_tileset.end(), Delete());
	if(m_loader!=NULL) delete m_loader;
	m_loader = NULL;
	m_level = 0;
	m_max_level = 0;
}
