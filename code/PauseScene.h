#ifndef __PAUSESCENE_H__
#define __PAUSESCENE_H__
#include "cocos2d.h"
#include "source.h"
#include "Myplane.h"
#include "gamestart.h"
#include "Level2_Scene.h"
#include "Level3_Scene.h"
#include "Level4_Scene.h"
#include "Level5_Scene.h"
#include"WinAllScene.h"
#include "Level6_Scene.h"
USING_NS_CC;

class PauseScene :public Layer
{
public:

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(PauseScene);
	static Scene* createScene();
	bool init();

	//加入按钮
	void addBackground();
	void addBackGameButton();
	void addBackMainmenuButton();
	void addQuitgameButton();
	void addRestartButton();
	void addCurrentScore();

	//回调函数
	void callBacktoGame();
	void callRestart();
	void callQuittheGame();
	void callBacktoMainmenu();
private:
	Menu * _menu;
	MenuItemImage *_back, *_backMain, *_quit, *_restart;
};

#endif
