#pragma once
#include "../stdafx.h"
#include "Buildings.h"

class GameStats
{
private:

	int wood, gold, food;
	int woodIncome, goldIncome, foodIncome;
	
	sf::Text wood_t, gold_t, food_t;
	sf::Font mainFont;

	sf::Texture food_icT, wood_icT, gold_icT;
	sf::Sprite food_S, wood_S, gold_S;

	sf::Clock incomeClock;
	sf::Time timeToAdd;

	void initFont();
	void initTextures();

	void updateT(sf::Text& _text, int _resource, int _income);

	void updateResources();


public:

	GameStats();

	std::vector<int> getResources() const;
	void setResources(std::vector<int> _res);
	void getIncome(std::vector<int> income);

	void update();

	void render(sf::RenderTarget& target);

};


