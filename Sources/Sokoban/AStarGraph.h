/*
 *  AStarGraph.h
 *  TMX_Renderer
 *
 *  Created by mooglwy on 21/01/11.
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

#ifndef _AStarGraph_H_
#define _AStarGraph_H_

#include "micropather.h"
#include <vector>
#include <SFML/System/Vector2.hpp>


class AStarGraph : public micropather::Graph
{
public:
	AStarGraph(const std::vector<int>& vec,int width,int height);
	~AStarGraph();

	float LeastCostEstimate( void* stateStart, void* stateEnd );
	void AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent );
	void PrintStateInfo( void* state );
	bool Solve(sf::Vector2i start,sf::Vector2i end,std::vector<sf::Vector2i>& path);
	void DataHaschange();
	
private:
	const std::vector<int>& m_data;
	const int m_width;
	const int m_height;
	
	micropather::MicroPather* m_solver;

	sf::Vector2i stateToPosition(void*        state) const;
	void*        positionToState(sf::Vector2i pos  ) const;

};

#endif //end of AStarGraph
