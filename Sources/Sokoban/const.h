/*
 *  const.h
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

#ifndef _CONST_
#define _CONST_

#include <string>

enum SokobanTile
{
	VIDE			= 0,
	MARIO_BAS		= 1,
	MARIO_DROITE	= 2,
	MARIO_GAUCHE	= 3,
	MARIO_HAUT		= 4,
	CAISSE			= 5,
	CAISSE_OK		= 6,
	MUR				= 7,
	OBJECTIF		= 8

};

const int NUMBER_TILES = 8; //VIDE doesn't count

enum Direction
{
	BAS		= 0,
	DROITE	= 1,
	GAUCHE	= 2,
	HAUT	= 3
};

const int TILE_SIZE					= 32;
const int NB_BLOCS_LARGEUR			= 12;
const int NB_BLOCS_HAUTEUR			= 12;
const std::string LEVEL_FILENAME	= "levels.tmx";

#endif //end of _CONST_