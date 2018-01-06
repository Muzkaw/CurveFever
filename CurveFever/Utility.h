//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>  

#define PI 3.14159265359

using namespace std ;
using namespace sf ;

float Norm(Vector2f const& v) ;
float Distance(Vector2f const& u, Vector2f const& v) ;
Vector2f randVector2f(float const& among) ;
Vector2f randVector2f(Vector2f const& among) ;
float randFloat(float const& among) ;
Color randColor() ;
void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color) ;
void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color) ;
