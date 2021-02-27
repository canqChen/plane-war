#include "GameLayer.h"

bool ControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addScorelabel();
	addBombLogo();
	addPauseAudioButton();
	addPauseButton();
	UpdateLifes();
	return true;
}

void ControlLayer::addBombLogo()
{
	Sprite* bomb = Sprite::createWithSpriteFrameName("bomb.png");
	bomb->setAnchorPoint(Vec2(0, 0));
	bomb->setPosition(Vec2(1, 1));
	this->addChild(bomb);
}
void ControlLayer::addScorelabel()
{
	scoreLabel = Label::createWithTTF("Scores:0", "fonts/arial.ttf", 30);
	scoreLabel->setAnchorPoint(Vec2(0, 1));
	scoreLabel->setPosition(Vec2(2, SCREEN_SIZE.height - 2));
	this->addChild(scoreLabel);
}

void ControlLayer::UpdateBombs()
{
	switch (Myplane::bombs)
	{
		case 5:
			{
			}
		default:
			break;
	}
}
void ControlLayer::UpdateLifes()
{
	if (lifes.size() > 0)
	{
		for (auto life : lifes)
		{
			life->removeFromParentAndCleanup(true);
		}
		lifes.clear();
	}
	int  gap = 4;
	for (int i = 0; i < Myplane::lifes; i++)
	{
		Sprite *life;
		switch (Myplane::is_plane1)
		{
			case true:
				{
					life = Sprite::createWithSpriteFrameName("life1.png");

					break;
				}
			default:
				{
					life = Sprite::createWithSpriteFrameName("life2.png");
					break;
				}
		}
		life->setAnchorPoint(Vec2(1, 1));
		lifes.pushBack(life);
		life->setPosition(Vec2(SCREEN_SIZE.width - i*(life->getContentSize().width + 4), life->getContentSize().height));
		this->addChild(life);
	}
}

void ControlLayer::UpdateScores()
{
	__String *str = __String::createWithFormat("Scores:%d", Myplane::scores);
	scoreLabel->setString(str->getCString());
}
void ControlLayer::addPauseButton()
{
	auto pause = MenuItemImage::create("images/run.png",
									   "images/pause.png",
									   CC_CALLBACK_0(ControlLayer::callpause, this));
	pause->setAnchorPoint(Vec2(1, 1));
	pause->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2));
	auto menu = Menu::create(pause, NULL);
	addChild(menu);
}

void ControlLayer::addPauseAudioButton()
{
	auto pauseaudio = MenuItemImage::create("images/pausemusic.png",
											"images/pausemusic.png",
											CC_CALLBACK_0(ControlLayer::callpausemusic, this));
	pauseaudio->setAnchorPoint(Vec2(1, 1));
	pauseaudio->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2 - pauseaudio->getContentSize().height));
	auto menu = Menu::create(pauseaudio, NULL);
	addChild(menu);
}

void ControlLayer::callpause()
{
	/*if (!Director::getInstance()->isPaused())
	{
	}*/
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->pause();
	((Layer*)(Myplane::getInstance()->getParent()))->setTouchEnabled(false);
	GET_MUSIC_INSTANCE->stopBackgroundMusic();
	GET_MUSIC_INSTANCE->stopAllEffects();
	auto layer = PauseLayer::create();
	addChild(layer, 20);
	/*else
	{
		((Layer*)(Myplane::getInstance()->getParent()))->setTouchEnabled(true);
		Director::getInstance()->resume();
		GET_MUSIC_INSTANCE->resumeBackgroundMusic();
		GET_MUSIC_INSTANCE->resumeAllEffects();
	}*/
}

void ControlLayer::callpausemusic()
{
	if (GET_MUSIC_INSTANCE->isBackgroundMusicPlaying())
	{
		GET_MUSIC_INSTANCE->playEffect("music/click.wav");
		GET_MUSIC_INSTANCE->stopBackgroundMusic();
		GET_MUSIC_INSTANCE->stopAllEffects();
	}
	else
	{
		GET_MUSIC_INSTANCE->playEffect("music/click.wav");
		GET_MUSIC_INSTANCE->resumeBackgroundMusic();
		GET_MUSIC_INSTANCE->resumeAllEffects();
	}
}