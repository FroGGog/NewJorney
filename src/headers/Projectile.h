#pragma once
#include "../stdafx.h"

enum projectile_state {NONE, HIT, OUT};

class Projectile
{

protected:
	sf::Sprite sprite;
	sf::Texture	texture;

	sf::Vector2f velocity;

	float speed;
	float rotation;

	projectile_state state;

	// TODO : Add damamge and other projectile params

	void updateCollision();
	bool updateBorderCollision();
	bool updateEnemyCollision();

public:

	Projectile(float r_degrees, sf::Vector2f start_pos, sf::Texture* _texture);

	void setScale(float x, float y);
	projectile_state getState() const;

	void update();
	

	void render(sf::RenderTarget& target);

};

