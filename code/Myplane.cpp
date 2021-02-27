#include "Myplane.h"
#include "GameOverScene.h"
int Myplane::bombs = 5;
int Myplane::lifes = 5;
int Myplane::scores = 0;
bool Myplane::is_plane1 = true;

bool Myplane::init()
{
	if (!Sprite::init())
		return false;

	switch (is_plane1)
	{
		case true: this->initWithSpriteFrameName("myplane1.png"); break;
		default:	this->initWithSpriteFrameName("myplane2.png"); break;
	}

	Blink *blink = Blink::create(1, 3);

	//ÉÁ3´Î
	Sequence *sequence = Sequence::create(blink, NULL);
	runAction(sequence);

	//±©Õ¨¶¯»­»º´æ

	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.005f);
	//animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("boom1.png"));
	//animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("boom2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom4.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom5.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom6.png"));
	//animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("boom7.png"));
	//animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("boom8.png"));
	AnimationCache::getInstance()->addAnimation(animation, "PlaneBlowUp");

	return true;
}

void  Myplane::blowUp()
{
	GET_MUSIC_INSTANCE->playEffect("music/planeboom.wav");
	Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("PlaneBlowUp"));
	auto actionDone = CallFunc::create(this, callfunc_selector(Myplane::removePlane));
	Sequence *sequence = Sequence::create(animate, actionDone, NULL);
	this->runAction(sequence);
}

void Myplane::removePlane()
{
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, GameOverScene::createScene()));
	//removeFromParentAndCleanup(true);
}

void Myplane::loseLife()
{
	GET_MUSIC_INSTANCE->playEffect("music/myplanedown.wav");
	--lifes;
}