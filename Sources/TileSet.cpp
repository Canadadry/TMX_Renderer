/*
 *  TileSet.cpp
 *  TMX_Renderer
 *
 *  Created by Canadadry on 15/12/10.
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
#include "TileSet.h"
#include <SFML/Graphics.hpp>

//#define _LOG_
#ifdef _LOG_
#include <iostream>
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

TileSet::TileSet()
: m_image(NULL)
, m_tilewidth(0)
, m_tileheight(0)
, m_numberOfTile(0)
, m_firstID(0)
, m_widthInTile(0)
, m_heightInTile(0)
{
}

TileSet::~TileSet()
{
}

void TileSet::loadTileSet(sf::Image* image,int firstID,int tilewidth, int tileheight)
{
	m_image = image;
	m_firstID      = firstID;
	m_tilewidth    = tilewidth;
	m_tileheight   = tileheight;
	m_widthInTile  = m_image->GetWidth()/m_tilewidth;
	m_heightInTile = m_image->GetHeight()/m_tileheight;
	m_numberOfTile = m_widthInTile * m_heightInTile;
}

int TileSet::getFirstID() const
{
	return m_firstID;
}

int TileSet::getNumberOfTile() const
{
	m_numberOfTile;
}

bool TileSet::containID(int id) const
{
	return (id >= m_firstID) && (id < ( m_firstID + m_numberOfTile)); 
}

sf::Image& TileSet::getImage() const
{
	return *m_image;
}

sf::IntRect TileSet::getRectOfTile(int tileID) const
{
	if(m_firstID < 1) return sf::IntRect(0,0,0,0);
	int id_x = (tileID-m_firstID) % m_widthInTile;
	int id_y = (tileID-m_firstID) / m_widthInTile;
	PRINT("id:%d -> id_x:%d id_y:%d\n",tileID,id_x,id_y);
	
	return sf::IntRect(id_x*m_tilewidth,id_y*m_tileheight,(id_x+1)*m_tilewidth,(id_y+1)*m_tileheight);
	
}

VectorTileSet::VectorTileSet()
: std::vector<TileSet*>()
{
}


int VectorTileSet::getTileSetFromID(int id) const
{
	if (id == 0) return -1;
	for(int i=0;i<size();i++)
	{
		if((*this)[i]->containID(id)) return i;
	}
	return -1;
}


