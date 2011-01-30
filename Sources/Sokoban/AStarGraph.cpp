/*
 *  AStarGraph.cpp
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
#include "AStarGraph.h"
#include "const.h"
#include <math.h>

AStarGraph::AStarGraph(const std::vector<int>& vec,int width,int height)
: m_data(vec)
, m_width(width)
, m_height(height)
, m_solver(new micropather::MicroPather(this,m_width*m_height,4))
{
	for(int j=0; j< m_height;j++)
	{
		for(int i=0; i< m_width;i++)
		{
			printf("%d",m_data[i+j*m_width]);
		}
		printf("\n");
	}		
	printf("\n");
}

AStarGraph::~AStarGraph()
{
	delete m_solver;
}


float AStarGraph::LeastCostEstimate( void* stateStart, void* stateEnd )
{
	int index = (int)stateStart;
	int s_y = index / m_width;
	int s_x = index - s_y * m_width;
	
	index = (int)stateEnd;
	int e_y = index / m_width;
	int e_x = index - e_y * m_width;
	
	int dx = s_x - e_x;
	int dy = s_y - e_y;
	return (float) sqrt( (double)(dx*dx) + (double)(dy*dy) );	
}

void AStarGraph::AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent )
{
	printf("ask for neightbor of ");
	PrintStateInfo(state);
	
	micropather::StateCost sc  = {NULL,0.f};
	int index = (int)state;
	int y = index / m_width;
	int x = index - y * m_width;
	
	if(x>0)
	{
		int adj = index-1;
		printf("\n testing");
		PrintStateInfo((void*) adj);

		if( (m_data[adj] == VIDE) || (m_data[adj]== OBJECTIF) )
		{
			sc.state = (void*) adj;
			sc.cost  = LeastCostEstimate(state,sc.state);
			adjacent->push_back(sc);
			printf("\n giving ");
			PrintStateInfo(sc.state);
			
		}
	}
	if(x<(m_width-1))
	{
		int adj = index+1;
		printf("\n testing");
		PrintStateInfo((void*) adj);
		
		if( (m_data[adj] == VIDE) || (m_data[adj]== OBJECTIF) )
		{
			sc.state = (void*) adj;
			sc.cost  = LeastCostEstimate(state,sc.state);
			adjacent->push_back(sc);
			printf("\n giving ");
			PrintStateInfo(sc.state);
		}
	}
	if(y>0)
	{
		int adj = index-m_width;
		printf("\n testing");
		PrintStateInfo((void*) adj);

		if( (m_data[adj] == VIDE) || (m_data[adj]== OBJECTIF) )
		{
			sc.state = (void*) adj;
			sc.cost  = LeastCostEstimate(state,sc.state);
			adjacent->push_back(sc);
			printf("\n giving ");
			PrintStateInfo(sc.state);
		}
	}
	if(y<(m_height-1))
	{
		int adj = index+m_width;
		printf("\n testing");
		PrintStateInfo((void*) adj);

		if( (m_data[adj] == VIDE) || (m_data[adj]== OBJECTIF) )
		{
			sc.state = (void*) adj;
			sc.cost  = LeastCostEstimate(state,sc.state);
			adjacent->push_back(sc);
			printf("\n giving ");
			PrintStateInfo(sc.state);
		}
	}
	printf("\n");
}

void  AStarGraph::PrintStateInfo( void* state )
{
	int index = (int)state;
	int s_y = index / m_width;
	int s_x = index - s_y * m_width;
	printf("(%d,%d)\n",s_x,s_y);
}

bool AStarGraph::Solve(sf::Vector2i start,sf::Vector2i end,std::vector<sf::Vector2i>& path)
{
	void* startState = (void*)(start.x+ start.y * m_width);
	void* endState   = (void*)(end.x  + end.y   * m_width);
	
	std::vector< void* > void_path;
	float totalCost;
	
	
	int result = m_solver->Solve( startState, endState, &void_path, &totalCost );
	if (result != micropather::MicroPather::SOLVED) return false;
	
	for (int i=0;i<(int)void_path.size();i++)
	{
		int index = (int)void_path[i];
		int s_y = index / m_width;
		int s_x = index - s_y * m_width;
		path.push_back(sf::Vector2i(s_x,s_y));
	}
	return true;
	
}

void AStarGraph::DataHaschange()
{
	for(int j=0; j< m_height;j++)
	{
		for(int i=0; i< m_width;i++)
		{
			printf("%d",m_data[i+j*m_width]);
		}
		printf("\n");
	}		
	printf("\n");
	
	
	m_solver->Reset();
}


