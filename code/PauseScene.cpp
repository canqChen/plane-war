#include "PauseScene.h"

Scene* PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}
bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addBackground();
	addBackGameButton();
	addRestartButton();
	addBackMainmenuButton();
	addQuitgameButton();
	_menu = Menu::create(_back, _restart, _backMain, _quit, NULL);
	_menu->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2 - 50));
	_menu->alignItemsVerticallyWithPadding(20);
	addChild(_menu);
	addCurrentScore();

	auto _listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = CC_CALLBACK_2(PauseScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	return true;
}

void PauseScene::addBackground()
{
	auto bg = Sprite::createWithSpriteFrameName("pausegame.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);
}
void PauseScene::addBackGameButton()
{
	_back = MenuItemImage::create("images/resume.png", "images/resume.png",
								  CC_CALLBACK_0(PauseScene::callBacktoGame, this));
}

void PauseScene::addBackMainmenuButton()
{
	_backMain = MenuItemImage::create("images/backtomainmenu.png", "images/backtomainmenu.png",
									  CC_CALLBACK_0(PauseScene::callBacktoMainmenu, this));
}

void PauseScene::addQuitgameButton()
{
	_quit = MenuItemImage::create("images/end.png", "images/end.png",
								  CC_CALLBACK_0(PauseScene::callQuittheGame, this));
}
void PauseScene::addRestartButton()
{
	_restart = MenuItemImage::create("images/restart.png", "images/restart.png",
									 CC_CALLBACK_0(PauseScene::callRestart, this));
}
void PauseScene::addCurrentScore()
{
	auto _score = Sprite::createWithSpriteFrameName("currentscore.png");
	_score->setPosition(Vec2(SCREEN_SIZE.width / 2 - _score->getContentSize().width, 120));
	addChild(_score);
	__String *str = __String::createWithFormat("%d", Myplane::scores);
	auto num = Label::createWithTTF(str->getCString(), "fonts/Marker Felt.ttf", 40);
	num->setColor(Color3B::RED);
	num->setPosition(Vec2(SCREEN_SIZE.width / 2, 120));
	addChild(num);
}
void PauseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		callBacktoGame();
	}
}

////////////////////////////////以下为回调函数//////////////////////////////////////////

void PauseScene::callBacktoGame()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	GET_MUSIC_INSTANCE->resumeBackgroundMusic();
	Director::getInstance()->popScene();
}

void PauseScene::callBacktoMainmenu()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.5, GameStart::createScene()));
}
void PauseScene::callQuittheGame()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->end();
}

void PauseScene::callRestart()
{
	switch (level)
	{
		case 1:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, Level1_Scene::createScene()));
				break;
			}
		case 2:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.5, Level2_Scene::createScene()));
				break;
			}
		case 3:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, Level3_Scene::createScene()));
				break;
			}
		case 4:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(0.5, Level4_Scene::createScene()));
				break;
			}
		case 5:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5, Level5_Scene::createScene()));
				break;
			}
		case 6:
			{
				MyplaneLayer::_hero = NULL;
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5, Level6_Scene::createScene()));
				break;
			}
	}
}