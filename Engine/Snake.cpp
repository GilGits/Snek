#include "Snake.h"

Snake::Snake()
{
	//luuuuuuuul
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth/2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim) / Graphics::cellDim) * Graphics::cellDim)));
	body.push_back(Location(static_cast<int>(ceil((Graphics::ScreenWidth / 2) / Graphics::cellDim) * Graphics::cellDim), static_cast<int>(ceil((Graphics::ScreenHeight / 2 + Graphics::cellDim*2) / Graphics::cellDim) * Graphics::cellDim)));
}

void Snake::getInput(const Keyboard& kbd)
{
	if(!hasChosen)
	{
		if ((kbd.KeyIsPressed('W') || kbd.KeyIsPressed(VK_UP)) && direction != Direction::Down)
		{
			direction = Direction::Up;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('A') || kbd.KeyIsPressed(VK_LEFT)) && direction != Direction::Right)
		{
			direction = Direction::Left;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('S') || kbd.KeyIsPressed(VK_DOWN)) && direction != Direction::Up)
		{
			direction = Direction::Down;
			hasChosen = true;
		}
		else if ((kbd.KeyIsPressed('D') || kbd.KeyIsPressed(VK_RIGHT)) && direction != Direction::Left)
		{
			direction = Direction::Right;
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

		if (direction == Direction::Up)
		{
			body[0].setY(body[0].getY() - Graphics::cellDim);
		}
		else if (direction == Direction::Left)
		{
			body[0].setX(body[0].getX() - Graphics::cellDim);
		}
		else if (direction == Direction::Down)
		{
			body[0].setY(body[0].getY() + Graphics::cellDim);
		}
		else if (direction == Direction::Right)
		{
			body[0].setX(body[0].getX() + Graphics::cellDim);
		}

		return true;
	}

	return false;
}

void Snake::draw(Graphics& gfx)
{
	//Draw head
	gfx.DrawRectDim(body[0].getX(), body[0].getY(), Graphics::cellDim, Graphics::cellDim, Color{ 2, 73, 4 });

	//Draw eyes on head
	int eyesDim = static_cast<int>(static_cast<float>(4) / 15 * Graphics::cellDim); // 8/30 is the proportion of eyesDim to cellDim
	int eyesDistance = static_cast<int>(static_cast<float>(1) / 6 * Graphics::cellDim); // 5/30 is the proportion of eyesDistance to cellDim

	if (direction == Direction::Up)
	{
		gfx.DrawRectDim(body[0].getX() + eyesDistance, body[0].getY() + 1, eyesDim, eyesDim, Color{ 0, 15, 0 });
		gfx.DrawRectDim(body[0].getX() + Graphics::cellDim - (eyesDim + eyesDistance), body[0].getY() + 1, eyesDim, eyesDim, Color{ 0, 15, 0 });
	}
	else if (direction == Direction::Left)
	{
		gfx.DrawRectDim(body[0].getX() + 1, body[0].getY() + eyesDistance, eyesDim, eyesDim, Color{ 0, 15, 0 });
		gfx.DrawRectDim(body[0].getX() + 1, body[0].getY() + Graphics::cellDim - (eyesDim + eyesDistance), eyesDim, eyesDim, Color{ 0, 15, 0 });
	}
	else if (direction == Direction::Down)
	{
		gfx.DrawRectDim(body[0].getX() + eyesDistance, body[0].getY() + Graphics::cellDim - (eyesDim + 1), eyesDim, eyesDim, Color{ 0, 15, 0 });
		gfx.DrawRectDim(body[0].getX() + Graphics::cellDim - (eyesDim + eyesDistance), body[0].getY() + Graphics::cellDim - (eyesDim + 1), eyesDim, eyesDim, Color{ 0, 15, 0 });
	}
	else if (direction == Direction::Right)
	{
		gfx.DrawRectDim(body[0].getX() + Graphics::cellDim - (eyesDim + 1), body[0].getY() + eyesDistance, eyesDim, eyesDim, Color{ 0, 15, 0 });
		gfx.DrawRectDim(body[0].getX() + Graphics::cellDim - (eyesDim + 1), body[0].getY() + Graphics::cellDim - (eyesDim + eyesDistance), eyesDim, eyesDim, Color{ 0, 15, 0 });
	}

	//Draw rest of the body
	for (unsigned int i = 1; i < body.size(); i++)
	{
		//Pattern of colors
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

		if(eatenBody == 0 || eatenBody != i)
			gfx.DrawRectDim(body[i].getX(), body[i].getY(), Graphics::cellDim, Graphics::cellDim, color);
		else
			gfx.DrawRectDim(body[i].getX(), body[i].getY(), Graphics::cellDim, Graphics::cellDim, Color(60, 0, 90));
	}
}

bool Snake::testCollision(Location location)
{
	if (direction == Direction::Up)
	{
		location.setY(location.getY() + Graphics::cellDim);
	}
	else if (direction == Direction::Left)
	{
		location.setX(location.getX() + Graphics::cellDim);
	}
	else if (direction == Direction::Down)
	{
		location.setY(location.getY() - Graphics::cellDim);
	}
	else if (direction == Direction::Right)
	{
		location.setX(location.getX() - Graphics::cellDim);
	}

	return body[0] == location;
}

bool Snake::hasFuckedUp()
{
	for (size_t i = body.size() - 2; i > 0; i--)
	{
		if (testCollision(body[i]))
		{
			eatenBody = static_cast<int>(i);
			return true;
		}
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
