//This file is part of Curve Fever (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "ThickLine.h"

ThickLine::ThickLine()
{
	VA.setPrimitiveType(TrianglesStrip) ;
	lineVA.setPrimitiveType(LinesStrip) ;
	thickness = 10 ;
	color = Color::Blue ;
}
ThickLine::ThickLine(float const& _thickness, Color const& _color)
{
	VA.setPrimitiveType(TrianglesStrip) ;
	lineVA.setPrimitiveType(LinesStrip) ;
	thickness = _thickness ;
	color = _color ;
}

void ThickLine::addPoint(Vector2f const& p)
{
	line.push_back(p) ;
	if(line.size()>1)
	{
		Vector2f n = line[line.size()-1]-line[line.size()-2] ; n /= Norm(n) ;
		Vector2f u(n.y,-n.x) ;
		VA.append( Vertex(u*thickness+line[line.size()-1],color) ) ;
		VA.append( Vertex(-u*thickness+line[line.size()-1],color) ) ;
		VA.append( Vertex(u*thickness+line[line.size()-2],color) ) ;
		VA.append( Vertex(-u*thickness+line[line.size()-2],color) ) ;
	}
}

void ThickLine::setThickness(float const& _thickness)
{
	thickness= _thickness ;
}
void ThickLine::clear()
{
	VA.clear() ;
	lineVA.clear() ;
	line.clear() ;
}

vector<Vector2f> ThickLine::getLine() const
{
	return line ;
}
int ThickLine::getSize() const
{
	return line.size() ;
}

void ThickLine::draw(RenderWindow &window)
{
	window.draw(VA) ;
}
void ThickLine::drawLine(RenderWindow &window)
{
	lineVA.clear();
	for(int i(0) ; i < line.size() ; i++)
	{
		lineVA.append(Vertex(line[i],Color::Red)) ;
	}
	window.draw(lineVA) ;
}