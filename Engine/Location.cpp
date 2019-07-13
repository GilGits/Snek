#include "Location.h"
#include "Graphics.h"

Location::Location()
{
}

Location::Location(int x, int y)
	:
	x (x),
	y (y)
{
}

int Location::getX()
{
	return x;
}

int Location::getY()
{
	return y;
}

void Location::setX(int x)
{
	//checks per wrappare

	if (x < 0)
		this->x = Graphics::ScreenWidth - Graphics::cellDim;
	
	else if (x > Graphics::ScreenWidth - Graphics::cellDim)
		this->x = 0;

	else
		this->x = x;
}

void Location::setY(int y)
{
	//checks per wrappare

	if (y < 0)
		this->y = Graphics::ScreenHeight - Graphics::cellDim;

	else if (y > Graphics::ScreenHeight - Graphics::cellDim)
		this->y = 0;

	else
		this->y = y;
}

bool Location::operator==(const Location & other)
{
	return x == other.x && y == other.y;
}

/* useless lul
Location& Location::operator=(const Location& other)
{
	x = other.x;
	y = other.y;

	return *this;
}*/
