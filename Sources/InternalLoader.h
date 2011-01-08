/*
 *  InternalLoader.h
 *  TMX_Renderer
 *
 *  Created by Canadadry on 18/12/10.
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

#ifndef _InternalLoader_H_
#define _InternalLoader_H_

#include <string>
#include <vector>
#include "TMXMap.h"

	class TiXmlNode;

	class InternalLoader 
	{
	public:
		InternalLoader(std::string filename = "");	
		void LoadFromFile(std::string filename);
		TMXMap* m_map;
		
	private:
		void readMap(TiXmlNode* node);
		void readProperties(TiXmlNode* node, std::vector<TMXProperty*>& porperties);
		TMXTileSet* readTileSet(TiXmlNode* node);
		const char* readImage(TiXmlNode* node);
		TMXLayer* readLayer(TiXmlNode* node);
		void readData(TiXmlNode* node, std::vector<int>& data);
		void readXML(TiXmlNode* node,std::vector<int>& data);
		void readCSV(TiXmlNode* node,std::vector<int>& data);
		void decodeblock( unsigned char* in, unsigned char* out );
		void readBase64(TiXmlNode* node,const char* compression,std::vector<int>& data);
	};	

#endif //end of InternalLoader
