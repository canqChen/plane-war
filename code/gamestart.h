#ifndef __GAMESTART_H__
#define __GAMESTART_H__
#include"AppDelegate.h"
#include "source.h"
#include "cocos2d.h"
#include "Level1_Scene.h"

#include "Myplane.h"
USING_NS_CC;
class GameStart : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	void callstart();
	void callendthegame();
	void callhelp();
	void callshift();
	void loadmusic();
	void pre_init();
	CREATE_FUNC(GameStart);
};

class HelpScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void callbacktomain();
	CREATE_FUNC(HelpScene);
};
class ShiftScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void slect_callback1();
	void slect_callback2();
	CREATE_FUNC(ShiftScene);
};
#endif
