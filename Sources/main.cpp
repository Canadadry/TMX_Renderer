#include "TileMap.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "TMXLoader.hpp"
#include <SFML/Graphics.hpp>

int test_map(const std::string& filename)
{
	TMXLoader loader(filename);
	TileMap* tilemap = loader.ExtractAsMap();
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
		tilemap->renderMap(App,view.GetRect());
		App.Display();
	}
	return 1;
}

int test_animation(const std::string& filename)
{
	TMXLoader loader(filename);
	std::vector<Animation*> anim = loader.ExtractAsAnimation(); 
	
	
    sf::RenderWindow Window(sf::VideoMode(50, 50, 32), "Test_Animation : "+filename);
	Window.SetFramerateLimit(60);
	
    AnimatedSprite MyCharacter(anim[2], true, true);
	
    sf::Event Event;
    while (Window.IsOpened())
    {
        while (Window.GetEvent(Event))
        {
            if(Event.Type == sf::Event::Closed)
				Window.Close();
        }
		if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left ))	MyCharacter.SetAnim(anim[3]);
		if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))	MyCharacter.SetAnim(anim[1]);
		if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up   ))	MyCharacter.SetAnim(anim[0]);
		if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down ))	MyCharacter.SetAnim(anim[2]);
		
        MyCharacter.update(Window.GetFrameTime());
		Window.Clear();
        Window.Draw(MyCharacter);
        Window.Display();
    }
	
    return EXIT_SUCCESS;
	
}

int test_both(const std::string& map, const std::string& anim_name)
{
	TMXLoader loader_anim(anim_name);
	std::vector<Animation*> anim = loader_anim.ExtractAsAnimation(); 
	for(int i=0; i<anim.size();i++)
	{
		anim[i]->SetFrameTime(0.07);
	}
	AnimatedSprite MyCharacter(anim[2], true, true);
	MyCharacter.SetPosition(308,224);
	
	TMXLoader loader_map(map);
	TileMap* tilemap = loader_map.ExtractAsMap();
	sf::RenderWindow App(sf::VideoMode(640,480), "TMX_Renderer");
	sf::View map_view = App.GetDefaultView();
	sf::View anim_view = App.GetDefaultView();
	anim_view.Zoom(2.0);

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
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left ))	MyCharacter.SetAnim(anim[3]);
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))	MyCharacter.SetAnim(anim[1]);
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up   ))	MyCharacter.SetAnim(anim[0]);
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down ))	MyCharacter.SetAnim(anim[2]);
			
		}
		
		if(Input.IsKeyDown(sf::Key::Left ))	map_view.Move(-App.GetFrameTime()*speed, 0.0);
		if(Input.IsKeyDown(sf::Key::Right))	map_view.Move( App.GetFrameTime()*speed, 0.0);
		if(Input.IsKeyDown(sf::Key::Up   ))	map_view.Move( 0.0, -App.GetFrameTime()*speed);
		if(Input.IsKeyDown(sf::Key::Down ))	map_view.Move( 0.0, App.GetFrameTime()*speed);
		MyCharacter.update(App.GetFrameTime());
		
		
		App.Clear();
		App.SetView(map_view);
		tilemap->renderMap(App,map_view.GetRect());
		App.SetView(anim_view);
		App.Draw(MyCharacter);
		
		App.Display();
	}
	return 1;
	
}
int main (int argc, const char ** argv)
{
	//return test_animation("link.tmx");
	return test_map("Zelda.tmx");
	//return test_both("Zelda.tmx","link.tmx");
	return 1;
}
