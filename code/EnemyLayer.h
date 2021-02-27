#ifndef __EnemyLayer_H__
#define __EnemyLayer_H__
#include "Enemy.h"
#include "cocos2d.h"
#include"source.h"
#include "Myplane.h"
#include"MyPlaneBulletLayer.h"
#include<cmath>
USING_NS_CC;

const int SMALL_MAXLIFE = 1;
const int BIG_MAXLIFE = 12;
const int BOSS_MAXLIFE1 = 40;
const int BOSS_MAXLIFE2 = 60;
const int BOSS_MAXLIFE3 = 80;
const int BOSS_MAXLIFE4 = 120;
const int BOSS_MAXLIFE5 = 160;
const int BOSS_MAXLIFE6 = 200;

class EnemyLayer :public Layer
{
public:

	CREATE_FUNC(EnemyLayer);    //创建图层
	bool init(); //初始化
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//处理小敌机的方法
	void addNormalSmallEnemy(float dt);
	void addTraceSmallEnemy(float dt);
	void smallEnemyBlowUp(Enemy * smallEnemy);
	void removeSmallEnemy(Enemy* enemy);
	void removeAllSmallEnemy();

	////处理大敌机的方法
	void addNormalBigEnemy(float dt);

	void bigEnemyBlowUp(Enemy * bigEnemy);
	void removeBigEnemy(Enemy* enemy);
	void removeAllBigEnemy();

	//处理boss的方法
	void addBossEnemy(float dt);
	void bossEnemyBlowUp(Enemy * bossEnemy);
	void removeBossEnemy(Enemy* enemy);

	//删除所有出现的大小敌机
	void removeAllEnemy();

	//敌机发射子弹
	void shoot(float dt);
	void enemyShootOnce(Enemy* enemy);
	void enemyShootFive(Enemy* enemy);
	void removeEnemyBullet(Sprite* bullet);
	void removeAllEnemyBullet();
	void bossShoot(Enemy* enemy);

	Vector<Enemy*> smallVec;  //存放小敌机的容器
	Vector<Enemy*> bigVec;			//存放打敌机的容器
	Vector<Enemy*> bossVec;	//存放boss的容器
	Vector<Sprite*> enemyBulletVec;  //存放敌机子弹
	Myplane * _hero;

	void callWin(float dt);
	void callUnschedule();

	float _smalldelay;
	float _bigdelay;
	float _bossdelay;
};

#endif // !__EnemyLayer_H__
