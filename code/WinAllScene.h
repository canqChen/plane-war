#ifndef __WinAllScene_H__
#define	__WinAllScene_H__
#include "Myplane.h"
#include "gamestart.h"
#include "cocos2d.h"
#include "MyplaneLayer.h"

USING_NS_CC;
class WinAllScene :public Layer
{
public:
	CREATE_FUNC(WinAllScene);
	static	Scene* createScene();
	bool init();

	void addRestartButton();
	void callRestart();
	void addBacktoMainMenuButton();

	void addCurrentScore();
	void callBacktoMainmenu();
	void addQuitGameButton();
	void callQuit();

	MenuItemImage *_backMain, *_quit, *_restart;
	Menu* menu;
};

#endif // !__WinAllScene_H__