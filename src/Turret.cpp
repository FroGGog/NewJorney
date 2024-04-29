#include "headers/Turret.h"


Turret::Turret(std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::Texture> _projectileTexture , turret_type _type)
{

	this->sprite.setTexture(*_texture);
	this->projectileTexture = _projectileTexture;


	this->sprite.setOrigin(_texture->getSize().x / static_cast<float>(2), _texture->getSize().y / static_cast<float>(2));

	this->attackSpeed = 1.f;
	this->rotationSpeed = 0.89f;
	this->saved_x = 5;
	this->saved_y = 5;

	this->type = _type;

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

void Turret::update(std::vector<army>& enemy_armies)
{
	sf::Vector2f _enemyPos = this->findClosestEnemy(enemy_armies);

	//rotation system

	float angle = atan2((_enemyPos.y + 2.5f) - this->sprite.getPosition().y, (_enemyPos.x + 2.5f) - this->sprite.getPosition().x) * 180 / 3.14;

	this->sprite.setRotation(angle);

	//shoot system
	this->shoot(_enemyPos);

	//update projectiles
	for (auto& i : this->projectiles) {
		i->update();
	}

	this->updateOutProjectiles();


}

void Turret::render(sf::RenderTarget& target)
{	
	target.draw(this->sprite);

	for (auto& i : this->projectiles) {
		i->render(target);
	}

}


void Turret::shoot(sf::Vector2f _enemyPos)
{
	
	this->reloadTime = this->reloadClock.getElapsedTime();

	if (this->reloadTime.asSeconds() > .5f) {

		float ProjectileAngle = atan2(_enemyPos.y - this->sprite.getPosition().y, _enemyPos.x - this->sprite.getPosition().x) * 180 / 3.14;

		sf::Vector2f projectile_stPos = {this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4 - 1.f,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 10 - 1.f};

		std::shared_ptr<Projectile> tempArrow = std::make_shared<Projectile>(ProjectileAngle, projectile_stPos , this->projectileTexture);

		tempArrow->setScale(this->saved_x, this->saved_y);
		
		this->projectiles.push_back(tempArrow);

		this->reloadClock.restart();

	}

}

void Turret::updateOutProjectiles()
{
	//if projectile out of screen border - delete it
	for (int i{ 0 }; i < this->projectiles.size(); i++) {
		if (this->projectiles[i]->getState() == projectile_state::OUT) {
			this->projectiles.erase(this->projectiles.begin() + i);
		}
	}
}

sf::Vector2f Turret::findClosestEnemy(std::vector<army>& enemy_armies)
{
	float ShortestDistance = 10000;
	float tempDistance = 0;
	sf::Vector2f enemyPosition;

	for (auto& i : enemy_armies) {
		
		tempDistance = this->calculateDistance(i.getPos());
		if (tempDistance < ShortestDistance) {
			enemyPosition = i.getPos();
			ShortestDistance = tempDistance;
		}
	}
	return enemyPosition;
	
}

float Turret::calculateDistance(sf::Vector2f enemyPos)
{
	float distance = sqrt(abs(pow(enemyPos.x - this->sprite.getPosition().x, 2) + pow(enemyPos.y - this->sprite.getPosition().y, 2)));

	return distance;
}

