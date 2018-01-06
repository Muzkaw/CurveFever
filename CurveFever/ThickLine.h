//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utility.h"

using namespace std ;
using namespace sf ;

class ThickLine 
{
public:
	ThickLine();
	ThickLine(float const& _thickness, Color const& _color);

	void addPoint(Vector2f const& p) ;
	
	void setThickness(float const& _thickness) ;
	void clear() ;
	
	vector<Vector2f> getLine() const ;
	int getSize() const ;

	void draw(RenderWindow &window) ;
	void drawLine(RenderWindow &window) ;
private:
	float thickness ;
	vector<Vector2f> line ;
	VertexArray VA ;
	VertexArray lineVA ;

	Color color ;
};

