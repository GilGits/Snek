#pragma once


class Location
{
private:
	int x;
	int y;

public:
	Location();
	Location(int x, int y);

	int getX() const;
	int getY() const;

	void setX(int x);
	void setY(int y);

	//useless lul Location& operator=(const Location& other);
	bool operator==(const Location& other);
};