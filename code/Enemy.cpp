#include "Enemy.h"

Enemy::Enemy()
{
	_life = 0;
}
Enemy::~Enemy()
{
}

Enemy * Enemy::create()
{
	Enemy * pRect = new Enemy();
	pRect->autorelease();
	return pRect;
}
void Enemy::bindEnemySprite(string name, int life)		//°ó¶¨¾«ÁéÍ¼Æ¬
{
	this->initWithSpriteFrameName(name);
	_life = life;
}

int Enemy::getLife()
{
	return _life;
}
void Enemy::loseLife()
{
	_life--;
}

void Enemy::lose10lifes()
{
	_life -= 10;
}