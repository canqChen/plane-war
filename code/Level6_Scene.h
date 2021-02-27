#ifndef __Level6_Scene_H__
#define __Level6_Scene_H__
#include "source.h"
#include"Myplane.h"
#include "cocos2d.h"
#include"MyPlaneBulletLayer.h"
#include "EnemyLayer.h"
#include "BackgroundLayer.h"
#include "MyplaneLayer.h"
#include "FoodLayer.h"
USING_NS_CC;

class Level6_Scene : public Layer
{
public:
	enum Tag
	{
		BG1, BG2
	};

	virtual bool init();
	static Scene* createScene();
	void addLayer();

	void addlevelscene();
	void moveLevelScene(float t);	//¹öÆÁ

									//´¥ÆÁ

									//ÓÎÏ·Âß¼­
	void update(float dt);

	//¼ì²âÅö×²
	void Collision_smallEnemy_Mybullet();
	void Collision_bigEnemy_Mybullet();
	void Collision_smallEnemy_Myplane();
	void Collision_bigEnemy_Myplane();
	void Collision_bossEnemy_Mybullet();
	void Collision_bossEnemy_Myplane();
	void Collision_enemyBullet_Myplane();
	void Collision_Myplane_Food();
	CREATE_FUNC(Level6_Scene);

	//Í¼²ã»òÊµÀý
	MyplaneLayer* _myplanelayer;
	BackgroundLayer* _backgroundlayer;
	MyPlaneBulletLayer * _myPlanebulletLayer;
	EnemyLayer * _enemyLayer;
	FoodLayer * _foodlayer;
};

#endif
