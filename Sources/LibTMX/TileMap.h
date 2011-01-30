/*
 *  TileMap.h
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

#ifndef _TileMap_H_
#define _TileMap_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TileSet.h"

class Tile;

class TileMap
{
public:
	TileMap(int width, int height, int tilewidth, int tileheight);
	~TileMap();
	void setLayer(const std::vector<int>& data,const VectorTileSet& tilesets,float opacity=1.0);
	void setTile(int x, int y,int tile_id,const VectorTileSet& tilesets,float opacity=1.0);
	void renderMap(sf::RenderWindow& window) const;
	int  getWidth() const;
	int  getHeight() const;
	int  getTileWidth() const;
	int  getTileHeight() const;
	
	
private:
	int m_width;
	int m_height;
	int m_tilewidth;
	int m_tileheight;
	Tile* m_layer;
};

class VectorTileMap : public std::vector<TileMap*> 
{
public:
	VectorTileMap();
	~VectorTileMap();
};

#endif //end of TileMap
