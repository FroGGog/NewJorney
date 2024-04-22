#pragma once
#include "../stdafx.h"

class FieldRect
{

public:
	enum f_type { GROUND, FOREST, ROAD, CITY, WATER, MOUNTAIN, NONE};

	FieldRect(sf::RectangleShape _rect, f_type _r_type);

	//accessors
	FieldRect::f_type getType() const;
	sf::RectangleShape getShape() const;

	//setters
	void setType(f_type _type);
	void setColor(sf::Color _color);
	
private:

	sf::RectangleShape rect;

	f_type rect_type;
};

