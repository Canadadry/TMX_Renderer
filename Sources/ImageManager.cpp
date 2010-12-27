#include "ImageManager.hpp"


ImageManager* ImageManager::instance=NULL;
std::map<std::string, sf::Image*> ImageManager::Images;


void ImageManager::Init()
{
	if(!ImageManager::instance)
	{
		ImageManager::instance=new ImageManager;
	}
}

void ImageManager::Destroy()
{
	if(ImageManager::instance!=NULL)
	{
		delete ImageManager::instance;
		ImageManager::instance=NULL;
	}
}

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	//On détruit toutes les images restantes
	std::map<std::string, sf::Image*>::iterator it;
	for(it = Images.begin(); it != Images.end(); it++)
	{
		delete it->second;
		Images.erase(it);
	}
}

bool ImageManager::SearchImage(const std::string &ImageLink, sf::Image* &ImgTemp)
{
	
	std::map<std::string, sf::Image*>::iterator it;

	it = Images.find(ImageLink);

	if(it == Images.end())
	{
		return false;
	}
	else
	{
		ImgTemp = it->second;
	}

	return true;
}

sf::Image *ImageManager::CreateImage(const std::string &ImageLink)
{
	sf::Image *ImgTemp = new sf::Image();
	if(ImgTemp->LoadFromFile(ImageLink))
	{
		ImgTemp->SetSmooth(false);
		Images.insert(std::pair<std::string, sf::Image*>(ImageLink, ImgTemp));
		return ImgTemp;
	}

	delete ImgTemp;
	return NULL;
}

sf::Image *ImageManager::GetImage(const std::string &ImageLink)
{
	Init();
	sf::Image *ImgTemp;

	//Si l'image demandée n'existe pas déjà, on la créée
	if(!SearchImage(ImageLink, ImgTemp))
	{
		ImgTemp = CreateImage(ImageLink);
	}

	return ImgTemp;
}

void ImageManager::DeleteImage(sf::Image &Img)
{
	Init();
	std::map<std::string, sf::Image*>::iterator it;

	//On cherche l'image demandée
	for(it = Images.begin(); it != Images.end(); it++)
	{
		//Si on la trouve, on la détruit et on la retire
		if(it->second == &Img)
		{
			delete &Img;
			Images.erase(it);
			break;
		}
	}
}

void ImageManager::DeleteImage(const std::string& ImageLink)
{
	Init();
	std::map<std::string, sf::Image*>::iterator it;
	it = Images.find(ImageLink);

	if(it != Images.end())
	{
		if(it->second != NULL)
		{
			delete (it->second);
			Images.erase(it);
		}
	}
}


