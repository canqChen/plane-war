#ifndef __Enemy_H__
#define __Enemy_H__
#include "cocos2d.h"
#include "source.h"
#include <string>
using namespace std;
USING_NS_CC;
class Enemy :public Sprite
{
public:
	Enemy();
	~Enemy();
	static Enemy * create();
	void bindEnemySprite(string name, int life);
	int getLife();
	void loseLife();
	void lose10lifes();

private:
	int _life;
};
#endif
