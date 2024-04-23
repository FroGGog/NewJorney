#pragma once
#include "../stdafx.h"
#include "FieldRect.h"

//class that create square = army, and moves it attack to enemy city 
class army
{

private:

	enum status{IDLE, ATTACK};

	sf::RectangleShape* shape;

	sf::Color color;

	sf::Vector2f pos;
	sf::Vector2f dest;

	sf::Clock armyMove;
	sf::Time moveTime;

	bool lastElem;
	int counter;

	std::vector<std::vector<std::string>> surrond;

	status state;

	//distance between army and city
	int distance;

	bool updateDistance(sf::Vector2f _newPos);
	void updatePos(std::vector<FieldRect*> _roads);

	void moveUp();

public:
	
	army(sf::Vector2f size, sf::Vector2f start_pos , sf::Color _color, sf::Vector2f _dest);
	~army();

	void update(std::vector<FieldRect*> _roads);

	void render(sf::RenderTarget& target);


};

