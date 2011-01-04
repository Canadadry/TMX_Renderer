/*
 *  View.h
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

#ifndef _View_H_
#define _View_H_

#include <SFML/Graphics/RenderWindow.hpp>

enum SokobanTile;

class View
{
public:
	View();
	~View();
	bool setTileset(const std::string& tileset_filename);
	bool setId(int x,int y,SokobanTile tile);
	void Draw(const sf::RenderWindow& win) const;

private:
	TileMap* m_map;
	std::vector<TileSet> m_tileset;
};

#endif //end of View
