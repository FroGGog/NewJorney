#include "headers/Turret.h"


Turret::Turret(sf::Texture* _texture, sf::Texture* _projectileTexture , turret_type _type)
{

	this->sprite.setTexture(*_texture);
	this->projectileTexture = _projectileTexture;


	this->sprite.setOrigin(_texture->getSize().x / 2, _texture->getSize().y / 2);

	this->attackSpeed = 1.f;
	this->rotationSpeed = 0.89f;
	this->saved_x = 5;
	this->saved_y = 5;

	this->type = _type;

}



Turret::~Turret()
{
	this->projectileTexture = nullptr;
}

sf::Sprite Turret::getSprite() const
{
	return this->sprite;
}

void Turret::setPos(sf::Vector2f _newPos)
{
	this->sprite.setPosition(_newPos);
}

void Turret::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
	this->saved_x = x;
	this->saved_y = y;
}

sf::FloatRect Turret::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void Turret::update(sf::Vector2f _enemyPos)
{
	//rotation system

	float angle = atan2((_enemyPos.y + 2.5f) - this->sprite.getPosition().y, (_enemyPos.x + 2.5f) - this->sprite.getPosition().x) * 180 / 3.14;

	this->sprite.setRotation(angle);

	//shoot system
	this->shoot(_enemyPos);

	//update projectiles
	for (auto& i : this->projectiles) {
		i.update();
	}


}

void Turret::render(sf::RenderTarget& target)
{	
	target.draw(this->sprite);

	for (auto& i : this->projectiles) {
		i.render(target);
	}

}

void Turret::updateRotation()
{

	this->sprite.rotate(2.f);
}

void Turret::shoot(sf::Vector2f _enemyPos)
{
	this->reloadTime = this->reloadClock.getElapsedTime();

	if (this->reloadTime.asSeconds() > .5f) {

		float ProjectileAngle = atan2(_enemyPos.y - this->sprite.getPosition().y, _enemyPos.x - this->sprite.getPosition().x) * 180 / 3.14;

		Projectile tempArrow{ ProjectileAngle, this->sprite.getPosition(), this->projectileTexture};

		tempArrow.setScale(this->saved_x, this->saved_y);
		
		this->projectiles.push_back(tempArrow);

		this->reloadClock.restart();

	}

}

