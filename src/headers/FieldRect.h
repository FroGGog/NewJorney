#pragma once
#include "../stdafx.h"

class FieldRect
{
// TODO : change rects to sprites
public:
	enum f_type { GROUND, FOREST, ROAD, CITY, WATER, MOUNTAIN, SPOINT, NONE};
	enum turn_type{LEFT, RIGHT, UP, DOWN, NONETURN};

	FieldRect(f_type _r_type, turn_type _turn = NONETURN);

	//accessors
	FieldRect::f_type getType() const;
	FieldRect::turn_type getTurn() const;
	sf::FloatRect getGBounds() const;

	std::unique_ptr<sf::Sprite> getShape() const;

	//setters
	void setType(f_type _type);
	void setTurnType(turn_type _turn);
	void setTexture(std::shared_ptr<sf::Texture> _texture, float scale_x, float scale_y);
	void setPos(sf::Vector2f _newPos);

private:

	sf::Sprite rect;

	f_type rect_type;
	turn_type turn_side;

};

