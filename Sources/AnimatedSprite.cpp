/*
 *  AnimatedSprite.cpp
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
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const AnimatedSprite& Cpy)
: sf::Sprite(Cpy)
, myElapsedTime(Cpy.myElapsedTime)
, Paused(Cpy.Paused)
, myLoop(Cpy.myLoop)
, myAnim(Cpy.myAnim)
, myCurrentFrame(Cpy.myCurrentFrame)
{}

AnimatedSprite::AnimatedSprite(bool Play, bool Loop)
: sf::Sprite()
, myElapsedTime(0.f)
, Paused(!Play)
, myLoop(Loop)
, myAnim(NULL)
, myCurrentFrame(0)
{}

AnimatedSprite::AnimatedSprite(Animation* NewAnim, bool Play, bool Loop)
: sf::Sprite()
, myElapsedTime(NewAnim->GetFrameTime())
, Paused(!Play)
, myLoop(Loop)
, myAnim(NewAnim)
, myCurrentFrame(0)
{
	SetFrame(0);
}

void AnimatedSprite::SetAnim(Animation* NewAnim)
{
	if( myAnim == NewAnim) return;
    myAnim = NewAnim;
	myElapsedTime = NewAnim->GetFrameTime();
	
    SetFrame(0);
}

Animation* AnimatedSprite::GetAnim()
{
    return myAnim;
}

void AnimatedSprite::SetFrame(int Frame)
{
    if ( myAnim != NULL)
    {
        if (myAnim->Size() > 0)
        {
            if ((*myAnim)[Frame].myImage != NULL)
                SetImage(*((*myAnim)[Frame].myImage));
			
            SetSubRect((*myAnim)[Frame].myRect);
			
            SetColor((*myAnim)[Frame].myColor);
			
            myCurrentFrame = Frame;
        }
    }
}

int AnimatedSprite::GetCurrentFrame()
{
    return myCurrentFrame;
}

void AnimatedSprite::SetLoop(bool Loop)
{
    myLoop = Loop;
}

bool AnimatedSprite::IsLoop()
{
    return myLoop;
}

void AnimatedSprite::Pause()
{
    Paused = true;
}

void AnimatedSprite::Play()
{
    Paused = false;
}

void AnimatedSprite::Stop()
{
    SetFrame(0);
    myElapsedTime = myAnim->GetFrameTime();
    Paused = true;
}

bool AnimatedSprite::IsPaused()
{
    return Paused;
}

bool AnimatedSprite::IsStoped()
{
    return (Paused && (myCurrentFrame == 0) && (myElapsedTime == myAnim->GetFrameTime()));
}

void AnimatedSprite::update(float ElapsedTime)
{
    if (!Paused && myAnim != NULL)
    {
        myElapsedTime -= ElapsedTime;
        if (myElapsedTime <= 0.f)
        {
            myElapsedTime = myAnim->GetFrameTime();
            if (myCurrentFrame + 1 < myAnim->Size())
                myCurrentFrame++;
            else
            {
                if (myLoop)
                    myCurrentFrame = 0;
                else
                {
                    Stop();
                }
            }
			
            SetFrame(myCurrentFrame);
        }
    }
}