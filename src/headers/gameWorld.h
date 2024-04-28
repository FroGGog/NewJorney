#pragma once
#include "../stdafx.h"
#include "Buildings.h"
#include "FieldRect.h"
#include "Turret.h"
#include "army.h"

class gameWorld
{
private:

	std::vector<std::vector<std::string>> worldMap;

	std::vector<FieldRect* > worldRects;

	std::vector<sf::Sprite> worldSprites;

	std::vector<Buildings> buildings;
	std::vector<Turret> turrets;

	std::map<std::string, int> resources;

	std::map < std::string, sf::Texture*> textures;

	GMine mine1;

	float saved_x, saved_y;
	float cal_x, cal_y;
	int temp_incomeGold, temp_incomeWood, temp_incomeFood;
	bool canBuild;

	//mouse check shape
	sf::RectangleShape Tshape;

	sf::Vector2i screen_size;

	//gui
	sf::Texture choosedTexture;
	sf::Sprite choosedSprite;

	//buttons
	sf::Texture goldMineT;
	sf::Texture sawmillT;

	sf::Sprite button1;
	sf::Sprite button2;

	bool clicked;
	bool print;

	//fill game field based on world string vector
	void fillRectsV();

	void initWorldMap();
	void initVars();
	void initTextures();

	void checkButtonCollision();

	//spawn sprite on clicked rect
	bool build(sf::Texture& _toBuild, bool turret = false);

	void CalculateIncome();

	//updates shape for button collision
	void updateTshape();

	void getOnRectClick(sf::Window& window);


public:

	gameWorld();
	~gameWorld();


	void getScreenSize(sf::Vector2i _screen_size);
	int getWorldEnd() const;
	void setResources(std::map <std::string, int> _res);
	std::map <std::string,int> getResources() const;
	std::vector<int> getIncome() const;

	//get all road and city rects from worldRects
	std::vector<FieldRect*> roadRects() const;

	void update(sf::Window& window);
	void updateTurrets(std::vector<army*>& enemy_armies);

	void render(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);

	void initGameField();


};
