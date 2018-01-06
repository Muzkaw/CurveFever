//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Bonus.h"
#include <stdlib.h>
#include <time.h>  

using namespace std ;
using namespace sf ;

class Terrain
{
public:
	Terrain(int const& _width, int const& _height);

	Vector2f getSize() const ;
	Vector2f getOffset() const ;
	vector<Bonus> getBonus() const ;

	void eraseBonus(int const& i) ;
	void updateBonus() ;
	void setColor(Color const& color) ;

	void draw(RenderWindow &window) ;

private:
	Vector2f size ;
	Vector2f offset ;
	RectangleShape rectangle ;
	vector<Bonus> bonus ;

	float delay ;
	float nextDelay ;
	Clock timer ;
};

