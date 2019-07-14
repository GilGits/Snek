#include "Snake.h"

Snake::Snake()
{
	//luuuuuuuul
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth/2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim*2) / Graphics::cellDim) * Graphics::cellDim)));
	/*body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim*3) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 4) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 5) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 6) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 7) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 8) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim * 9) / Graphics::cellDim) * Graphics::cellDim)));*/
}

void Snake::getInput(const Keyboard& kbd)
{
	if(!hasChosen)
	{
		if ((kbd.KeyIsPressed('W') || kbd.KeyIsPressed(VK_UP)) && direction != down)
		{
			direction = up;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('A') || kbd.KeyIsPressed(VK_LEFT)) && direction != right)
		{
			direction = left;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('S') || kbd.KeyIsPressed(VK_DOWN)) && direction != up)
		{
			direction = down;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('D') || kbd.KeyIsPressed(VK_RIGHT)) && direction != left)
		{
			direction = right;
			hasChosen = true;
		}
	}
}

bool Snake::move()
{
	hasChosen = false;

	if (!hasFuckedUp())
	{
		for (size_t i = body.size() - 1; i > 0; i--)
		{
			body[i] = body[i - 1];
		}

		if (direction == up)
		{
			body[0].setY(body[0].getY() - Graphics::cellDim);
		}
		else if (direction == left)
		{
			body[0].setX(body[0].getX() - Graphics::cellDim);
		}
		else if (direction == down)
		{
			body[0].setY(body[0].getY() + Graphics::cellDim);
		}
		else if (direction == right)
		{
			body[0].setX(body[0].getX() + Graphics::cellDim);
		}

		return true;
	}

	return false;
}

void Snake::draw(Graphics& gfx)
{
	gfx.DrawRectDim(body[0].getX(), body[0].getY(), Graphics::cellDim, Graphics::cellDim, Color{ 2, 73, 4 });

	for (unsigned int i = 1; i < body.size(); i++)
	{
		switch (i % 5)
		{
		case 0:
			color = Color{ 0, 255, 0};
			break;
		case 1:
			color = Color{ 20, 180, 30};
			break;
		case 2:
			color = Color{ 10, 205, 0 };
			break;
		case 3:
			color = Color{ 50, 160, 0 };
			break;
		case 4:
			color = Color{ 0, 225, 40 }; 
			break;
		}

		gfx.DrawRectDim(body[i].getX(), body[i].getY(), Graphics::cellDim, Graphics::cellDim, color);
	}
}

bool Snake::testCollision(Location location)
{
	if (direction == up)
	{
		location.setY(location.getY() + Graphics::cellDim);
	}
	else if (direction == left)
	{
		location.setX(location.getX() + Graphics::cellDim);
	}
	else if (direction == down)
	{
		location.setY(location.getY() - Graphics::cellDim);
	}
	else if (direction == right)
	{
		location.setX(location.getX() - Graphics::cellDim);
	}

	return body[0] == location;
}

bool Snake::hasFuckedUp()
{
	// quando si perdeva ai bordi
	/*if (direction == up)
	{
		if (body[0].getY() < Graphics::cellDim)
			return true;
	}
	if (direction == left)
	{
		if (body[0].getX() < Graphics::cellDim)
			return true;
	}
	if (direction == down)
	{
		if (body[0].getY() > Graphics::ScreenHeight - Graphics::cellDim - 1)
			return true;
	}
	if (direction == right)
	{
		if (body[0].getX() > Graphics::ScreenWidth - Graphics::cellDim - 1)
			return true;
	}*/

	for (size_t i = body.size() - 2; i > 0; i--)
	{
		if (testCollision(body[i]))
			return true;
	}

	return false;
}

bool Snake::hasEaten(Food food)
{
	if (testCollision(food.getLocation()))
	{
		body.insert(body.begin(), food.getLocation());

		return true;
	}

	return false;
}

bool Snake::isOverlapping(Location foodLocation)
{
	for (size_t i = 0; i < body.size(); i++)
	{
		if (body[i] == foodLocation)
			return true;
	}

	return false;
}
