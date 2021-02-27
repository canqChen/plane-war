#ifndef __GameOverScene_H__
#define __GameOverScene_H__
#include "gamestart.h"
#include "cocos2d.h"
#include "source.h"
#include "Myplane.h"
#include "Level1_Scene.h"
USING_NS_CC;
class GameOverScene :public Layer
{
public:
public:
	CREATE_FUNC(GameOverScene);
	static	Scene* createScene();
	bool init();

	void addRestartButton();
	void callRestart();
	void addBacktoMainMenuButton();
	void callBacktoMainmenu();
	void addQuitGameButton();
	void callQuit();
	void addCurrentScore();

	MenuItemImage *_backMain, *_quit, *_restart;
	Menu* menu;
};

#endif
