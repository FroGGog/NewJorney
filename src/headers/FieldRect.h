#pragma once
#include "../stdafx.h"

class FieldRect
{
// TODO : change rects to sprites
public:
	enum f_type { GROUND, FOREST, ROAD, CITY, WATER, MOUNTAIN, NONE};
	enum turn_type{LEFT, RIGHT, UP, DOWN, NONETURN};

	FieldRect(sf::RectangleShape _rect, f_type _r_type, turn_type _turn = NONETURN);

	//accessors
	FieldRect::f_type getType() const;
	FieldRect::turn_type getTurn() const;
	sf::FloatRect getGBounds() const;

	sf::RectangleShape getShape() const;

	//setters
	void setType(f_type _type);
	void setColor(sf::Color _color);
	void setTurnType(turn_type _turn);
	
private:

	sf::RectangleShape rect;

	f_type rect_type;
	turn_type turn_side;

};

