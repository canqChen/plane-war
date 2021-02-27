#ifndef __MyPlanebulletLayer_H__
#define __MyPlanebulletLayer_H__
#include "source.h"
#include "cocos2d.h"
#include "MyplaneLayer.h"
USING_NS_CC;
class MyPlaneBulletLayer :public Layer
{
public:
	CREATE_FUNC(MyPlaneBulletLayer);
	bool init();

	void startShoot();
	void stopShoot();
	void addBulletCallback(float dt);
	void removeBullet(Sprite* bullet);
	Vector<Sprite*>bulletVec;
};

#endif 