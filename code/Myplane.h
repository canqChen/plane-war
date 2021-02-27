#ifndef __Myplane_H__
#define __Myplane_H__
#include"cocos2d.h"
#include"source.h"

USING_NS_CC;
class Myplane :public Sprite
{
public:
	CREATE_FUNC(Myplane);

	bool init();
	static bool is_plane1;
	void blowUp();
	void removePlane();
	void loseLife();

	static int lifes;			//生命数
	static int scores;//分数
	static int bombs;
};

#endif