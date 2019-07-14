#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Food.h"
#include <vector>

enum Direction {up, left, down, right};

class Snake
{
private:
	std::vector<Location> body;
	Direction direction = up;
	Color color = Colors::Green;
	bool hasChosen = false;

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