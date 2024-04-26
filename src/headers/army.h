#pragma once
#include "../stdafx.h"
#include "FieldRect.h"

//class that create square = army, and moves it attack to enemy city 
class army
{

private:

	sf::RectangleShape* shape;

	sf::Color color;

	sf::Clock armyMove;
	sf::Time moveTime;

	sf::Vector2f moveDir;
	float speed;

	void updatePos(std::vector<FieldRect*> _roads);

	void updateTurnCollsion(std::vector<FieldRect*> _roads);


public:
	
	army(sf::Vector2f size, sf::Vector2f start_pos , sf::Color _color);
	~army();

	void setMoveDir(sf::Vector2f _moveDir);

	void update(std::vector<FieldRect*> _roads);

	void render(sf::RenderTarget& target);


};

