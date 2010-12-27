/*
 *  TMXLoader.cpp
 *  TMXLoader
 *
 *  Created by mooglwy on 28/11/10.
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
#include "ImageManager.hpp"
#include "TMXLoader.hpp"
#include "InternalLoader.h"
#include "TMXMap.h"
#include "TileSet.h"
#include "TileMap.h"
#include "AnimatedSprite.h"
#include "AnimationFrame.h"
#include "Animation.h"

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
	m_tilesets = ExtractTileSets();
	return (m_map != NULL);
}

TileMap* TMXLoader::ExtractAsMap() const
{
	if(m_map==NULL) return NULL;

	TileMap* layers = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
	
	for (int i = 0; i < m_map->layers.size(); i++)
	{
		if(m_map->layers[i]->visible==1)
		{
			layers->addLayer(m_map->layers[i]->data,*m_tilesets,m_map->layers[i]->opacity);
		}
	}
	return layers;
}

TileMap* TMXLoader::ExtractLayerAsMap(int layer) const
{
	if(m_map==NULL) return NULL;
	if( (layer <0) || (layer >= m_map->layers.size())) return NULL;
	
	TileMap* layers = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
	layers->addLayer(m_map->layers[layer]->data,*m_tilesets,m_map->layers[layer]->opacity);
	
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
			layer->addLayer(m_map->layers[i]->data,*m_tilesets,m_map->layers[i]->opacity);
			return layer;
		}
	}
	return NULL;
}

std::vector<TileMap*> TMXLoader::ExtractAsSeparateMap() const
{
	if(m_map==NULL) return std::vector<TileMap*>();
	
	std::vector<TileMap*> layers;
	
	for (int i = 0; i < m_map->layers.size(); i++)
	{
		TileMap* layer = new TileMap(m_map->width,m_map->height,m_map->tileWidth,m_map->tileHeight);
		layer->addLayer(m_map->layers[i]->data,*m_tilesets,m_map->layers[i]->opacity);
		layers.push_back(layer);
	}
	return layers;
}

std::vector<Animation*> TMXLoader::ExtractAsAnimation() const
{
	if(m_map==NULL) return std::vector<Animation*>();
	
	std::vector<Animation*> tabAnim;
	for (int l=0;l<m_map->layers.size();l++)
	{
		for (int i=0;i<m_map->height;i++)
		{
			Animation* anim = new Animation;
			for (int j = 0; j < m_map->width; j++)
			{
				int id = m_map->layers[l]->data[m_map->width*i+j];
				if (id==0) break;
				int tileset = m_tilesets->getTileSetFromID(id);
				anim->PushFrame(AnimationFrame((*m_tilesets)[tileset]->getImage(),(*m_tilesets)[tileset]->getRectOfTile(id)));
			}
			if (anim->Size() == 0) delete anim;
			else
			{
				PRINT("Found anim\n");
				for(int p=0;p<m_map->layers[l]->properties.size();p++)
				{
					PRINT("Property found : name:%s value:%s\n",m_map->layers[l]->properties[p]->name.c_str(),m_map->layers[l]->properties[p]->value.c_str());
					if(m_map->layers[l]->properties[p]->name == "speed")
					{
						PRINT("Found speed %lf\n",m_map->layers[l]->properties[p]->doubleValue);
						anim->SetFrameTime(m_map->layers[l]->properties[p]->doubleValue);
					}
				}
				tabAnim.push_back(anim);
			}
		}
	}
	return tabAnim;
}

std::vector<Animation*> TMXLoader::ExtractLayerAsAnimation(int layer) const
{
	if(m_map==NULL) return std::vector<Animation*>();
	if( (layer <0) || (layer >= m_map->layers.size())) return std::vector<Animation*>();

	std::vector<Animation*> tabAnim;
	for (int i=0;i<m_map->height;i++)
	{
		Animation* anim = new Animation;
		for (int j = 0; j < m_map->width; j++)
		{
			int id = m_map->layers[layer]->data[m_map->width*i+j];
			if (id==0) break;
			int tileset = m_tilesets->getTileSetFromID(id);
			anim->PushFrame(AnimationFrame((*m_tilesets)[tileset]->getImage(),(*m_tilesets)[tileset]->getRectOfTile(id)));
		}
		if (anim->Size() == 0) delete anim;
		else tabAnim.push_back(anim);
	}
	return tabAnim;
}

std::vector<Animation*> TMXLoader::ExtractLayerAsAnimation(const std::string& layerName) const
{
	if(m_map==NULL) return std::vector<Animation*>();
	
	std::vector<Animation*> tabAnim;
	for (int l=0;l<m_map->layers.size();l++)
	{
		for (int i=0;i<m_map->height;i++)
		{
			if(std::string(m_map->layers[l]->name)==layerName)
			{
				Animation* anim = new Animation;
				for (int j = 0; j < m_map->width; j++)
				{
					int id = m_map->layers[l]->data[m_map->width*i+j];
					if (id==0) break;
					int tileset = m_tilesets->getTileSetFromID(id);
					anim->PushFrame(AnimationFrame((*m_tilesets)[tileset]->getImage(),(*m_tilesets)[tileset]->getRectOfTile(id)));
				}
				if (anim->Size() == 0) delete anim;
				else tabAnim.push_back(anim);
			}
		}
	}
	return tabAnim;
}

TileSets* TMXLoader::ExtractTileSets() const
{
	if(m_map==NULL) return NULL;

	TileSets* tilesets = new TileSets;
	for (int i = 0; i < m_map->tilesets.size(); i++)
	{
		TileSet* tileset = new TileSet();
		sf::Image* img = ImageManager::GetImage(m_map->tilesets[i]->sourceFileName);
		if(img != NULL)
		{
			tileset->loadTileSet(img,
								 m_map->tilesets[i]->firtGlobalID,
								 m_map->tilesets[i]->tileWidth,
								 m_map->tilesets[i]->tileHeight);
			
			tilesets->push_back(tileset);
		}
		else 
		{
			delete tileset;
		}
	}
	return tilesets;
}


