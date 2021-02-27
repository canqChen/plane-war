#ifndef __FoodLayer_H__
#define __FoodLayer_H__

#include "cocos2d.h"
#include "source.h"
USING_NS_CC;

class FoodLayer :public Layer
{
public:
	CREATE_FUNC(FoodLayer);
	bool init();

	void addBomb(float dt);
	void addLife(float dt);

	void removeBomb(Sprite* bomb);
	void removeLife(Sprite* life);
	Vector<Sprite*>bombVec;
	Vector<Sprite*>lifeVec;
};

#endif
