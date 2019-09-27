#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Food.h"
#include <vector>



class Snake
{
private:
	enum class Direction { Up, Left, Down, Right };
	std::vector<Location> body;
	Direction direction = Direction::Right;
	Color color = Colors::Green;
	bool hasChosen = false;
	int eatenBody = 0;
	bool testCollision(Location location);
	bool hasFuckedUp();


public:
	Snake();

	static constexpr int moveRate = 5;

	void getInput(const Keyboard& kbd);
	bool move();
	void draw(Graphics& gfx);

	bool hasEaten(Food food);
	bool isOverlapping(Location foodLocation);
};