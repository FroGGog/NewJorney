#pragma once
#include "../stdafx.h"
#include "Projectile.h"

enum turret_type { ARROW };

class Turret
{
private:

	std::vector<Projectile> projectiles;

	sf::Texture* projectileTexture;
	sf::Sprite sprite;
	
	sf::Clock reloadClock;
	sf::Time reloadTime;

	float attackSpeed;
	float rotationSpeed;
	turret_type type;

	//for scale
	float saved_x, saved_y;

	void updateRotation();
	void shoot(sf::Vector2f _enemyPos);

public:

	Turret(sf::Texture* _texture, sf::Texture* _projectileTexture, turret_type _type);
	~Turret();

	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f _newPos);
	void setScale(float x, float y);
	sf::FloatRect getBounds();


	void update(sf::Vector2f _enemyPos);

	void render(sf::RenderTarget& target);

};

