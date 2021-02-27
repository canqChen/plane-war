#ifndef __WinScene_H__
#define __WinScene_H__
#include "cocos2d.h"
#include "source.h"
#include "Myplane.h"
#include "gamestart.h"
#include "Level2_Scene.h"
#include "Level3_Scene.h"
#include "Level4_Scene.h"
#include "Level5_Scene.h"
#include "Level6_Scene.h"
USING_NS_CC;
class WinScene :public Layer
{
public:
	CREATE_FUNC(WinScene);
	static Scene* createScene();
	bool init();

	void addNextButton();
	void addBackground();
	void addBackMainmenuButton();
	void addQuitgameButton();
	void addCurrentScore();

	void callQuittheGame();
	void callBacktoMainmenu();
	void callNext();

private:
	Menu * _menu;
	MenuItemImage *_next, *_backMain, *_quit;
};

#endif
