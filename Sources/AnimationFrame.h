/*
 *  AnimationFrame.h
 *  TMX_Animation
 *
 *  Created by mooglwy on 18/12/10.
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

#ifndef _AnimationFrame_H_
#define _AnimationFrame_H_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>


namespace sf 
{
	class Image;
	class Color;
}

class AnimationFrame
{
public:
	AnimationFrame(const sf::Color& NewColor = sf::Color::White);
	AnimationFrame(const AnimationFrame& Cpy);
	AnimationFrame(sf::Image* NewImage, const sf::Rect<int>& NewRect, const sf::Color& NewColor = sf::Color::White);
	AnimationFrame(sf::Image* NewImage, const sf::Color& NewColor = sf::Color::White);

	virtual ~AnimationFrame();
	
	sf::Image* myImage;
	sf::Rect<int> myRect;
	sf::Color myColor;
};
	

#endif //end of AnimationFrame
