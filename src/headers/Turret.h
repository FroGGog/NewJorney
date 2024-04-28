#pragma once
#include "../stdafx.h"


class Turret
{
private:

	sf::Sprite sprite;

	float attackSpeed;
	float rotationSpeed;

	void updateRotation();

public:

	Turret(sf::Texture* _texture);

	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f _newPos);
	void setScale(float x, float y);

	void update(sf::Vector2f _enemyPos);

	void render(sf::RenderTarget& target);

};

