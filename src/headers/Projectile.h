#pragma once
#include "../stdafx.h"

class Projectile
{

protected:
	sf::Sprite sprite;
	sf::Texture	texture;

	sf::Vector2f velocity;

	float speed;
	float rotation;
	// TODO : Add damamge and other projectile params

public:

	Projectile(float r_degrees, sf::Vector2f start_pos, sf::Texture* _texture);

	void setScale(float x, float y);

	void update();

	void render(sf::RenderTarget& target);

};

