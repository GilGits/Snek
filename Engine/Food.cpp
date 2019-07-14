#include "Food.h"


Food::Food()
{
	setPosition();
}

void Food::setPosition()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, Graphics::ScreenWidth - Graphics::cellDim*2); //idk if -1 is needed
	std::uniform_int_distribution<int> yDist(0, Graphics::ScreenHeight - Graphics::cellDim*2);

	//lul
	location.setX(static_cast<int>(ceil(xDist(rng) / Graphics::cellDim) * Graphics::cellDim));
	location.setY(static_cast<int>(ceil(yDist(rng) / Graphics::cellDim) * Graphics::cellDim));
}

void Food::draw(Graphics& gfx)
{
	if (goingUnder)
	{
		notRed -= 5;

		if (notRed < 5)
		{
			goingUnder = false;
		}
	}
	else
	{
		notRed += 5;

		if (notRed > 250)
		{
			goingUnder = true;
		}
	}



	for (int i = Graphics::cellDim / 10; i < Graphics::cellDim; i++)
	{
		for (int j = Graphics::cellDim / 10; j < Graphics::cellDim; j++)
		{
			gfx.PutPixel(location.getX() + i, location.getY() + j, 255, notRed, notRed);
		}
	}
}

Location Food::getLocation() const
{
	return this->location;
}