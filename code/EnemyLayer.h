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

	CREATE_FUNC(EnemyLayer);    //����ͼ��
	bool init(); //��ʼ��
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//����С�л��ķ���
	void addNormalSmallEnemy(float dt);
	void addTraceSmallEnemy(float dt);
	void smallEnemyBlowUp(Enemy * smallEnemy);
	void removeSmallEnemy(Enemy* enemy);
	void removeAllSmallEnemy();

	////�����л��ķ���
	void addNormalBigEnemy(float dt);

	void bigEnemyBlowUp(Enemy * bigEnemy);
	void removeBigEnemy(Enemy* enemy);
	void removeAllBigEnemy();

	//����boss�ķ���
	void addBossEnemy(float dt);
	void bossEnemyBlowUp(Enemy * bossEnemy);
	void removeBossEnemy(Enemy* enemy);

	//ɾ�����г��ֵĴ�С�л�
	void removeAllEnemy();

	//�л������ӵ�
	void shoot(float dt);
	void enemyShootOnce(Enemy* enemy);
	void enemyShootFive(Enemy* enemy);
	void removeEnemyBullet(Sprite* bullet);
	void removeAllEnemyBullet();
	void bossShoot(Enemy* enemy);

	Vector<Enemy*> smallVec;  //���С�л�������
	Vector<Enemy*> bigVec;			//��Ŵ�л�������
	Vector<Enemy*> bossVec;	//���boss������
	Vector<Sprite*> enemyBulletVec;  //��ŵл��ӵ�
	Myplane * _hero;

	void callWin(float dt);
	void callUnschedule();

	float _smalldelay;
	float _bigdelay;
	float _bossdelay;
};

#endif // !__EnemyLayer_H__
