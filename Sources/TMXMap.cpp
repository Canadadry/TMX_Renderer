/*
 *  Map.cpp
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
#include "TMXMap.h"
#include <algorithm>

struct Delete 
{ 
	template <class T> void operator ()(T*& p) const 
	{ 
		delete p;
		p = NULL;
	} 
};

TMXMap::TMXMap()
: name("")
, width(0)
, height(0)
, tileWidth(0)
, tileHeight(0)
, tilesets()
, layers()
, properties()
{}

TMXMap::~TMXMap()
{
	std::for_each(layers.begin()     , layers.end()     , Delete());
	std::for_each(tilesets.begin()   , tilesets.end()   , Delete());
	std::for_each(properties.begin() , properties.end() , Delete());
}

TMXTileSet::TMXTileSet()
: firtGlobalID(1)
, name("")
, sourceFileName("")
, tileWidth(0)
, tileHeight(0)
, spacing(0)
, margin(0)
{}

TMXTileSet::~TMXTileSet()
{
}

TMXLayer::TMXLayer()
: name("")
, opacity(1.0)
, visible(1)
, data()
, properties()
{}

TMXLayer::~TMXLayer()	
{
	std::for_each(properties.begin() , properties.end() , Delete());
}

TMXProperty::TMXProperty()
: name("")
, value("")
, intValue(0)
, doubleValue(0.0)
{
}

TMXProperty::~TMXProperty()
{
}

