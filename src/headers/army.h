#pragma once
#include "../stdafx.h"
#include "FieldRect.h"

//class that create square = army, and moves it attack to enemy city 
class army
{

private:

	enum m_side {UP, DOWN, LEFT, RIGHT};

	sf::RectangleShape shape;

	sf::Color color;

	sf::Clock armyMove;
	sf::Time moveTime;

	sf::Vector2f moveDir;
	float speed;
	bool alive;
	int hp;
	m_side movingSide;

	void updateTurnCollsion(std::vector<FieldRect*> _roads);


public:
	
	army(sf::Vector2f size, sf::Vector2f start_pos , sf::Color _color);

	void setMoveDir(sf::Vector2f _moveDir);
	sf::Vector2f getPos();
	sf::FloatRect getGlobalBounds();

	void update(std::vector<FieldRect*> _roads);

	void render(sf::RenderTarget& target);


};

