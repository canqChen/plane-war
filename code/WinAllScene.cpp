#include "WinAllScene.h"

Scene* WinAllScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WinAllScene::create();
	scene->addChild(layer);
	return scene;
}

bool WinAllScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::createWithSpriteFrameName("winall.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	this->addChild(bg);

	addRestartButton();
	addBacktoMainMenuButton();
	addQuitGameButton();
	addCurrentScore();
	menu = Menu::create(_restart, _backMain, _quit, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2));
	this->addChild(menu);
	GET_MUSIC_INSTANCE->playEffect("music/hightscore.mp3");

	return true;
}

void WinAllScene::addRestartButton()
{
	_restart = MenuItemImage::create("images/restart.png", "images/restart.png",
									 CC_CALLBACK_0(WinAllScene::callRestart, this));
}

void WinAllScene::addBacktoMainMenuButton()
{
	_backMain = MenuItemImage::create("images/backtomainmenu.png", "images/backtomainmenu.png",
									  CC_CALLBACK_0(WinAllScene::callBacktoMainmenu, this));
}

void WinAllScene::addQuitGameButton()
{
	_quit = MenuItemImage::create("images/end.png", "images/end.png",
								  CC_CALLBACK_0(WinAllScene::callQuit, this));
}

void WinAllScene::addCurrentScore()
{
	__String *str = __String::createWithFormat("The Final Scores: %d", Myplane::scores);
	auto num = Label::createWithTTF(str->getCString(), "fonts/Marker Felt.ttf", 40);
	num->setColor(Color3B::RED);
	num->setPosition(Vec2(SCREEN_SIZE.width / 2, 150));
	addChild(num);
}

void WinAllScene::callBacktoMainmenu()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.5, GameStart::createScene()));
}

void WinAllScene::callRestart()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, Level1_Scene::createScene()));
}

void WinAllScene::callQuit()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->end();
}