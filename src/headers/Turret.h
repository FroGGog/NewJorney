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

	void update();

	void render(sf::RenderTarget& target);



};

