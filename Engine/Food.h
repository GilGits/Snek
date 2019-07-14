#pragma once


#include "Colors.h"
#include "Graphics.h"
#include "Location.h"
#include <random>

class Food
{
private:
	Location location;
	int notRed = 0;
	bool goingUnder = false;

public:
	Food();

	void setPosition();
	void draw(Graphics& gfx);

	Location Food::getLocation() const;
};