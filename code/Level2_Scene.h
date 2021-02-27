#ifndef __Level2_Scene_H__
#define   __Level2_Scene_H__
#include "source.h"
#include"Myplane.h"
#include "cocos2d.h"
#include"MyPlaneBulletLayer.h"
#include "EnemyLayer.h"
#include "BackgroundLayer.h"
#include"MyplaneLayer.h"
#include "FoodLayer.h"
USING_NS_CC;

class Level2_Scene :public Layer
{
public:

	enum Tag
	{
		BG1, BG2
	};

	virtual bool init();
	static Scene* createScene();
	//void addhero();
	void addLayer();

	void addlevelscene();
	void moveLevelScene(float t);	//����

	//��Ϸ�߼�
	void update(float dt);

	//�����ײ
	void Collision_smallEnemy_Mybullet();
	void Collision_bigEnemy_Mybullet();
	void Collision_smallEnemy_Myplane();
	void Collision_bigEnemy_Myplane();
	void Collision_bossEnemy_Mybullet();
	void Collision_bossEnemy_Myplane();
	void Collision_enemyBullet_Myplane();
	void Collision_Myplane_Food();
	CREATE_FUNC(Level2_Scene);

	//ͼ���ʵ��

	BackgroundLayer* _backgroundlayer;
	MyPlaneBulletLayer * _myPlanebulletLayer;
	EnemyLayer * _enemyLayer;
	MyplaneLayer* _myplanelayer;
	FoodLayer * _foodlayer;
};

#endif
