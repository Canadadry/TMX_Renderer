/*
 *  TMXLoader.hpp
 *  TMXLoader
 *
 *  Created by Canadadry on 28/11/10.
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

#ifndef _TMX_LOADER_
#define _TMX_LOADER_

#include <string>
#include <vector>


class TMXMap;
class TileMap;
class VectorTileSet;

class TMXLoader
{
public:
	TMXLoader(const std::string& filename = "");
	~TMXLoader();
	//TODO : problem if two successive call
	bool LoadFromFile(const std::string& filename);
	
	int ExtractVectorTileSet(VectorTileSet& tilesets) const;
	
	int getNbLayer() const;
	int getWidth() const;
	int getHeight() const;
	int getTileWidth() const;
	int getTileHeight() const;
	
	TileMap* ExtractLayerAsMap(int layer) const;
	TileMap* ExtractLayerAsMap(const std::string& layerName) const;
	bool ExtractAsVectorMap(std::vector<TileMap*>& map) const;
	
	bool ExtractLayerAsData(int layer,std::vector<int>& data) const;
	bool ExtractLayerAsData(const std::string& layerName,std::vector<int>& data) const;
	
		
private: 
	TMXMap*   m_map;
	VectorTileSet* m_tilesets;

};
		

#endif //end of _TMX_LOADER_