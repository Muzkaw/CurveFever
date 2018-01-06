//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "ThickLine.h"
#include "Terrain.h"
#include <stdlib.h>
#include <time.h>  

using namespace std ;
using namespace sf ;

class Snake
{
public:
	Snake(Vector2f const& _position, Vector2f const& _forward, Color const& _color, Terrain *_terrain, Keyboard::Key const& _leftKey, Keyboard::Key const& _rightKey);
	~Snake() ;

	void setSize(float const& _size) ;
	void setSpeed(float const& _speed) ;
	void reverseKeys() ;
	void lineOff() ;
	void lineOn() ;
	void wallOff() ;
	void wallOn() ;
	void eraseLine() ;

	vector<ThickLine> getLines() const ;
	float getSpeed() const ;
	float getSize() const ;
	int getLinesSize() const ;

	void addEnemy(Snake *_enemy) ;

	void checkSelfCollision() ;
	void checkWallCollision() ;
	void checkEnemyCollision() ;
	void updateBonusCollision() ;
	void startCollision() ;
	void goThroughWall() ;
	void control(float const& dt) ;
	void update(float const& dt) ;

	void draw(RenderWindow &window) ;

private:
	vector<ThickLine> lines ;
	float size ;
	CircleShape startCircle ;
	CircleShape endCircle ;
	Color color ;
	float dx ;

	float speed ;
	float turnSpeed ;

	Vector2f position ;
	Vector2f forward ;

	bool left ;
	bool right ;
	bool alive ;
	bool lineTimerEnd ;
	bool startTimeEnd ;
	bool noLine ;
	bool noWall ;

	Clock lineTimer ;
	Clock startTime ;
	float gap ;
	int delay ;
	float nextDelay ;

	Terrain *terrain ;

	vector<Snake*> enemy ; 
	vector<Bonus> bonusStack ;

	Keyboard::Key leftKey ;
	Keyboard::Key rightKey ;
};

