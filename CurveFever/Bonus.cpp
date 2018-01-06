//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Bonus.h"

Bonus::Bonus(Vector2f const& _position, int const& _type)
{
	radius = 25 ; sprite.setOrigin(2*radius, 2*radius) ; 
	sprite.setPosition(_position) ;
	type = _type ;
	
	if(type==0) image.loadFromFile("Resource/speed+.png") ;
	if(type==1) image.loadFromFile("Resource/speed-.png") ;
	if(type==2) image.loadFromFile("Resource/size+.png") ;
	if(type==3) image.loadFromFile("Resource/size-.png") ;
	if(type==4) image.loadFromFile("Resource/through.png") ;
	if(type==5) image.loadFromFile("Resource/wall.png") ;
	if(type==6) image.loadFromFile("Resource/speed+2.png") ;
	if(type==7) image.loadFromFile("Resource/speed-2.png") ;
	if(type==8) image.loadFromFile("Resource/size+2.png") ;
	if(type==9) image.loadFromFile("Resource/size-2.png") ;
	if(type==10) image.loadFromFile("Resource/reverse.png") ;
	if(type==11) image.loadFromFile("Resource/wall2.png") ;
	if(type==12) image.loadFromFile("Resource/erase.png") ;
	
	texture.loadFromImage(image) ;
	sprite.setTexture(texture) ;
	sprite.setScale(0.5f,0.5f) ;

	delay = 5 ;
}

Vector2f Bonus::getPosition() const
{
	return sprite.getPosition() ;
}
float Bonus::getRadius() const
{
	return radius ;
}
int Bonus::getType() const
{
	return type ;
}
float Bonus::getDelay() const
{
	return delay ;
}

void Bonus::startTimer()
{
	timer.restart() ;
}
bool Bonus::isEnded() const
{
	if(timer.getElapsedTime().asSeconds()>delay)
		return true ;
	else return false ;
}

void Bonus::draw(RenderWindow &window)
{
	sprite.setTexture(texture);
	window.draw(sprite) ;
}
