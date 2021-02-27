#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "cocos2d.h"

#include "Myplane.h"
#include "source.h"

USING_NS_CC;

class BackgroundLayer :public Layer
{
public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool init();
	static Label* bombNumLabel;
	Label* scoreLabel;
	void addBombLogo();
	void addScorelabel();
	static void UpdateBombs();
	void UpdateLifes();
	void UpdateScores();
	void addPauseButton();
	void addPauseAudioButton();
	void callpause();
	void callpausemusic();
	void callChangeMuisc();
	Vector<Sprite*> lifes;

	CREATE_FUNC(BackgroundLayer);
};

#endif
