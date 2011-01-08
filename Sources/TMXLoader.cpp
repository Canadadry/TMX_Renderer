/*
 *  TMXLoader.cpp
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
#include "TMXLoader.hpp"
#include "InternalLoader.h"
#include "TMXMap.h"
#include "TileSet.h"
#include "TileMap.h"
#include <SFML/Graphics/Image.hpp>

#include <algorithm>
#include <iostream>
#include <memory>

//#define _LOG_
#ifdef _LOG_
#include <iostream>
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

TMXLoader::TMXLoader(const std::string& filename)
: m_map(0)
, m_tilesets(0)
{
	if (filename != "")
	{
		LoadFromFile(filename);
	}
}

TMXLoader::~TMXLoader()
{
	delete m_map;
	delete m_tilesets;
}

bool TMXLoader::LoadFromFile(const std::string& filename)
{
	InternalLoader private_loader(filename);
	m_map = private_loader.m_map;
	m_tilesets = new VectorTileSet;
	if(ExtractVectorTileSet(*m_tilesets)==false) return false;
	return (m_map != NULL);
}

TileMap* TMXLoader::ExtractLayerAsMap(int layer) const
{
	if(m_map==NULL) return NULL;
	if( (layer <0) || (layer >= m_map->layers.size())) return NULL;
	
	TileMap* layers = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
	layers->setLayer(m_map->layers[layer]->data,*m_tilesets,m_map->layers[layer]->opacity);
	
	return layers;
}

TileMap* TMXLoader::ExtractLayerAsMap(const std::string& layerName) const
{
	if(m_map==NULL) return NULL;
	
	for (int i = 0; i < m_map->layers.size(); i++)
	{
		if(std::string(m_map->layers[i]->name)==layerName)
		{
			TileMap* layer = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
			layer->setLayer(m_map->layers[i]->data,*m_tilesets,m_map->layers[i]->opacity);
			return layer;
		}
	}
	return NULL;
}

bool TMXLoader::ExtractAsVectorMap(std::vector<TileMap*>& map) const
{
	if(m_map==NULL) return false;
	if(m_map->layers.size()<=0) return false;
	
	
	for (int i = 0; i < m_map->layers.size(); i++)
	{
		TileMap* layer = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
		layer->setLayer(m_map->layers[i]->data,*m_tilesets,m_map->layers[i]->opacity);
		map.push_back(layer);
	}
	return true;
}

int TMXLoader::getNbLayer() const
{
	if(m_map==NULL) return 0;
	return m_map->layers.size();
}

int  TMXLoader::getWidth() const
{
	if(m_map==NULL) return 0;
	return m_map->width;
}

int  TMXLoader::getHeight() const
{
	if(m_map==NULL) return 0;
	return m_map->height;
}

int  TMXLoader::getTileWidth() const
{
	if(m_map==NULL) return 0;
	return m_map->tileWidth;
}

int  TMXLoader::getTileHeight() const
{
	if(m_map==NULL) return 0;
	return m_map->tileHeight;
}

bool TMXLoader::ExtractLayerAsData(int layer,std::vector<int>& data) const
{
	if(m_map==NULL) return false;
	if( (layer <0) || (layer >= m_map->layers.size())) return false;
	data =  m_map->layers[layer]->data;
	return true;
}

bool TMXLoader::ExtractLayerAsData(const std::string& layerName,std::vector<int>& data) const
{
	if(m_map==NULL) return false;
	
	for (int i = 0; i < m_map->layers.size(); i++)
	{
		if(std::string(m_map->layers[i]->name)==layerName)
		{
			data =  m_map->layers[i]->data;
			return true;
		}
	}
	return false;
}


int TMXLoader::ExtractVectorTileSet(VectorTileSet& tilesets) const
{
	if(m_map==NULL) return 0;
	if(m_map->tilesets.size()<=0) return 0; 
	
	int tileset_load = 0;
	for (int i = 0; i < m_map->tilesets.size(); i++)
	{
		TileSet* tileset = new TileSet();
		sf::Image* img = new sf::Image;
		if(img->LoadFromFile(m_map->tilesets[i]->sourceFileName)==true)
		{
			img->SetSmooth(false);
			tileset->loadTileSet(img,
								 m_map->tilesets[i]->firtGlobalID,
								 m_map->tilesets[i]->tileWidth,
								 m_map->tilesets[i]->tileHeight);
			
			tilesets.push_back(tileset);
			tileset_load ++;
		}
		else 
		{
			delete img;
			delete tileset;
		}
	}
	return tileset_load;
}


