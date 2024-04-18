#pragma once
#include "../stdafx.h"

class gameWorld
{
private:

	std::vector<std::vector<std::string>> worldMap;

	std::vector<sf::RectangleShape> worldRects;

	std::vector<sf::Sprite> worldSprites;

	float saved_x, saved_y;
	float cal_x, cal_y;
	std::string saved_type;

	//mouse check shape
	sf::RectangleShape Tshape;

	sf::Vector2i scree_size;

	//gui
	sf::Texture choosedTexture;
	sf::Sprite choosedSprite;

	sf::Texture goldMineT;
	sf::Texture goldMineTplace;
	sf::Sprite button1;

	bool clicked;

	void fillRectsV();

	void initWorldMap();
	void initVars();
	void initTextures();

	void updateRects();

	void getOnRectClick(sf::Window& window);


public:

	gameWorld();

	void getScreenSize(sf::Vector2i _screen_size);
	int getWorldEnd() const;

	void update(sf::Window& window);

	void render(sf::RenderTarget& target);


};
