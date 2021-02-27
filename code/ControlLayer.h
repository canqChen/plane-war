#ifndef __ControlLayer_H__
#define __ControlLayer_H__
#include "cocos2d.h"
#include "Myplane.h"
#include "source.h"
#include "PauseLayer.h"
USING_NS_CC;

class ControlLayer :public Layer
{
public:
	bool init();
	Label* scoreLabel;
	void addBombLogo();
	void addScorelabel();
	//void UpdateBombs();
	//void UpdateLifes();
	//void UpdateScores();
	//void addPauseButton();
	//void addPauseAudioButton();
	void callpause();
	void callpausemusic();
	Vector<Sprite*> lifes;

	CREATE_FUNC(ControlLayer);
};

#endif
