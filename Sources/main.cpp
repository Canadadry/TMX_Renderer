#include "TileMap.h"
#include "TMXLoader.hpp"
#include <SFML/Graphics.hpp>

int main (int argc, const char ** argv)
{
	std::string filename = "Zelda.tmx";
	/*
	if(argc >1) filename = argv[1];
	else return 0;
	//*/
	
	TMXLoader loader(filename);
	VectorTileMap tilemap = loader.ExtractAsVectorMap();
	sf::RenderWindow App(sf::VideoMode(640,480), "TMX_Renderer : " + filename);
	sf::View view = App.GetDefaultView();
	App.SetView(view);
	const sf::Input& Input = App.GetInput();
	float speed = 120.0;
	App.SetFramerateLimit(60);
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
		if(Input.IsKeyDown(sf::Key::Left ))	view.Move(-App.GetFrameTime()*speed, 0.0);
		if(Input.IsKeyDown(sf::Key::Right))	view.Move( App.GetFrameTime()*speed, 0.0);
		if(Input.IsKeyDown(sf::Key::Up   ))	view.Move( 0.0, -App.GetFrameTime()*speed);
		if(Input.IsKeyDown(sf::Key::Down ))	view.Move( 0.0, App.GetFrameTime()*speed);
		
		
		App.Clear();
		for (int i=0;i<tilemap.size();i++)
			tilemap[i]->renderMap(App);
		App.Display();
	}
	return 1;
}
