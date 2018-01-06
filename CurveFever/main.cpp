/*********************************************************************

This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

Curve Fever is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Curve Fever is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Curve Fever. If not, see <http://www.gnu.org/licenses/>.

Curve Fever codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>  
#include "Utility.h"
#include "Snake.h"
#include "Terrain.h"

using namespace std ;
using namespace sf ;

int main()
{
	int width = 800, height = 800, playerNb ;
	cout<<"Terrain size : "<<endl ; 
	cout<<"Width : " ; cin>>width ; 
	cout<<"Height : " ; cin>>height ;
	cout<<"Number of players : " ; cin>>playerNb ;

	vector<Keyboard::Key> keyBinding(playerNb*2+1,Keyboard::Unknown) ;
	
	for(int k(0) ; k < keyBinding.size() ; k++) // bind players input to Snakes movements
	{
		if(k!=keyBinding.size()-1) cout<<"Choose your ";
		if(k%2==0 && k!=keyBinding.size()-1) cout<<"left key " ;
		else if(k%2!=0 && k!=keyBinding.size()-1)cout<<"right key " ;
		if(k!=keyBinding.size()-1) cout<<"player "<<k/2+1<<"..."<<endl ; 

		else cout<<"Choose the restart key... " ;

		while(keyBinding[k]==Keyboard::Unknown)
		{
			for(int i(0) ; i < Keyboard::KeyCount ; i++)
			{
				if(Keyboard::isKeyPressed(Keyboard::Key(i)) && Keyboard::Key(i) != keyBinding[k-1] && Keyboard::Key(i) != Keyboard::Return) keyBinding[k]=Keyboard::Key(i) ;
			}
		}
	}
	Keyboard::Key restartKey = keyBinding[keyBinding.size()-1] ;
	
	ContextSettings antiAliasing ; antiAliasing.antialiasingLevel = 32 ;
	RenderWindow window(VideoMode(width,height, 32), "CurveFever",Style::Default,antiAliasing);
	window.setFramerateLimit(60) ;

	vector<Color> c;
	 c.push_back(Color::Red) ;
	  c.push_back(Color::Blue) ;
	   c.push_back(Color::White) ;
	    c.push_back(Color::Green) ;

	while(true) //loop to restart game
	{
		Terrain terrain(width, height) ; 

		srand(time(NULL)) ;
	
		vector<Snake> player ; //vector that stores the players
		
		for(int i(0) ; i < playerNb ; i++)
		{
			player.push_back(Snake(randVector2f(terrain.getSize())/2.f+terrain.getSize()/4.f,
					randVector2f(1)-Vector2f(0.5,0.5), c[i],	&terrain ,keyBinding[2*i],keyBinding[2*i+1])) ;
		}
	
		for(int i(0) ; i < playerNb ; i++) //assigning enemies
		{
			for(int j(0) ; j < playerNb ; j++)
			{
				if(i!=j)
					player[i].addEnemy(&player[j]) ;
			}
		}

		Clock deltaTime ;
		float dt= 0.001 ;
		Event ev ;

		while(window.isOpen())
		{
			while(window.pollEvent(ev)) {} 
			for(int i(0) ; i < playerNb ; i++) //update players position, alive state and so on
				player[i].update(dt) ;

			terrain.updateBonus() ; //eventually add a bonus
		
			window.clear() ; //draw players, bonus and terrain borders
			terrain.draw(window) ;
			for(int i(0) ; i < playerNb ; i++)
				player[i].draw(window) ;
			window.display() ;

			if(Keyboard::isKeyPressed(restartKey)) break ; //restart game

			dt= deltaTime.restart().asSeconds() ; //get time since the last frame
		}
	}
}