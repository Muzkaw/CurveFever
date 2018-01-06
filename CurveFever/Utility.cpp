//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Utility.h"

float Norm(Vector2f const& v)
{
	return sqrt(pow(v.x,2)+pow(v.y,2)) ;
}
float Distance(Vector2f const& u, Vector2f const& v)
{
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)) ;
}
Vector2f randVector2f(float const& among)
{
	return Vector2f(rand()%RAND_MAX/(float)RAND_MAX*among,rand()%RAND_MAX/(float)RAND_MAX*among) ; 
}
Vector2f randVector2f(Vector2f const& among)
{
	return Vector2f(rand()%RAND_MAX/(float)RAND_MAX*among.x,rand()%RAND_MAX/(float)RAND_MAX*among.y) ; 
}
float randFloat(float const& among)
{
	return rand()%RAND_MAX/(float)RAND_MAX*among ; 
}
Color randColor()
{
	return Color::Color(rand()%RAND_MAX/(float)RAND_MAX*255,rand()%RAND_MAX/(float)RAND_MAX*255,rand()%RAND_MAX/(float)RAND_MAX*255) ;
}

void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color)
{
	VertexArray lines(Lines, 2) ;
	lines[0].position = pos ;
	lines[0].color = color ;
	lines[1].position = dir+pos ;
	lines[1].color = color ;
	window.draw(lines) ;
}

void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color)
{
	CircleShape c(radius) ;
	c.setFillColor(color) ;
	c.setPosition(p) ;
	c.setOrigin(radius,radius) ;
	window.draw(c) ;
}

