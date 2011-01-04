#include "TileMap.h"
#include "TMXLoader.hpp"
#include <SFML/Graphics.hpp>

int main (int argc, const char ** argv)
{
	std::string filename = "levels.tmx";
	TMXLoader loader;
	if(!loader.LoadFromFile(filename)) return 0;
	TileMap* tilemap = loader.ExtractLayerAsMap(0);
	sf::RenderWindow App(sf::VideoMode(tilemap->getWidth()*tilemap->getTileWidth(),
									   tilemap->getHeight()*tilemap->getTileHeight()),
						"Sokoban");
	sf::View view = App.GetDefaultView();
	App.SetView(view);

	App.SetFramerateLimit(20);
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
		App.Clear(sf::Color::White);
		tilemap->renderMap(App);
		App.Display();
	}
	return 1;
}
