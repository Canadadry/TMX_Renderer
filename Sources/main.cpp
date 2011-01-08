#include "const.h"
#include "Sokoban.h"
#include <SFML/Graphics.hpp>

int main (int argc, const char ** argv)
{
	std::string filename = "levels.tmx";
	Sokoban skbn;
	if(!skbn.loadLevels(filename)) return 0;
	
	sf::RenderWindow App(sf::VideoMode(NB_BLOCS_LARGEUR*TILE_SIZE,NB_BLOCS_LARGEUR*TILE_SIZE),"Sokoban");
	App.SetFramerateLimit(20);
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			skbn.handleEvent(Event);
		}
		skbn.update(0);
		App.Clear(sf::Color::White);
		skbn.render(App);
		App.Display();
	}
	return 1;
}
