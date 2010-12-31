/*
 *  TileMap.cpp
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
#include "TileMap.h"
#include "TileSet.h"
#include "Tile.h"
#include "TMXLoader.hpp"
#include <SFML/Graphics.hpp>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

TileMap::TileMap(int width, int height, int tilewidth, int tileheight)
: m_width(width)
, m_height(height)
, m_tilewidth(tilewidth)
, m_tileheight(tileheight)
, m_layer(NULL)
{
}

TileMap::~TileMap()
{
	if (m_layer != NULL) delete[] m_layer;
}

void TileMap::setLayer(const std::vector<int>& data,const VectorTileSet& tilesets,float opacity)
{
	if (m_layer != NULL) delete[] m_layer;
	m_layer = new Tile[m_width*m_height];
	for(int i=0; i<m_width;i++)
	{
		for(int j=0;j<m_height;j++)
		{
			int pos = i+j*m_width;
			int numTileSet = tilesets.getTileSetFromID(data[i+j*m_width]);
			if (numTileSet>=0)
			{
				m_layer[pos].SetTile(*tilesets[numTileSet],data[i+j*m_width]);
				m_layer[pos].SetColor(sf::Color(255,255,255,255*opacity));
			}
			else 
			{
				m_layer[pos].SetColor(sf::Color(255,255,255,0));
			}
			m_layer[pos].SetPosition(i*m_tilewidth,j*m_tileheight);
		}
	}
}
void TileMap::setTile(int x, int y,int tile_id,const VectorTileSet& tilesets,float opacity)
{
	int pos = x+y*m_width;
	int numTileSet = tilesets.getTileSetFromID(tile_id);
	if (numTileSet>=0)
	{
		m_layer[pos].SetTile(*tilesets[numTileSet],tile_id);
		m_layer[pos].SetColor(sf::Color(255,255,255,255*opacity));
	}
	else 
	{
		m_layer[pos].SetColor(sf::Color(255,255,255,0));
	}	
}


void TileMap::renderMap(sf::RenderWindow& window) const
{	
	for(int i= 0;i<m_width;i++)
	{
		for(int j=0;j<m_height;j++)
		{
			window.Draw(m_layer[i+j*m_width]);
		}
	}
}
