#ifndef __MyplaneLayer_H__
#define __MyplaneLayer_H__
#include "cocos2d.h"
#include"Myplane.h"
#include "source.h"
USING_NS_CC;
class MyplaneLayer :public Layer
{
public:
	CREATE_FUNC(MyplaneLayer);
	bool init();

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	static Myplane* _hero;

	void addHero();
	static Myplane* getHero();
};

#endif // !__MyplaneLayer_H__
