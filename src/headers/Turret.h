#pragma once
#include "../stdafx.h"
#include "Projectile.h"
#include "army.h"

enum turret_type { ARROW };

class Turret
{
private:
	// TODO : add turet shoot range

	std::vector<std::shared_ptr<Projectile>> projectiles;

	std::shared_ptr<sf::Texture> projectileTexture;
	sf::Sprite sprite;

	sf::CircleShape radiusShape;
	float radius;
	
	sf::Clock reloadClock;
	sf::Time reloadTime;

	float attackSpeed;
	float rotationSpeed;
	turret_type type;

	//for scale
	float saved_x, saved_y;

	void shoot(sf::Vector2f _enemyPos);

	void updateOutProjectiles();
	void updateHitProjectiles();

	std::shared_ptr<army> findClosestEnemy(std::vector<std::shared_ptr<army>> enemy_armies);
	float calculateDistance(sf::Vector2f enemyPos);

public:

	Turret(std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::Texture> _projectileTexture, turret_type _type);

	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f _newPos);
	void setScale(float x, float y);
	sf::FloatRect getBounds();


	void update(std::vector<std::shared_ptr<army>> enemy_armies);

	void render(sf::RenderTarget& target);

};

// TODO : add othet types of towers