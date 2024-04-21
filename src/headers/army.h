#pragma once
#include "../stdafx.h"

//class that create square = army, and moves it attack to enemy city 
class army
{

private:

	enum status{IDLE, ATTACK};

	sf::RectangleShape* shape;

	sf::Color color;

	sf::Vector2f pos;

	std::vector<std::vector<std::string>> surrond;

public:
	
	army(sf::Vector2f size, sf::Vector2f start_pos , sf::Color _color);
	~army();

	void update();
	void updateDest();
	void updateSurrond();

	void render(sf::RenderTarget& target);


};

