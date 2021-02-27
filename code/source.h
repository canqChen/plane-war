#ifndef _SOURCE_H_
#define _SOURCE_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
#define GET_MUSIC_INSTANCE CocosDenshion::SimpleAudioEngine::getInstance()
const Size SCREEN_SIZE = Size(650, 900);
extern int level;
enum GameScore
{
	SMALL_SCORE = 10,
	BIG_SCORE = 30,
	BOSS_SCORE = 100
};
#endif
