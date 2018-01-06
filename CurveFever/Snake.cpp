//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Snake.h"

Snake::Snake(Vector2f const& _position, Vector2f const& _forward, Color const& _color, Terrain *_terrain, Keyboard::Key const& _leftKey, Keyboard::Key const& _rightKey)
{
	size=3 ;
	color = _color ;
	position = _position ;
	forward = _forward ;
	speed = 100 ;
	turnSpeed = 3 ;

	lines.push_back(ThickLine(size,color)) ;
	lines[lines.size()-1].addPoint(position) ;

	startCircle.setFillColor(color) ; startCircle.setOrigin(size,size) ; startCircle.setRadius(size) ; startCircle.setPosition(position) ;
	endCircle.setFillColor(color) ; endCircle.setOrigin(size,size) ; endCircle.setRadius(size) ; endCircle.setPosition(position) ;
	dx = 3 ;

	left = false ;
	right = false ;
	alive = true ;
	lineTimerEnd = false ;
	startTimeEnd = false ;
	noWall = false ;
	noLine = false ;

	gap = size/speed*10 ;
	delay = 3 ;
	nextDelay = randFloat(delay) ;

	terrain = _terrain ;

	leftKey = _leftKey ;
	rightKey = _rightKey ;
}
Snake::~Snake()
{
	terrain = 0 ;
	for(int i(0) ; i < enemy.size() ; i++)
	{
		enemy[i]=0 ;
	}
}

void Snake::setSize(float const& _size)
{
	size = _size ;
	endCircle.setRadius(size) ;
	endCircle.setOrigin(size,size) ;
	lines[lines.size()-1].setThickness(size) ;
}
void Snake::setSpeed(float const& _speed)
{
	speed = _speed ;
	turnSpeed = speed/33.333f ;
}
void Snake::reverseKeys()
{
	Keyboard::Key buffer = leftKey ;
	leftKey = rightKey ;
	rightKey = buffer ;
}
void Snake::lineOff()
{
	noLine = true ;
}
void Snake::lineOn()
{
	noLine = false ;
	lines.push_back(ThickLine(size,color)) ;
	lines[lines.size()-1].addPoint(position) ;
}
void Snake::wallOff()
{
	noWall = true ;
	terrain->setColor(Color::Color(50,50,50)) ;
}
void Snake::wallOn()
{
	noWall = false ;
	terrain->setColor(Color::White) ;
}
void Snake::eraseLine()
{
	for(int i(0) ; i < lines.size() ; i++)
	{
		lines[i].clear() ;
	}
	lines.resize(0) ;
	lines.push_back(ThickLine(size,color)) ;
	lines[lines.size()-1].addPoint(position) ;
	startCircle.setPosition(position) ;
}

vector<ThickLine> Snake::getLines() const
{
	return lines ;
}
float Snake::getSpeed() const
{
	return speed ;
}
float Snake::getSize() const
{
	return size ;
}
int Snake::getLinesSize() const
{
	return lines.size() ;
}

void Snake::addEnemy(Snake *_enemy)
{
	enemy.push_back(_enemy) ;
}

void Snake::checkSelfCollision()
{
	if(!noLine)
	{
		for(int l(0) ; l < lines.size() ; l++)
		{
			for(int i(1) ; i < lines[l].getLine().size()-1 ; i++)
			{
				if(Distance(position,lines[l].getLine()[i])<2*size &&
				!(l==lines.size()-1 && (i>lines[l].getLine().size()-size/speed*1000 || lines[l].getLine().size() < size/speed*1000)))
				{
					alive = false ;
				}
			}
		}
	}
}
void Snake::checkWallCollision()
{
	if(noWall)
	{
		if(position.x-size<terrain->getOffset().x)
		{
			position = position + Vector2f(terrain->getSize().x,0) ;
			lines.push_back(ThickLine(size,color)) ;
			lines[lines.size()-1].addPoint(position) ;
		}
		else if(position.x+size>terrain->getSize().x)
		{
			position = position - Vector2f(terrain->getSize().x,0) ;
			lines.push_back(ThickLine(size,color)) ;
			lines[lines.size()-1].addPoint(position) ;
		}
		else if(position.y-size < terrain->getOffset().y) 
		{
			position = position + Vector2f(0,terrain->getSize().y) ;
			lines.push_back(ThickLine(size,color)) ;
			lines[lines.size()-1].addPoint(position) ;
		}
		else if(position.y+size>terrain->getSize().y)
		{
			position = position - Vector2f(0,terrain->getSize().y) ;
			lines.push_back(ThickLine(size,color)) ;
			lines[lines.size()-1].addPoint(position) ;
		}
	}
	else if(position.x-size<terrain->getOffset().x || position.x+size>terrain->getSize().x || position.y-size < terrain->getOffset().y || position.y+size>terrain->getSize().y)
	{
		if(!noWall)
			alive = false ;
	}
}
void Snake::checkEnemyCollision()
{
	if(!noLine)
	{
		ThickLine a ;

		for(int e(0) ; e < enemy.size() ; e++)
		{
			for(int l(0) ; l < enemy[e]->getLinesSize() ; l++)
			{
				a = enemy[e]->getLines()[l] ;

				for(int i(1) ; i < a.getSize()-1 ; i++)
				{
					if(Distance(position,a.getLine()[i])<2*size)
					{
						alive = false ;
					}
				}
			}
		}
	}
}
void Snake::updateBonusCollision()
{
	vector<Bonus> bonus = terrain->getBonus() ;
	for(int i(0) ; i < bonus.size() ; i++)
	{
		if(Distance(position, bonus[i].getPosition()) < bonus[i].getRadius() + size)
		{
			switch(bonus[i].getType())
			{
			case 0 : { setSpeed(2*speed) ; break ; }
			case 1 : { setSpeed(speed/2) ; break ; }
			case 2 : { setSize(size*2) ; break ; }
			case 3 : { setSize(size/2) ; break ; }
			case 4 : { lineOff() ; break ; }
			case 5 : { wallOff() ; break ; }

			case 6 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSpeed(2*enemy[i]->getSpeed()) ;	break ; }	
			case 7 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSpeed(enemy[i]->getSpeed()/2) ;	break ; }	
			case 8 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSize(2*enemy[i]->getSize()) ; break ; }
			case 9 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSize(enemy[i]->getSize()/2) ; break ; }
			case 10 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->reverseKeys() ; break ; }

			case 11 : { wallOff() ;	for(int i(0) ; i < enemy.size() ; i++) enemy[i]->wallOff() ; break ; }
			case 12 : { eraseLine() ; for(int i(0) ; i < enemy.size() ; i++) enemy[i]->eraseLine() ; break ; }
			}			
			bonus[i].startTimer() ;
			if(bonus[i].getType() != 12)
				bonusStack.push_back(bonus[i]) ;
			terrain->eraseBonus(i) ;
		}
	}
	for(int i(0) ; i < bonusStack.size() ; i++)
	{
		if(bonusStack[i].isEnded())
		{
			switch(bonusStack[i].getType())
			{
			case 0 : { setSpeed(speed/2) ; break ; }
			case 1 : { setSpeed(speed*2) ; break ; }
			case 2 : { setSize(size/2) ; break ; }
			case 3 : { setSize(size*2) ; break ; }
			case 4 : { lineOn() ; break ; }
			case 5 : { wallOn() ; break ; }

			case 6 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSpeed(enemy[i]->getSpeed()/2) ;	break ; }	
			case 7 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSpeed(enemy[i]->getSpeed()*2) ;	break ; }	
			case 8 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSize(enemy[i]->getSize()/2) ; break ; }
			case 9 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->setSize(enemy[i]->getSize()*2) ; break ; }
			case 10 : { for(int i(0) ; i < enemy.size() ; i++) enemy[i]->reverseKeys() ; break ; }

			case 11 : { wallOn() ;	for(int i(0) ; i < enemy.size() ; i++) enemy[i]->wallOn() ; break ; }
			}
		
			bonusStack.erase(bonusStack.begin()+i) ;
		}
	}
}
void Snake::startCollision()
{
	if(startTime.getElapsedTime().asSeconds()<2)
	{
		lineOff() ;
		startCircle.setPosition(position) ;
	}
	else if(!startTimeEnd && startTime.getElapsedTime().asSeconds()>2) 
	{
		lineOn() ;
		startTimeEnd = true ;
	}
}
void Snake::control(float const& dt)
{
	left = Keyboard::isKeyPressed(leftKey) ;
	right = Keyboard::isKeyPressed(rightKey) ;

	if(left) forward += Vector2f(forward.y, -forward.x)*turnSpeed*dt ;
	if(right) forward -= Vector2f(forward.y, -forward.x)*turnSpeed*dt ;

	forward /= Norm(forward) ;
		
	if(alive)
		position += forward*speed*dt ;
	endCircle.setPosition(position) ;
}
void Snake::update(float const& dt)
{
	startCollision() ;

	control(dt) ;

	checkSelfCollision() ;
	checkEnemyCollision() ;
	checkWallCollision() ;
	updateBonusCollision() ;

	gap = size/speed*7 ;

	if(lineTimer.getElapsedTime().asSeconds()<nextDelay && 
		Distance(lines[lines.size()-1].getLine()[lines[lines.size()-1].getLine().size()-1],position)>dx &&
		!noLine)
	{
		lines[lines.size()-1].addPoint(position) ;
	}
	else if(lineTimer.getElapsedTime().asSeconds()>=nextDelay && !lineTimerEnd && !noLine)
	{
		lineTimerEnd = true ;
		lines[lines.size()-1].addPoint(position+forward*size) ;
	}
	else if(lineTimer.getElapsedTime().asSeconds()>nextDelay+gap && !noLine)
	{
		lines.push_back(ThickLine(size,color)) ;
		lines[lines.size()-1].addPoint(position-forward*size) ;
		lines[lines.size()-1].addPoint(position) ;
		lineTimer.restart() ;
		nextDelay = randFloat(delay) ;
		lineTimerEnd = false ;
	}
}
void Snake::draw(RenderWindow &window)
{
	window.draw(startCircle) ;
	window.draw(endCircle) ;
	for(int i(0) ; i < lines.size() ; i++)
	{
		lines[i].draw(window) ;
	}
}