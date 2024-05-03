#pragma once
#include "../stdafx.h"
#include "army.h"

enum projectile_state {NONE, HIT, OUT};

class Projectile
{

protected:
	sf::Sprite sprite;

	sf::Vector2f velocity;

	float speed;
	float rotation;

	projectile_state state;

	int damage;

	void updateBorderCollision();
	void updateEnemyCollision(std::shared_ptr<army> checkArmy);

public:

	Projectile(float r_degrees, sf::Vector2f start_pos, std::shared_ptr<sf::Texture> _texture);

	void setScale(float x, float y, std::shared_ptr<sf::Texture> _texture);
	void setDamage(int _damage);
	projectile_state getState() const;

	void update(std::shared_ptr<army> checkArmy);
	

	void render(sf::RenderTarget& target);

};

