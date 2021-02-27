#include "Level3_Scene.h"

Scene* Level3_Scene::createScene()
{
	auto scene = Scene::create();

	auto layer = Level3_Scene::create();
	scene->addChild(layer);

	return scene;
}

void Level3_Scene::addLayer()
{
	_myplanelayer = MyplaneLayer::create();
	addChild(_myplanelayer);

	_myPlanebulletLayer = MyPlaneBulletLayer::create();		//增加玩家子弹图层
	addChild(_myPlanebulletLayer);

	_enemyLayer = EnemyLayer::create();
	addChild(_enemyLayer);    //增加敌机图层

	_backgroundlayer = BackgroundLayer::create();	//增加界面静态图层
	addChild(_backgroundlayer);

	_foodlayer = FoodLayer::create();
	addChild(_foodlayer);
}

bool Level3_Scene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	level = 3;
	addlevelscene();		//加载背景
	addLayer();		//加载图层
	GET_MUSIC_INSTANCE->playBackgroundMusic("music/music_1.mp3", true); //加载背景音乐
	scheduleUpdate();
	return true;
}

void Level3_Scene::addlevelscene()
{
	Sprite *level1_bg1 = CCSprite::createWithSpriteFrameName("level3.png");
	level1_bg1->setTag(BG1);
	level1_bg1->setAnchorPoint(Vec2(0, 0));
	level1_bg1->setPosition(Vec2(0, 0));
	this->addChild(level1_bg1);

	Sprite * level1_bg2 = CCSprite::createWithSpriteFrameName("level3.png");
	level1_bg2->setTag(BG2);
	level1_bg2->setAnchorPoint(Vec2(0, 0));
	level1_bg2->setPosition(Vec2(0, level1_bg2->getContentSize().height - 2.5));
	addChild(level1_bg2);

	schedule(schedule_selector(Level3_Scene::moveLevelScene), 0.01f);
}

void Level3_Scene::moveLevelScene(float t)
{
	Sprite * bg1 = (Sprite*)getChildByTag(BG1);
	Sprite * bg2 = (Sprite*)getChildByTag(BG2);

	bg1->setPositionY(bg1->getPositionY() - 2.5);
	bg2->setPositionY(bg1->getPositionY() + bg2->getContentSize().height - 2.5);

	if (bg2->getPositionY() < 0)
	{
		bg1->setPositionY(0);
	}
}

//小敌机与玩家子弹碰撞
void Level3_Scene::Collision_smallEnemy_Mybullet()
{
	if (_enemyLayer->smallVec.size() > 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Vector<Sprite*>* tempBulletVec = new Vector<Sprite*>();
		for (auto enemy : _enemyLayer->smallVec)
		{
			for (auto bullet : _myPlanebulletLayer->bulletVec)
			{
				Rect enemyRect = enemy->getBoundingBox();
				enemyRect.origin.x += 5;
				enemyRect.origin.y += 5;
				enemyRect.size.width -= 10;
				enemyRect.size.height -= 10;
				if (enemyRect.intersectsRect(bullet->getBoundingBox()))
				{
					tempBulletVec->pushBack(bullet);
					tempEnemyVec->pushBack(enemy);
					Myplane::scores += SMALL_SCORE;
					_backgroundlayer->UpdateScores();
				}
			}
		}
		for (int i = 0; i < tempEnemyVec->size(); i++)
		{
			Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
			_enemyLayer->smallEnemyBlowUp(tempEnemy);
			this->removeChild(tempEnemy, true);
		}
		for (int i = 0; i < tempBulletVec->size(); i++)
		{
			Sprite* tempBullet = (Sprite*)tempBulletVec->at(i);
			_myPlanebulletLayer->removeBullet(tempBullet);
			this->removeChild(tempBullet, true);
		}
		delete tempBulletVec;
		delete tempEnemyVec;
	}
}

//大敌机与玩家子弹碰撞
void Level3_Scene::Collision_bigEnemy_Mybullet()
{
	if (_enemyLayer->bigVec.size() > 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Vector<Sprite*>* tempBulletVec = new Vector<Sprite*>();

		for (auto enemy : _enemyLayer->bigVec)
		{
			Rect enemyRect = enemy->getBoundingBox();
			enemyRect.origin.x += 20;
			enemyRect.origin.y += 20;
			enemyRect.size.width -= 40;
			enemyRect.size.height -= 40;
			for (auto bullet : _myPlanebulletLayer->bulletVec)
			{
				if (enemyRect.intersectsRect(bullet->getBoundingBox()))
				{
					tempBulletVec->pushBack(bullet);
					enemy->loseLife();
					if (enemy->getLife() > 0)
					{
						GET_MUSIC_INSTANCE->playEffect("music/myplaneattack.wav");
					}
					else
					{
						tempEnemyVec->pushBack(enemy);
						Myplane::scores += BIG_SCORE;
						_backgroundlayer->UpdateScores();
					}
				}
			}
		}

		for (int i = 0; i < tempEnemyVec->size(); i++)
		{
			Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
			_enemyLayer->bigEnemyBlowUp(tempEnemy);
			this->removeChild(tempEnemy, true);
		}
		for (int i = 0; i < tempBulletVec->size(); i++)
		{
			Sprite* tempBullet = (Sprite*)tempBulletVec->at(i);
			_myPlanebulletLayer->removeBullet(tempBullet);
			this->removeChild(tempBullet, true);
		}
		delete tempBulletVec;
		delete tempEnemyVec;
	}
}

//boss与玩家子弹碰撞
void Level3_Scene::Collision_bossEnemy_Mybullet()
{
	if (_enemyLayer->bossVec.size() > 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Vector<Sprite*>* tempBulletVec = new Vector<Sprite*>();

		for (auto enemy : _enemyLayer->bossVec)
		{
			Rect enemyRect = enemy->getBoundingBox();
			enemyRect.origin.x += 20;
			enemyRect.origin.y += 20;
			enemyRect.size.width -= 40;
			enemyRect.size.height -= 40;
			for (auto bullet : _myPlanebulletLayer->bulletVec)
			{
				if (enemyRect.intersectsRect(bullet->getBoundingBox()))
				{
					tempBulletVec->pushBack(bullet);
					enemy->loseLife();
					if (enemy->getLife() > 0)
					{
						GET_MUSIC_INSTANCE->playEffect("music/bossattack.wav");
					}
					else
					{
						tempEnemyVec->pushBack(enemy);
						Myplane::scores += BOSS_SCORE;
						_backgroundlayer->UpdateScores();
						_myPlanebulletLayer->stopShoot();
					}
				}
			}
		}
		for (int i = 0; i < tempEnemyVec->size(); i++)
		{
			Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
			_enemyLayer->bossEnemyBlowUp(tempEnemy);
			this->removeChild(tempEnemy, true);
		}
		for (int i = 0; i < tempBulletVec->size(); i++)
		{
			Sprite* tempBullet = (Sprite*)tempBulletVec->at(i);
			_myPlanebulletLayer->removeBullet(tempBullet);
			this->removeChild(tempBullet, true);
		}
		delete tempBulletVec;
		delete tempEnemyVec;
	}
}

//小敌机与玩家飞机碰撞

void  Level3_Scene::Collision_smallEnemy_Myplane()
{
	if (Myplane::lifes >= 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 10;
		planeRect.origin.y += 10;
		planeRect.size.width -= 20;
		planeRect.size.height -= 20;
		for (auto enemy : _enemyLayer->smallVec)
		{
			Rect enemyRect = enemy->getBoundingBox();
			enemyRect.origin.x += 5;
			enemyRect.origin.y += 5;
			enemyRect.size.width -= 10;
			enemyRect.size.height -= 10;

			if (planeRect.intersectsRect(enemyRect))
			{
				tempEnemyVec->pushBack(enemy);
				for (int i = 0; i < tempEnemyVec->size(); i++)
				{
					Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
					_enemyLayer->smallEnemyBlowUp(tempEnemy);
					this->removeChild(tempEnemy, true);
				}
				Myplane::scores += SMALL_SCORE;
				_backgroundlayer->UpdateScores();
				_myplanelayer->_hero->loseLife();
				_backgroundlayer->UpdateLifes();
				if (Myplane::lifes < 0)
				{
					_myPlanebulletLayer->stopShoot();
					_myplanelayer->_hero->blowUp();
				}
			}
		}
		delete tempEnemyVec;
	}
}

//大敌机与玩家飞机碰撞

void Level3_Scene::Collision_bigEnemy_Myplane()
{
	if (Myplane::lifes >= 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 10;
		planeRect.origin.y += 10;
		planeRect.size.width -= 20;
		planeRect.size.height -= 20;
		for (auto enemy : _enemyLayer->bigVec)
		{
			Rect enemyRect = enemy->getBoundingBox();
			enemyRect.origin.x += 15;
			enemyRect.origin.y += 10;
			enemyRect.size.width -= 30;
			enemyRect.size.height -= 20;

			if (planeRect.intersectsRect(enemyRect))
			{
				tempEnemyVec->pushBack(enemy);
				for (int i = 0; i < tempEnemyVec->size(); i++)
				{
					Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
					this->removeChild(tempEnemy, true);
					_enemyLayer->bigEnemyBlowUp(tempEnemy);
				}
				Myplane::scores += BIG_SCORE;
				_backgroundlayer->UpdateScores();
				_myplanelayer->_hero->loseLife();
				_backgroundlayer->UpdateLifes();
				if (Myplane::lifes < 0)
				{
					_myPlanebulletLayer->stopShoot();
					_myplanelayer->_hero->blowUp();
				}
			}
		}
		delete tempEnemyVec;
	}
}

//boss 与玩家飞机碰撞
void Level3_Scene::Collision_bossEnemy_Myplane()
{
	if (Myplane::lifes >= 0)
	{
		Vector<Enemy*>* tempEnemyVec = new Vector<Enemy*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 10;
		planeRect.origin.y += 10;
		planeRect.size.width -= 20;
		planeRect.size.height -= 20;
		for (auto enemy : _enemyLayer->bossVec)
		{
			Rect enemyRect = enemy->getBoundingBox();
			enemyRect.origin.x += 20;
			enemyRect.origin.y += 10;
			enemyRect.size.width -= 40;
			enemyRect.size.height -= 20;

			if (planeRect.intersectsRect(enemyRect))
			{
				enemy->loseLife();
				if (enemy->getLife() > 0)
				{
					GET_MUSIC_INSTANCE->playEffect("music/bossattack.wav");
				}
				else
				{
					tempEnemyVec->pushBack(enemy);
					for (int i = 0; i < tempEnemyVec->size(); i++)
					{
						Enemy* tempEnemy = (Enemy*)tempEnemyVec->at(i);
						_enemyLayer->bossEnemyBlowUp(tempEnemy);
						this->removeChild(tempEnemy, true);
					}
					Myplane::scores += BOSS_SCORE;
					_backgroundlayer->UpdateScores();
					_myPlanebulletLayer->stopShoot();
				}
				_myplanelayer->_hero->loseLife();
				_backgroundlayer->UpdateLifes();
				if (Myplane::lifes < 0)
				{
					_myPlanebulletLayer->stopShoot();
					_myplanelayer->_hero->blowUp();
				}
			}
		}
		delete tempEnemyVec;
	}
}

//敌机子弹与玩家飞机碰撞
void Level3_Scene::Collision_enemyBullet_Myplane()
{
	if (Myplane::lifes >= 0)
	{
		Vector<Sprite*>* tempBulletVec = new Vector<Sprite*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 20;
		planeRect.origin.y += 15;
		planeRect.size.width -= 40;
		planeRect.size.height -= 30;
		for (auto bullet : _enemyLayer->enemyBulletVec)
		{
			if (planeRect.intersectsRect(bullet->getBoundingBox()))
			{
				tempBulletVec->pushBack(bullet);
				for (int i = 0; i < tempBulletVec->size(); i++)
				{
					Sprite* tempbullet = (Sprite*)tempBulletVec->at(i);
					_enemyLayer->removeEnemyBullet(tempbullet);
					this->removeChild(tempbullet, true);
				}
				_myplanelayer->_hero->loseLife();
				_backgroundlayer->UpdateLifes();
				if (Myplane::lifes < 0)
				{
					_myPlanebulletLayer->stopShoot();
					_myplanelayer->_hero->blowUp();
				}
			}
		}
		delete tempBulletVec;
	}
}

void Level3_Scene::Collision_Myplane_Food()
{
	if (_foodlayer->bombVec.size() > 0)
	{
		Vector<Sprite*>*tempVec = new Vector<Sprite*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 10;
		planeRect.origin.y += 10;
		planeRect.size.width -= 20;
		planeRect.size.height -= 20;
		for (auto bomb : _foodlayer->bombVec)
		{
			if (planeRect.intersectsRect(bomb->getBoundingBox()))
			{
				GET_MUSIC_INSTANCE->playEffect("music/get.mp3");
				tempVec->pushBack(bomb);
				if (Myplane::bombs <= 7)
				{
					Myplane::bombs++;
					_backgroundlayer->UpdateBombs();
				}
			}
		}
		for (int i = 0; i < tempVec->size(); i++)
		{
			Sprite* tempbomb = (Sprite*)tempVec->at(i);
			_foodlayer->removeBomb(tempbomb);
			this->removeChild(tempbomb, true);
		}
		delete tempVec;
	}
	if (_foodlayer->lifeVec.size() > 0)
	{
		Vector<Sprite*>*templifeVec = new Vector<Sprite*>();
		Rect planeRect = _myplanelayer->_hero->getBoundingBox();
		planeRect.origin.x += 10;
		planeRect.origin.y += 10;
		planeRect.size.width -= 20;
		planeRect.size.height -= 20;
		for (auto life : _foodlayer->lifeVec)
		{
			if (planeRect.intersectsRect(life->getBoundingBox()))
			{
				GET_MUSIC_INSTANCE->playEffect("music/get.mp3");
				templifeVec->pushBack(life);
				if (Myplane::lifes <= 7)
				{
					Myplane::lifes++;
					_backgroundlayer->UpdateLifes();
				}
			}
		}
		for (int i = 0; i < templifeVec->size(); i++)
		{
			Sprite* templife = (Sprite*)templifeVec->at(i);
			_foodlayer->removeLife(templife);
			this->removeChild(templife, true);
		}
		delete templifeVec;
	}
}

void Level3_Scene::update(float dt)
{
	Collision_smallEnemy_Mybullet();
	Collision_bigEnemy_Mybullet();
	Collision_smallEnemy_Myplane();
	Collision_bigEnemy_Myplane();
	Collision_bossEnemy_Myplane();
	Collision_bossEnemy_Mybullet();
	Collision_enemyBullet_Myplane();
	Collision_Myplane_Food();
}