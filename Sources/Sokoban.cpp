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

static sf::Vector2i v_dir[4]={sf::Vector2i(0,1),sf::Vector2i(1,0),sf::Vector2i(-1,0),sf::Vector2i(0,-1)};
static SokobanTile  player_dir[4] = {MARIO_BAS,MARIO_DROITE,MARIO_GAUCHE,MARIO_HAUT};
static int toId(const sf::Vector2i& v)
{
	return v.x+v.y*NB_BLOCS_LARGEUR;
}

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
, m_oldTile(VIDE)
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
	while ((loadLevel(i)==false) && (i<m_loader->getNbLayer()))i++;
	if (i==m_loader->getNbLayer())
	{   
		error("can't load any levels");
		return false;
	}
	m_level = i;
	
	return true;
}

void Sokoban::goNextLevel()
{
	if(m_tempo.GetElapsedTime()>0.5)
	{
		int i=m_level+1;
		while(loadLevel((i)%m_max_level)==false) i++;
		m_level = i%m_max_level;
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
			case sf::Key::Space : goNextLevel();                break;
			case sf::Key::Return: loadLevel(m_level);           break;
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
	if(m_nb_objectif==0) goNextLevel();		
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
						m_data[toId(m_pos)]=0;
						setTile(VIDE, m_pos);
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
	if(canMove(m_pos,dir))
	{
		moveJoueur(m_pos,dir);
	}
	else if( isBox(m_pos,dir) && canMove(m_pos+v_dir[dir],dir) )
	{
		moveCaisse(m_pos+v_dir[dir],dir);
		moveJoueur(m_pos,dir);
	}
	else 
	{
		setTile(player_dir[dir], m_pos);
	}

	m_tempo.Reset();
}

bool Sokoban::canMove(const sf::Vector2i pos,Direction dir) const
{
	if( ((pos+v_dir[dir]).y>=0) && ((pos+v_dir[dir]).y<NB_BLOCS_HAUTEUR) && ((pos+v_dir[dir]).x>=0) && ((pos+v_dir[dir]).x<NB_BLOCS_LARGEUR) )
	{
		if ((m_data[toId(pos+v_dir[dir])] == VIDE) || (m_data[toId(pos+v_dir[dir])] == OBJECTIF)) return true;
	}
	return false;
}

bool Sokoban::isBox(const sf::Vector2i pos,Direction dir) const
{
	if( ((pos+v_dir[dir]).y>=0) && ((pos+v_dir[dir]).y<NB_BLOCS_HAUTEUR) && ((pos+v_dir[dir]).x>=0) && ((pos+v_dir[dir]).x<NB_BLOCS_LARGEUR) )
	{
		if ((m_data[toId(pos+v_dir[dir])] == CAISSE) || (m_data[toId(pos+v_dir[dir])] == CAISSE_OK)) return true;
	}
	return false;
}


void Sokoban::moveCaisse(const sf::Vector2i pos,Direction dir)
{
	if(m_data[toId(pos)] == CAISSE_OK)
	{
		setTile(OBJECTIF , pos);
		m_data[toId(pos)] = OBJECTIF;
		m_nb_objectif++;
	}
	else if(m_data[toId(pos)] == CAISSE)
	{
		setTile(VIDE , pos);
		m_data[toId(pos)] = VIDE;
	}
	if(m_data[toId(pos+v_dir[dir])] == VIDE)
	{
		setTile(CAISSE, pos+v_dir[dir]);
		m_data[toId(pos+v_dir[dir])] = CAISSE;

	}
	else if(m_data[toId(pos+v_dir[dir])] == OBJECTIF)
	{
		setTile(CAISSE_OK, pos+v_dir[dir]);
		m_data[toId(pos+v_dir[dir])] = CAISSE_OK;
		m_nb_objectif--;
	}
}

void Sokoban::moveJoueur(const sf::Vector2i pos,Direction dir)
{
	setTile(m_oldTile , m_pos);
	m_data[toId(m_pos)] = m_oldTile;
	m_oldTile = (SokobanTile)m_data[toId(m_pos+v_dir[dir])];
	setTile(player_dir[dir], m_pos+v_dir[dir]);
	m_data[toId(m_pos+v_dir[dir])] = player_dir[dir];
	m_pos+=v_dir[dir];
}

void Sokoban::setTile(SokobanTile tile,const sf::Vector2i pos)
{
	m_tilemap->setTile(pos.x, pos.y, tile, m_tileset,1);
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
