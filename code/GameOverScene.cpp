#include "GameOverScene.h"

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::createWithSpriteFrameName("gameover.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	this->addChild(bg);

	addRestartButton();
	addBacktoMainMenuButton();
	addQuitGameButton();

	menu = Menu::create(_restart, _backMain, _quit, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2));
	this->addChild(menu);
	addCurrentScore();
	GET_MUSIC_INSTANCE->playEffect("music/over.wav");
	return true;
}

void GameOverScene::addRestartButton()
{
	_restart = MenuItemImage::create("images/restart.png", "images/restart.png",
									 CC_CALLBACK_0(GameOverScene::callRestart, this));
}

void GameOverScene::addBacktoMainMenuButton()
{
	_backMain = MenuItemImage::create("images/backtomainmenu.png", "images/backtomainmenu.png",
									  CC_CALLBACK_0(GameOverScene::callBacktoMainmenu, this));
}

void GameOverScene::addQuitGameButton()
{
	_quit = MenuItemImage::create("images/end.png", "images/end.png",
								  CC_CALLBACK_0(GameOverScene::callQuit, this));
}

void GameOverScene::addCurrentScore()
{
	__String *str = __String::createWithFormat("The Final Scores: %d", Myplane::scores);
	auto num = Label::createWithTTF(str->getCString(), "fonts/Marker Felt.ttf", 40);
	num->setColor(Color3B::RED);
	num->setPosition(Vec2(SCREEN_SIZE.width / 2, 150));
	addChild(num);
}

void GameOverScene::callBacktoMainmenu()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.5, GameStart::createScene()));
}

void GameOverScene::callRestart()
{
	Myplane::scores = 0;
	Myplane::lifes = 5;
	MyplaneLayer::_hero = NULL;
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, Level1_Scene::createScene()));
}

void GameOverScene::callQuit()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->end();
}