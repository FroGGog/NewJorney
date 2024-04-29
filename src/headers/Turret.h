#pragma once
#include "../stdafx.h"
#include "Projectile.h"
#include "army.h"

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

	void shoot(sf::Vector2f _enemyPos);
	void updateOutProjectiles();
	sf::Vector2f findClosestEnemy(std::vector<army>& enemy_armies);
	float calculateDistance(sf::Vector2f enemyPos);

public:

	Turret(sf::Texture* _texture, sf::Texture* _projectileTexture, turret_type _type);
	~Turret();

	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f _newPos);
	void setScale(float x, float y);
	sf::FloatRect getBounds();


	void update(std::vector<army>& enemy_armies);

	void render(sf::RenderTarget& target);

};

// TODO : add othet types of towers