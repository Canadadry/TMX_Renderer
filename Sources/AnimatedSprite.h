/*
 *  AnimatedSprite.h
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

#ifndef _AnimatedSprite_H_
#define _AnimatedSprite_H_

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimationFrame.h"

class AnimatedSprite : public sf::Sprite
{
public:
	AnimatedSprite(bool Play = false, bool Loop = true);
	AnimatedSprite(Animation* NewAnim, bool Play = false, bool Loop = true);
	AnimatedSprite(const AnimatedSprite& Cpy);

	void SetAnim(Animation* NewAnim);
	Animation* GetAnim();

	void SetFrame(int Frame);
	int GetCurrentFrame();
	
	void SetLoop(bool Loop);
	bool IsLoop();

	void Pause();
	void Play();
	void Stop();

	bool IsPaused();
	bool IsStoped();
	void update(float ElapsedTime);
	
private:
	float myElapsedTime;
    bool Paused;
    bool myLoop;
	Animation* myAnim;
	int myCurrentFrame;
};

#endif //end of AnimatedSprite
