#pragma once
#include "../stdafx.h"
#include "FieldRect.h"

//class that create square = army, and moves to end point
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

	void updateTurnCollsion(std::vector<std::shared_ptr<FieldRect>> _roads);

	// TODO : add different types of enemies fast, invisible, armour

public:
	
	army(sf::Vector2f size, sf::Vector2f start_pos , sf::Color _color);
	army();

	//setter
	void setMoveDir(sf::Vector2f _moveDir);

	//getter
	sf::Vector2f getPos() const;
	sf::FloatRect getGlobalBounds() const;
	bool isAlive() const;

	void gotHit(int hp);

	void update(std::vector<std::shared_ptr<FieldRect>> _roads);

	void render(sf::RenderTarget& target);


};

