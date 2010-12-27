/*
 *  TileMap.cpp
 *  TMX_Renderer
 *
 *  Created by mooglwy on 15/12/10.
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
#include "TMXLoader.hpp"
#include <SFML/Graphics.hpp>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

TileMap::TileMap(int width, int height, int tilewidth, int tileheight)
: m_width(width)
, m_height(height)
, m_tilewidth(tilewidth)
, m_tileheight(tileheight)
, m_layer()
{
}

TileMap::~TileMap()
{
	for (int i=0; i<m_layer.size(); i++)
	{
		delete[] m_layer[i];
	}
}

void TileMap::addLayer(const std::vector<int>& data,const TileSets& tilesets, float opacity)
{
	sf::Sprite* layer = new sf::Sprite[m_width*m_height];
	for(int i=0; i<m_width;i++)
	{
		for(int j=0;j<m_height;j++)
		{
			int pos = i+j*m_width;
			int numTileSet = tilesets.getTileSetFromID(data[i+j*m_width]);
			if (numTileSet>=0)
			{
				sf::IntRect rect = tilesets[numTileSet]->getRectOfTile(data[i+j*m_width]);
				layer[pos].SetImage(*(tilesets[numTileSet]->getImage()));
				layer[pos].SetSubRect(rect);
				layer[pos].SetColor(sf::Color(255,255,255,255*opacity));
			}
			else 
			{
				layer[pos].SetColor(sf::Color(255,255,255,0));
			}
			layer[pos].SetPosition(i*m_tilewidth,j*m_tileheight);
		}
	}
	m_layer.push_back(layer);
}

void TileMap::addLayers(TileMap& layers)
{
	if(   (m_width      != layers.m_width     ) 
	   || (m_height     != layers.m_height    ) 
	   || (m_tilewidth  != layers.m_tilewidth ) 
	   || (m_tileheight != layers.m_tileheight) )
	{
		return;
	}
	for(int l=0;l<layers.m_layer.size();l++)
	{
		m_layer.push_back(layers.m_layer[l]);
	}
	layers.m_layer.clear();
}


void TileMap::renderMap(sf::RenderWindow& window,const sf::FloatRect& area) const
{
	int first_x = MAX(0,area.Left / (float)m_tilewidth);
	int first_y = MAX(0,area.Top  / (float)m_tileheight);
	int  last_x = MIN(m_width,(area.Right  / (float)m_tilewidth)+1);
	int  last_y = MIN(m_height,(area.Bottom / (float)m_tileheight)+1);
	
	for(int l=0;l<m_layer.size();l++)
	{
		for(int i= first_x;i<last_x;i++)
		{
			for(int j=first_y;j<last_y;j++)
			{
				window.Draw(m_layer[l][i+j*m_width]);
			}
		}
	}
}
