//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <stdlib.h>
#include <time.h>  

using namespace std ;
using namespace sf ;

class Bonus
{
public:
	Bonus(Vector2f const& _position, int const& _type);
	
	Vector2f getPosition() const ;
	float getRadius() const ;
	int getType() const ;
	float getDelay() const ;

	void startTimer() ;
	bool isEnded() const ;

	void draw(RenderWindow &window) ;

private:
	Image image ;
	Texture texture ;
	Sprite sprite ;
	float radius ;
	int type ;
	float delay ;
	Clock timer ;
};

