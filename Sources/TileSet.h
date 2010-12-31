/*
 *  TileSet.h
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

#ifndef _TileSet_H_
#define _TileSet_H_

#include <string>
#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace sf 
{
	class Image;
}

class TileSet
{
public:
	TileSet();
	~TileSet();
	void loadTileSet(sf::Image* image,int firstID,int tilewidth, int tileheight);
	int getFirstID() const;
	int getNumberOfTile() const;
	bool containID(int id) const;
	sf::Image& getImage() const;
	sf::IntRect getRectOfTile(int tileID) const;


private:
	sf::Image* m_image;
	int m_tilewidth;
	int m_tileheight;
	int m_numberOfTile;
	int m_firstID;
	int m_widthInTile;
	int m_heightInTile;
		
};

class VectorTileSet : public std::vector<TileSet*> 
{
public:
	VectorTileSet();
	int getTileSetFromID(int id) const;
	
};

#endif //end of TileSet
