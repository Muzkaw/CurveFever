//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Terrain.h"

Terrain::Terrain(int const& _width, int const& _height)
{
	size = Vector2f(_width, _height) ;
	offset = Vector2f(5,5) ;
	rectangle.setOutlineColor(Color::White) ; rectangle.setSize(size - 2.f*offset) ; rectangle.setOutlineThickness(offset.x) ;
	rectangle.setFillColor(Color::Transparent) ; rectangle.setPosition(offset) ;
	delay = 10 ;
	nextDelay = randFloat(delay) ; ;
}
Vector2f Terrain::getSize() const
{
	return size-offset ;
}
Vector2f Terrain::getOffset() const
{
	return offset ;
}
vector<Bonus> Terrain::getBonus() const
{
	return bonus ;
}

void Terrain::eraseBonus(int const& i)
{
	bonus.erase(bonus.begin()+i) ;
}
void Terrain::updateBonus()
{
	if(timer.getElapsedTime().asSeconds() > nextDelay) 
	{
		bonus.push_back(Bonus(randVector2f(size-Vector2f(60,60))+Vector2f(30,30),rand()%13));
		nextDelay = randFloat(delay) ;
		timer.restart() ;
	}
}
void Terrain::setColor(Color const& color)
{
	rectangle.setOutlineColor(color) ;
}

void Terrain::draw(RenderWindow &window)
{
	window.draw(rectangle) ;
	for(int i(0) ; i < bonus.size() ; i++)
	{
		bonus[i].draw(window) ;
	}
}
