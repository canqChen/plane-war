#include "WinScene.h"

Scene* WinScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WinScene::create();
	scene->addChild(layer);
	return scene;
}
bool WinScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addBackground();
	addNextButton();
	addBackMainmenuButton();
	addQuitgameButton();
	_menu = Menu::create(_next, _backMain, _quit, NULL);
	_menu->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2 - 100));
	_menu->alignItemsVerticallyWithPadding(20);
	addChild(_menu);
	addCurrentScore();
	GET_MUSIC_INSTANCE->playEffect("music/win.wav");

	return true;
}

void WinScene::addBackground()
{
	auto bg = Sprite::createWithSpriteFrameName("victory.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);
}

void WinScene::addBackMainmenuButton()
{
	_backMain = MenuItemImage::create("images/backtomainmenu.png", "images/backtomainmenu.png",
									  CC_CALLBACK_0(WinScene::callBacktoMainmenu, this));
}

void WinScene::addQuitgameButton()
{
	_quit = MenuItemImage::create("images/end.png", "images/end.png",
								  CC_CALLBACK_0(WinScene::callQuittheGame, this));
}

void WinScene::addCurrentScore()
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

void WinScene::addNextButton()
{
	_next = MenuItemImage::create("images/next.png", "images/nxet.png",
								  CC_CALLBACK_0(WinScene::callNext, this));
}

//////////////////////////////////»Øµ÷º¯Êý////////////////////////////////////////

void WinScene::callBacktoMainmenu()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionSplitRows::create(0.5, GameStart::createScene()));
}
void WinScene::callQuittheGame()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->end();
}
void WinScene::callNext()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	switch (level)
	{
		case 1:Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, Level2_Scene::createScene(), TransitionScene::Orientation::RIGHT_OVER)); break;
		case 2:Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, Level3_Scene::createScene(), TransitionScene::Orientation::UP_OVER)); break;
		case 3:Director::getInstance()->replaceScene(TransitionShrinkGrow::create(0.5, Level4_Scene::createScene())); break;
		case 4:Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5, Level5_Scene::createScene())); break;
		case 5:Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.5, Level6_Scene::createScene())); break;
	}
}