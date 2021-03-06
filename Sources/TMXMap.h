/*
 *  TMXMap.h
 *  TMX_Renderer
 *
 *  Created by mooglwy on 18/12/10.
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

#ifndef _TMXMap_H_
#define _TMXMap_H_

#include <vector>
#include <string>

class TMXTileSet;
class TMXLayer;
class TMXProperty;

class TMXMap
{
public:
	TMXMap();
	~TMXMap();
	
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	std::vector<TMXTileSet*> tilesets;
	std::vector<TMXLayer*>   layers;
	std::vector<TMXProperty*> properties;
};

class TMXTileSet
{
public:
	TMXTileSet();
	~TMXTileSet();
	
	int firtGlobalID;
	std::string name;
	std::string sourceFileName;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
};

class TMXLayer
{
public:
	TMXLayer();
	~TMXLayer();
	std::string name;
	float opacity;
	int  visible;
	std::vector<int> data;
	std::vector<TMXProperty*> properties;
};

class TMXProperty
{
public:
	TMXProperty();
	~TMXProperty();
	std::string name;
	std::string value;
	int intValue;
	double doubleValue;
};

#endif //end of TMXMap
