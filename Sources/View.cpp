/*
 *  View.cpp
 *  TMX_Renderer
 *
 *  Created by mooglwy on 04/01/11.
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
#include "View.h"
#include "const.h"

View::View()
: m_map(new TileMap(NB_BLOCS_LARGEUR,NB_BLOCS_HAUTEUR,TILE_SIZE,TILE_SIZE))
, m_tileset()
{
}

View::~View()
{
	delete m_map;
}

bool View::setTileset(const std::string& tileset_filename)
{
	sf::Image* image = new sf::Image;
	if(!image.LoadFromFile(tileset_filename))
	{
		delete image;
		return false;
	}
	TileSet tileset;
	tileset.loadTileSet(image,1, TILE_SIZE, TILE_SIZE);
	m_tileset[0] = tileset;
	return true;
}

bool View::setId(int x,int y,SokobanTile tile)
{
	if(x>=0 && x<NB_BLOCS_LARGEUR && y>=0 && Y<NB_BLOCS_HAUTEUR)
	{
		m_map.setID(x,y,(int)tile,m_tileset);
		return true;
	}
	return false;
}

void View::Draw(sf::RenderWindow& win) const
{
	m_map.renderMap(win);
}
