#include "gamestart.h"
//��Ϸ��ʼ���泡��
Scene* GameStart::createScene()
{
	auto scene = Scene::create();
	auto layer = GameStart::create();
	scene->addChild(layer);

	return scene;
}

void GameStart::pre_init()
{
	//Ԥ����plist�ļ�
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/level.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/boom.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/GameStart_.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/myplane.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/_Bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/UI.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/enemy.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/extra.plist");

	//Ԥ���������ļ�
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/bang.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/DJ.mp3");

	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_1.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_2.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_3.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_4.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_5.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/music_7.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/moca.mp3");
	GET_MUSIC_INSTANCE->preloadBackgroundMusic("music/gameMusic.mp3");
	GET_MUSIC_INSTANCE->preloadEffect("music/hightscore.mp3");
	GET_MUSIC_INSTANCE->preloadEffect("music/win.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/get.mp3");
	GET_MUSIC_INSTANCE->preloadEffect("music/over.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/myplaneattack.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/planeboom.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/smallenemyboom.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/bossattack.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/click.wav");
	GET_MUSIC_INSTANCE->preloadEffect("music/myplanedown.wav");
}
bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}
	pre_init();
	Sprite *bg = CCSprite::createWithSpriteFrameName("gamestart.png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);
	//��ʼ��Ϸ��ť
	auto startbutton = MenuItemImage::create("images/start.png",
											 "images/start.png",
											 CC_CALLBACK_0(GameStart::callstart, this));

	//������ť
	auto helpbutton = MenuItemImage::create("images/help.png",
											"images/help.png",
											CC_CALLBACK_0(GameStart::callhelp, this));

	//������Ϸ
	auto endbutton = MenuItemImage::create("images/end.png",
										   "images/end.png",
										   CC_CALLBACK_0(GameStart::callendthegame, this));

	auto shiftbutton = MenuItemImage::create("images/shift.png",
											 "images/shift.png",
											 CC_CALLBACK_0(GameStart::callshift, this));

	auto menu = Menu::create(startbutton, shiftbutton, helpbutton, endbutton, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(SCREEN_SIZE.width / 2, SCREEN_SIZE.height / 2 - 100));
	this->addChild(menu, 10);

	//��Ϸ��ʼ����������Ч
	loadmusic();

	return true;
}

void GameStart::callstart()  //��ʼ��Ϸ�ص�����
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	GET_MUSIC_INSTANCE->stopBackgroundMusic();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, Level1_Scene::createScene(), false));
}

void GameStart::callendthegame()	//������Ϸ�ص�����
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->end();
}
void GameStart::callhelp()			//�����˵��ص�����
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionFadeUp::create(0.5, HelpScene::createScene()));
}

void GameStart::callshift()	//�л�ս������ص�����
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	CCDirector::getInstance()->replaceScene(CCTransitionJumpZoom::create(0.5, ShiftScene::createScene()));
}

void GameStart::loadmusic()			//���ر�������
{
	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_4.mp3", true);
}

//�������泡��
Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);

	return scene;
}
bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite *bg = CCSprite::create("images/H.png");
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);
	MenuItem * back = CCMenuItemImage::create("images/back.png",
											  "images/back.png",
											  CC_CALLBACK_0(HelpScene::callbacktomain, this));
	back->setPosition(Vec2(300, -425));
	auto menu = Menu::create(back, NULL);
	this->addChild(menu, 10);
	return true;
}
void HelpScene::callbacktomain()	//�ص���ʼ����ص�����
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.5, GameStart::createScene()));
}

//�л�ս������
Scene* ShiftScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShiftScene::create();
	scene->addChild(layer);

	return scene;
}
bool ShiftScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = LabelBMFont::create("PLEASE CHOOSE YOUR HERO", "fonts/bitmapFontTest.fnt");
	label->setPosition(Vec2(SCREEN_SIZE.width / 2, 550));

	this->addChild(label, 5);

	auto plane1 = MenuItemImage::create("images/myplane1.png",
										"images/myplane1.png",
										CC_CALLBACK_0(ShiftScene::slect_callback1, this));

	auto plane2 = MenuItemImage::create("images/myplane2.png",
										"images/myplane2.png",
										CC_CALLBACK_0(ShiftScene::slect_callback2, this));
	auto menu = Menu::create(plane1, plane2, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Vec2(SCREEN_SIZE.width / 2, 400));
	this->addChild(menu, 10);
	return true;
}
void ShiftScene::slect_callback1()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Myplane::is_plane1 = true;
	CCDirector::getInstance()->replaceScene(TransitionShrinkGrow::create(1, GameStart::createScene()));
}
void ShiftScene::slect_callback2()
{
	GET_MUSIC_INSTANCE->playEffect("music/click.wav");
	Myplane::is_plane1 = false;
	CCDirector::getInstance()->replaceScene(TransitionMoveInB::create(1, GameStart::createScene()));
}