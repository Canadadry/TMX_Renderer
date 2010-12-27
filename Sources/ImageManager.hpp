#ifndef _IMAGEMANAGER_
#define _IMAGEMANAGER_

#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>


class ImageManager
	{
	private:
		static ImageManager* instance;
		static std::map<std::string, sf::Image*> Images;
		static bool SearchImage(const std::string &ImageLink, sf::Image* &ImgTemp);
		static sf::Image *CreateImage(const std::string &ImageLink);

		ImageManager();
		~ImageManager();

	public:


		static sf::Image* GetImage(const std::string &ImageLink);
		static void DeleteImage(sf::Image &Img);
		static void DeleteImage(const std::string& ImageLink);
		static void Init();
		static void Destroy();
	};


#endif

