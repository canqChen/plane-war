#include "BackgroundLayer.h"
#include"PauseScene.h"

Label* BackgroundLayer::bombNumLabel = NULL;
bool BackgroundLayer::init()
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
	UpdateScores();
	auto _listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = CC_CALLBACK_2(BackgroundLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	return true;
}

void BackgroundLayer::addBombLogo()
{
	Sprite* bomb = Sprite::createWithSpriteFrameName("bomb.png");
	bomb->setAnchorPoint(Vec2(0, 0));
	bomb->setPosition(Vec2(1, 1));
	this->addChild(bomb);
	bombNumLabel = Label::create("  X  5", "fonts/Marker Felt.ttf", 30);
	bombNumLabel->setAnchorPoint(Vec2(0, 0));
	bombNumLabel->setColor(Color3B::WHITE);
	bombNumLabel->setPosition(Vec2(41, 3));
	this->addChild(bombNumLabel);
}
void BackgroundLayer::addScorelabel()
{
	scoreLabel = Label::createWithTTF(" Scores: 0", "fonts/Marker Felt.ttf", 30);
	scoreLabel->setAnchorPoint(Vec2(0, 1));
	scoreLabel->setPosition(Vec2(2, SCREEN_SIZE.height - 2));
	this->addChild(scoreLabel);
}

void BackgroundLayer::UpdateBombs()
{
	__String *str = __String::createWithFormat("  X  %d", Myplane::bombs);

	bombNumLabel->setString(str->getCString());
}

void BackgroundLayer::UpdateLifes()
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

void BackgroundLayer::UpdateScores()
{
	__String *str = __String::createWithFormat(" Scores: %d", Myplane::scores);
	scoreLabel->setString(str->getCString());
}

void BackgroundLayer::addPauseButton()
{
	auto pause = MenuItemImage::create("images/run.png",
									   "images/pause.png",
									   CC_CALLBACK_0(BackgroundLayer::callpause, this));
	pause->setAnchorPoint(Vec2(1, 1));
	pause->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2));
	auto menu = Menu::create(pause, NULL);
	addChild(menu);
}

void BackgroundLayer::addPauseAudioButton()
{
	auto pauseaudio = MenuItemImage::create("images/pausemusic.png",
											"images/pausemusic.png",
											CC_CALLBACK_0(BackgroundLayer::callpausemusic, this));
	pauseaudio->setAnchorPoint(Vec2(1, 1));
	pauseaudio->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2 - pauseaudio->getContentSize().height));
	auto menu = Menu::create(pauseaudio, NULL);
	addChild(menu);
}

void BackgroundLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:callpause(); break;
		case EventKeyboard::KeyCode::KEY_TAB:callChangeMuisc(); break;
	}
}
///////////////////////////////以下为回调函数///////////////////////////////////////////

void BackgroundLayer::callpause()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	GET_MUSIC_INSTANCE->stopBackgroundMusic();

	Director::getInstance()->pushScene(TransitionShrinkGrow::create(0.5, PauseScene::createScene()));
}

void BackgroundLayer::callpausemusic()
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

void BackgroundLayer::callChangeMuisc()
{
	static int change = 0;
	if (change < 9)
	{
		change++;
	}
	else
		change = 0;
	switch (change)
	{
		case 0:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/bangbangbang.mp3", true); break;
		case 1:GET_MUSIC_INSTANCE->playBackgroundMusic("music/DJ.mp3", true); break;
		case 2:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/gameMusic.mp3", true); break;
		case 3:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/moca.mp3", true);	break;
		case 4:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_1.mp3", true); break;
		case 5:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_2.mp3", true); break;
		case 6:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_3.mp3", true); break;
		case 7:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_4.mp3", true); break;
		case 8:GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_5.mp3", true); break;
		case 9:	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_7.mp3", true); break;
	}
}