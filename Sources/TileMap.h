/*
 *  TileMap.h
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

#ifndef _TileMap_H_
#define _TileMap_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace sf 
{
	class RenderWindow;
	class Sprite;
}

class TileSet;
class TileSets;


class TileMap
{
public:
	TileMap(int width, int height, int tilewidth, int tileheight);
	~TileMap();
	void addLayer(const std::vector<int>& data,const TileSets& tilesets,float opacity=1.0);
	void addLayers(TileMap& layers);
	void renderMap(sf::RenderWindow& window,const sf::FloatRect& area) const;
	
private:
	int m_width;
	int m_height;
	int m_tilewidth;
	int m_tileheight;
	std::vector<sf::Sprite*> m_layer;
};

#endif //end of TileMap
