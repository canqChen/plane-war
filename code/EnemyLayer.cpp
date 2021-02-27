#include "EnemyLayer.h"
#include "WinScene.h"
#include"WinAllScene.h"
bool is_boss_come = false;
bool EnemyLayer::init()		//初始化方法
{
	if (!Layer::init())
	{
		return false;
	}
	_hero = MyplaneLayer::_hero;
	//动画特效
	Animation *smallAnimation = Animation::create();
	smallAnimation->setDelayPerUnit(0.006f);
	char nameBuf[100];						//初始化
	for (int i = 1; i < 6; i++)				//爆炸播放的
	{
		memset(nameBuf, 0, sizeof(nameBuf));	//动画
		sprintf(nameBuf, "boom%d.png", i + 1);
		smallAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(nameBuf));
	}
	AnimationCache::getInstance()->addAnimation(smallAnimation, "BlowUp");

	schedule(schedule_selector(EnemyLayer::addNormalSmallEnemy), 0.5f); //设置及定时器 使0.6秒出现一架正常飞行小敌机
	schedule(schedule_selector(EnemyLayer::addTraceSmallEnemy), 1.5f);	//设置及定时器 使2秒出现一架追踪玩家的小敌机
	schedule(schedule_selector(EnemyLayer::addNormalBigEnemy), 10.0f);	//设置及定时器 使15秒出现一架大敌机
	schedule(schedule_selector(EnemyLayer::shoot), 0.2f);
	switch (level)
	{
		case 1:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 3.0*60.0f); break;
		case 2:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 3.5*60.0f); break;
		case 3:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 4.0*60.0f); break;
		case 4:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 4.5*60.0f); break;
		case 5:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 5.0*60.0f); break;
		default:scheduleOnce(schedule_selector(EnemyLayer::addBossEnemy), 5.0*60.0f); break;
	}

	auto _listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = CC_CALLBACK_2(EnemyLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	return true;
}

void EnemyLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (Myplane::bombs > 0)
		{
			Myplane::bombs--;
			BackgroundLayer::UpdateBombs();
			GET_MUSIC_INSTANCE->playEffect("music/effect_bigBoom.wav");
			removeAllEnemy();
			removeAllEnemyBullet();
			for (auto boss : bossVec)
			{
				boss->lose10lifes();
			}
		}
	}
}

///////////////////////////////////处理小敌机///////////////////////////////////////

void  EnemyLayer::addNormalSmallEnemy(float dt)			//加入正常飞行的小敌机（即从上直下）
{
	switch (is_boss_come)
	{
		case false:
			{
				Enemy * smallPlane = Enemy::create();
				switch (rand() % 5)		//随机生成5种小敌机
				{
					case 1:smallPlane->bindEnemySprite("smallenemy1.png", SMALL_MAXLIFE); break;
					case 2:smallPlane->bindEnemySprite("smallenemy2.png", SMALL_MAXLIFE); break;
					case 3:smallPlane->bindEnemySprite("smallenemy3.png", SMALL_MAXLIFE); break;
					case 4:smallPlane->bindEnemySprite("smallenemy4.png", SMALL_MAXLIFE); break;
					default:smallPlane->bindEnemySprite("smallenemy5.png", SMALL_MAXLIFE); break;
				}

				addChild(smallPlane);

				float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - smallPlane->getContentSize().width) + smallPlane->getContentSize().width / 2;
				float y = SCREEN_SIZE.height - smallPlane->getContentSize().height / 3;

				Point smallBirth = Vec2(x, y);
				smallPlane->setPosition(smallBirth);
				smallVec.pushBack(smallPlane);
				MoveTo *to;
				switch (rand() % 10)		//随机生成速度不同的小敌机
				{
					case 1:
						{
							to = MoveTo::create(2, Vec2(smallBirth.x,
														smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
							auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(to, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
					case 4:
						{
							to = MoveTo::create(3, Vec2(smallBirth.x + SCREEN_SIZE.width / 3,
														smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
							auto ease = EaseSineInOut::create(to);
							auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(ease, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
					case 7:
						{
							to = MoveTo::create(3, Vec2(smallBirth.x - SCREEN_SIZE.width / 3,
														smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
							auto ease = EaseSineInOut::create(to);
							auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(ease, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
					default:
						{
							to = MoveTo::create(3, Vec2(smallBirth.x,
														smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
							auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(to, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
				}
				break;
			}
		default:
			{
				switch (rand() % 5)
				{
					case 1:
						{
							Enemy * smallPlane = Enemy::create();
							switch (rand() % 5)		//随机生成5种小敌机
							{
								case 1:smallPlane->bindEnemySprite("smallenemy1.png", SMALL_MAXLIFE); break;
								case 2:smallPlane->bindEnemySprite("smallenemy2.png", SMALL_MAXLIFE); break;
								case 3:smallPlane->bindEnemySprite("smallenemy3.png", SMALL_MAXLIFE); break;
								case 4:smallPlane->bindEnemySprite("smallenemy4.png", SMALL_MAXLIFE); break;
								default:smallPlane->bindEnemySprite("smallenemy5.png", SMALL_MAXLIFE); break;
							}

							addChild(smallPlane);

							float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - smallPlane->getContentSize().width) + smallPlane->getContentSize().width / 2;
							float y = SCREEN_SIZE.height - smallPlane->getContentSize().height / 3;

							Point smallBirth = Vec2(x, y);
							smallPlane->setPosition(smallBirth);
							smallVec.pushBack(smallPlane);
							MoveTo *to;
							switch (rand() % 10)		//随机生成速度不同的小敌机
							{
								case 1:
									{
										to = MoveTo::create(2, Vec2(smallBirth.x,
																	smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
										auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(to, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
								case 4:
									{
										to = MoveTo::create(3, Vec2(smallBirth.x + SCREEN_SIZE.width / 3,
																	smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
										auto ease = EaseSineInOut::create(to);
										auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(ease, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
								case 7:
									{
										to = MoveTo::create(3, Vec2(smallBirth.x - SCREEN_SIZE.width / 3,
																	smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
										auto ease = EaseSineInOut::create(to);
										auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(ease, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
								default:
									{
										to = MoveTo::create(3, Vec2(smallBirth.x,
																	smallBirth.y - SCREEN_SIZE.height - smallPlane->getContentSize().height));
										auto actionDone = CCCallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(to, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
							}
							break;
						}
					default:
						break;
				}
				break;
			}
	}
}

void EnemyLayer::addTraceSmallEnemy(float dt)	//加入追击玩家飞机的小敌机
{
	switch (is_boss_come)
	{
		case true:
			{
				switch (rand() % 5)
				{
					case 1:
						{
							Enemy * smallPlane = Enemy::create();
							switch (rand() % 5)		//随机生成5种小敌机
							{
								case 1:smallPlane->bindEnemySprite("smallenemy1.png", SMALL_MAXLIFE); break;
								case 2:smallPlane->bindEnemySprite("smallenemy2.png", SMALL_MAXLIFE); break;
								case 3:smallPlane->bindEnemySprite("smallenemy3.png", SMALL_MAXLIFE); break;
								case 4:smallPlane->bindEnemySprite("smallenemy4.png", SMALL_MAXLIFE); break;
								default:smallPlane->bindEnemySprite("smallenemy5.png", SMALL_MAXLIFE); break;
							}

							addChild(smallPlane);

							float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - smallPlane->getContentSize().width) + smallPlane->getContentSize().width / 2;
							float y = SCREEN_SIZE.height + smallPlane->getContentSize().height / 2;

							Point smallBirth = Vec2(x, y);
							smallPlane->setPosition(smallBirth);
							smallVec.pushBack(smallPlane);
							MoveTo *to;
							switch (rand() % 10)		//随机生成速度不同的撞击玩家的小敌机
							{
								case 1:
									{
										to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																															   _hero->getPositionY()));

										auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
																 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
										auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(to, go, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
								case 5:
									{
										to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																															   _hero->getPositionY()));

										auto ease = EaseSineInOut::create(to);
										auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
																 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
										auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(ease, go, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}

								case 8:
									{
										to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																															   _hero->getPositionY()));

										auto ease = EaseSineInOut::create(to);
										auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
																 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
										auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(ease, go, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
								default:
									{
										to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 400), Vec2(_hero->getPositionX(),
																															   _hero->getPositionY()));

										auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
																 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
										auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
										Sequence * sequence = Sequence::create(to, go, actionDone, NULL);
										smallPlane->runAction(sequence);		//小敌机运动
										break;
									}
							}
							break;
						}
					default:
						break;
				}
				break;
			}
		default:
			{
				Enemy * smallPlane = Enemy::create();
				switch (rand() % 5)		//随机生成5种小敌机
				{
					case 1:smallPlane->bindEnemySprite("smallenemy1.png", SMALL_MAXLIFE); break;
					case 2:smallPlane->bindEnemySprite("smallenemy2.png", SMALL_MAXLIFE); break;
					case 3:smallPlane->bindEnemySprite("smallenemy3.png", SMALL_MAXLIFE); break;
					case 4:smallPlane->bindEnemySprite("smallenemy4.png", SMALL_MAXLIFE); break;
					default:smallPlane->bindEnemySprite("smallenemy5.png", SMALL_MAXLIFE); break;
				}

				addChild(smallPlane);

				float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - smallPlane->getContentSize().width) + smallPlane->getContentSize().width / 2;
				float y = SCREEN_SIZE.height + smallPlane->getContentSize().height / 2;

				Point smallBirth = Vec2(x, y);
				smallPlane->setPosition(smallBirth);
				smallVec.pushBack(smallPlane);
				MoveTo *to;
				switch (rand() % 10)		//随机生成速度不同的撞击玩家的小敌机
				{
					case 1:
						{
							to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																												   _hero->getPositionY()));

							auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
													 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
							auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(to, go, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
					case 5:
						{
							to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																												   _hero->getPositionY()));

							auto ease = EaseSineInOut::create(to);
							auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
													 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
							auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(ease, go, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}

					case 8:
						{
							to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 800), Vec2(_hero->getPositionX(),
																												   _hero->getPositionY()));

							auto ease = EaseSineInOut::create(to);
							auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
													 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
							auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(ease, go, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
					default:
						{
							to = MoveTo::create(((smallPlane->getPositionY() - _hero->getPositionY()) / 400), Vec2(_hero->getPositionX(),
																												   _hero->getPositionY()));

							auto go = MoveTo::create(((_hero->getPositionY() + smallPlane->getContentSize().height) / 600),
													 Vec2(_hero->getPositionX(), -smallPlane->getContentSize().height));
							auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallPlane));
							Sequence * sequence = Sequence::create(to, go, actionDone, NULL);
							smallPlane->runAction(sequence);		//小敌机运动
							break;
						}
				}
				break;
			}
	}
}

void  EnemyLayer::smallEnemyBlowUp(Enemy * smallEnemy)		//被击落后播放爆炸动画并删除
{
	GET_MUSIC_INSTANCE->playEffect("music/smallenemyboom.wav");
	Animate * smallAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("BlowUp"));
	auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeSmallEnemy, this, smallEnemy));
	Sequence *sequence = Sequence::create(smallAnimate, actionDone, NULL);
	smallEnemy->runAction(sequence);
}

void  EnemyLayer::removeSmallEnemy(Enemy *enemy)	//实现小飞机被删除的函数
{
	if (enemy)
	{
		enemy->removeFromParentAndCleanup(true);
		smallVec.eraseObject(enemy);
	}
}

void EnemyLayer::removeAllSmallEnemy()		//当按下炸弹技能后删除所有出现在屏幕中的小敌机
{
	for (auto enemy : smallVec)
	{
		if (enemy->getLife() >= 1)
		{
			smallEnemyBlowUp(enemy);
		}
	}
}

////////////////////////////对全部飞机//////////////////////////////////////////////
//全部飞机爆炸
void  EnemyLayer::removeAllEnemy()
{
	removeAllSmallEnemy();
	removeAllBigEnemy();
}

//////////////////////////////对敌机子弹////////////////////////////////////////////

//加入小敌机子弹，射一次

void EnemyLayer::enemyShootOnce(Enemy* enemy)
{
	if (enemy&&_hero)
	{
		auto bullet = Sprite::createWithSpriteFrameName("enemybullet.png");

		Point birthplace = enemy->getPosition() + Vec2(0, -enemy->getContentSize().height / 2);
		bullet->setPosition(birthplace);
		addChild(bullet);
		enemyBulletVec.pushBack(bullet);
		MoveTo * to;
		switch (rand() % 5)
		{
			case 0:
			case 1:
				{
					if (enemy->getPositionX() < _hero->getPositionX())
					{
						to = MoveTo::create(birthplace.y / 400.0,
											Vec2((_hero->getPositionX() - birthplace.x)*(birthplace.y - _hero->getPositionY()) / birthplace.y + birthplace.x,
												 -bullet->getContentSize().height));
					}
					else
					{
						to = MoveTo::create(birthplace.y / 400.0,
											Vec2(birthplace.x - (birthplace.x - _hero->getPositionX())*(birthplace.y - _hero->getPositionY()) / birthplace.y,
												 -bullet->getContentSize().height));
					}
					auto func = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet));
					bullet->runAction(Sequence::create(to, func, NULL));
					break;
				}
			default:
				{
					to = MoveTo::create(birthplace.y / 400.0,
										Vec2(birthplace.x, -bullet->getContentSize().height));
					auto func = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet));
					bullet->runAction(Sequence::create(to, func, NULL));
					break;
				}
		}
	}
}
//大敌机射五颗子弹
void EnemyLayer::enemyShootFive(Enemy* enemy)
{
	if (enemy)
	{
		auto bullet1 = Sprite::createWithSpriteFrameName("enemybullet.png");
		auto bullet2 = Sprite::createWithSpriteFrameName("enemybullet.png");
		auto bullet3 = Sprite::createWithSpriteFrameName("enemybullet.png");
		auto bullet4 = Sprite::createWithSpriteFrameName("enemybullet.png");
		auto bullet5 = Sprite::createWithSpriteFrameName("enemybullet.png");

		Point birthplace1 = enemy->getPosition() + Vec2(5.0, -enemy->getContentSize().height / 2);
		Point birthplace2 = enemy->getPosition() + Vec2(2.5, -enemy->getContentSize().height / 2);
		Point birthplace3 = enemy->getPosition() + Vec2(0.0, -enemy->getContentSize().height / 2);
		Point birthplace4 = enemy->getPosition() + Vec2(2.5, -enemy->getContentSize().height / 2);
		Point birthplace5 = enemy->getPosition() + Vec2(5.0, -enemy->getContentSize().height / 2);

		bullet1->setPosition(birthplace1);
		bullet2->setPosition(birthplace2);
		bullet3->setPosition(birthplace3);
		bullet4->setPosition(birthplace4);
		bullet5->setPosition(birthplace5);

		addChild(bullet1);
		addChild(bullet2);
		addChild(bullet3);
		addChild(bullet4);
		addChild(bullet5);

		enemyBulletVec.pushBack(bullet1);
		enemyBulletVec.pushBack(bullet2);
		enemyBulletVec.pushBack(bullet3);
		enemyBulletVec.pushBack(bullet4);
		enemyBulletVec.pushBack(bullet5);

		auto to1 = MoveTo::create(birthplace1.y / 250.0, Vec2(birthplace1.x - birthplace1.y*tan(40.0*3.14 / 180.0), -bullet1->getContentSize().height));
		auto to2 = MoveTo::create(birthplace1.y / 250.0, Vec2(birthplace2.x - birthplace1.y*tan(20.0*3.14 / 180.0), -bullet2->getContentSize().height));
		auto to3 = MoveTo::create(birthplace1.y / 250.0, Vec2(birthplace3.x, -bullet3->getContentSize().height));
		auto to4 = MoveTo::create(birthplace1.y / 250.0, Vec2(birthplace4.x + birthplace1.y*tan(20.0*3.14 / 180.0), -bullet4->getContentSize().height));
		auto to5 = MoveTo::create(birthplace1.y / 250.0, Vec2(birthplace5.x + birthplace1.y*tan(40.0*3.14 / 180.0), -bullet5->getContentSize().height));

		auto func1 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet1));
		auto func2 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet2));
		auto func3 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet3));
		auto func4 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet4));
		auto func5 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet5));

		bullet1->runAction(Sequence::create(to1, func1, NULL));
		bullet2->runAction(Sequence::create(to2, func2, NULL));
		bullet3->runAction(Sequence::create(to3, func3, NULL));
		bullet4->runAction(Sequence::create(to4, func4, NULL));
		bullet5->runAction(Sequence::create(to5, func5, NULL));
	}
}

void EnemyLayer::bossShoot(Enemy* enemy)
{
	if (enemy)
	{
		auto bullet1 = Sprite::createWithSpriteFrameName("bossbullet.png");
		auto bullet2 = Sprite::createWithSpriteFrameName("bossbullet.png");
		auto bullet3 = Sprite::createWithSpriteFrameName("bossbullet.png");
		Point birthplace1 = enemy->getPosition() + Vec2(-20.0, -enemy->getContentSize().height / 2);
		Point birthplace2 = enemy->getPosition() + Vec2(0.0, -enemy->getContentSize().height / 2);
		Point birthplace3 = enemy->getPosition() + Vec2(20.0, -enemy->getContentSize().height / 2);
		bullet1->setPosition(birthplace1);
		bullet2->setPosition(birthplace2);
		bullet3->setPosition(birthplace2);

		addChild(bullet1);
		addChild(bullet2);
		addChild(bullet3);

		enemyBulletVec.pushBack(bullet1);
		enemyBulletVec.pushBack(bullet2);
		enemyBulletVec.pushBack(bullet3);
		auto to1 = MoveTo::create(birthplace1.y / 400.0, Vec2(birthplace1.x - birthplace1.y*tan(30.0*3.14 / 180.0), -bullet1->getContentSize().height));
		auto to2 = MoveTo::create(birthplace1.y / 400.0, Vec2(birthplace1.x, -bullet1->getContentSize().height));
		auto to3 = MoveTo::create(birthplace1.y / 400.0, Vec2(birthplace1.x + birthplace1.y*tan(30.0*3.14 / 180.0), -bullet1->getContentSize().height));

		auto func1 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet1));
		auto func2 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet2));
		auto func3 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemyBullet, this, bullet3));

		bullet1->runAction(Sequence::create(to1, func1, NULL));
		bullet2->runAction(Sequence::create(to2, func2, NULL));
		bullet3->runAction(Sequence::create(to3, func3, NULL));
	}
}

void EnemyLayer::shoot(float dt)
{
	_smalldelay += dt;
	_bigdelay += dt;
	_bossdelay += dt;
	switch (level)
	{
		case 1:
			{
				if (_smalldelay > 0.7)
				{
					_smalldelay = 0.0;
					if (smallVec.size() > 0)
					{
						for (auto smallenemy : smallVec)
						{
							if (smallenemy->getLife() >= 1)
							{
								switch (rand() % 5)
								{
									case 0:
									case 1:
									case 2:	enemyShootOnce(smallenemy); break;
									default:
										break;
								}
							}
						}
					}
				}
				if (_bigdelay > 1.9)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 1.1)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
		case 2:
			{
				if (_smalldelay > 0.5)
				{
					_smalldelay = 0.0;
					for (auto smallenemy : smallVec)
					{
						if (smallenemy->getLife() >= 1)
						{
							switch (rand() % 5)
							{
								case 0:
								case 1:
								case 2:	enemyShootOnce(smallenemy); break;
								default:
									break;
							}
						}
					}
				}
				if (_bigdelay > 1.7)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 0.9)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
		case 3:
			{
				if (_smalldelay > 0.5)
				{
					_smalldelay = 0.0;
					if (smallVec.size() > 0)
					{
						for (auto smallenemy : smallVec)
						{
							if (smallenemy->getLife() >= 1)
							{
								switch (rand() % 5)
								{
									case 0:
									case 1:
									case 2:	enemyShootOnce(smallenemy); break;
									default:
										break;
								}
							}
						}
					}
				}
				if (_bigdelay > 1.5)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 0.7)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
		case 4:
			{
				if (_smalldelay > 0.5)
				{
					_smalldelay = 0.0;
					if (smallVec.size() > 0)
					{
						for (auto smallenemy : smallVec)
						{
							if (smallenemy->getLife() >= 1)
							{
								switch (rand() % 5)
								{
									case 0:
									case 1:
									case 2:	enemyShootOnce(smallenemy); break;
									default:
										break;
								}
							}
						}
					}
				}
				if (_bigdelay > 1.3)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 0.5)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
		case 5:
			{
				if (_smalldelay > 0.3)
				{
					_smalldelay = 0.0;
					if (smallVec.size() > 0)
					{
						for (auto smallenemy : smallVec)
						{
							if (smallenemy->getLife() >= 1)
							{
								switch (rand() % 5)
								{
									case 0:
									case 1:
									case 2:	enemyShootOnce(smallenemy); break;
									default:
										break;
								}
							}
						}
					}
				}
				if (_bigdelay > 1.3)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 0.3)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
		default:
			{
				if (_smalldelay > 0.3)
				{
					_smalldelay = 0.0;
					if (smallVec.size() > 0)
					{
						for (auto smallenemy : smallVec)
						{
							if (smallenemy->getLife() >= 1)
							{
								switch (rand() % 5)
								{
									case 0:
									case 1:
									case 2:	enemyShootOnce(smallenemy); break;
									default:
										break;
								}
							}
						}
					}
				}
				if (_bigdelay > 1.5)
				{
					_bigdelay = 0.0;
					if (bigVec.size() > 0)
					{
						for (auto bigenemy : bigVec)
						{
							if (bigenemy->getLife() >= 1)
							{
								enemyShootFive(bigenemy);
							}
						}
					}
				}
				if (_bossdelay > 0.3)
				{
					_bossdelay = 0.0;
					if (bossVec.size() > 0)
					{
						for (auto bossenemy : bossVec)
						{
							if (bossenemy->getLife() >= 1)
							{
								bossShoot(bossenemy);
							}
						}
					}
				}
				break;
			}
	}
}

//删除敌机子弹
void EnemyLayer::removeEnemyBullet(Sprite* bullet)
{
	bullet->removeFromParentAndCleanup(true);
	enemyBulletVec.eraseObject(bullet);
}

void EnemyLayer::removeAllEnemyBullet()
{
	Vector<Sprite*> *BulletVec = new Vector<Sprite*>();
	for (auto bullet : enemyBulletVec)
	{
		BulletVec->pushBack(bullet);
	}
	for (int i = 0; i < BulletVec->size(); i++)
	{
		Sprite* tempbullet = (Sprite*)BulletVec->at(i);
		removeEnemyBullet(tempbullet);
		this->removeChild(tempbullet, true);
	}
	delete BulletVec;
}

//////////////////////////////////处理大敌机////////////////////////////////////////
////////////////功能实现与小敌机类似//////////////////////////////////////////////////

void  EnemyLayer::addNormalBigEnemy(float dt)		//加入大敌机
{
	switch (is_boss_come)
	{
		case true:
			{
				switch (rand() % 5)
				{
					case 0:
					case 1:
						{
							Enemy * bigPlane = Enemy::create();
							switch (rand() % 5)
							{
								case 1:bigPlane->bindEnemySprite("bigenemy1.png", BIG_MAXLIFE); break;
								case 2:bigPlane->bindEnemySprite("bigenemy2.png", BIG_MAXLIFE); break;
								case 3:bigPlane->bindEnemySprite("bigenemy3.png", BIG_MAXLIFE); break;
								case 4:bigPlane->bindEnemySprite("bigenemy4.png", BIG_MAXLIFE); break;
								default:bigPlane->bindEnemySprite("bigenemy5.png", BIG_MAXLIFE); break;
							}
							bigVec.pushBack(bigPlane);
							addChild(bigPlane);

							float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - bigPlane->getContentSize().width) + bigPlane->getContentSize().width / 2;
							float y = SCREEN_SIZE.height + bigPlane->getContentSize().height / 3;

							Point bigBirth = Vec2(x, y);
							bigPlane->setPosition(bigBirth);
							MoveTo *	to = MoveTo::create(10, Vec2(bigBirth.x,
																	 bigBirth.y - SCREEN_SIZE.height - bigPlane->getContentSize().height));
							auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeBigEnemy, this, bigPlane));
							Sequence * sequence = Sequence::create(to, actionDone, NULL);
							bigPlane->runAction(sequence);
							break;
						}
					default:
						break;
				}
				break;
			}
		default:
			{
				Enemy * bigPlane = Enemy::create();
				switch (rand() % 5)
				{
					case 1:bigPlane->bindEnemySprite("bigenemy1.png", BIG_MAXLIFE); break;
					case 2:bigPlane->bindEnemySprite("bigenemy2.png", BIG_MAXLIFE); break;
					case 3:bigPlane->bindEnemySprite("bigenemy3.png", BIG_MAXLIFE); break;
					case 4:bigPlane->bindEnemySprite("bigenemy4.png", BIG_MAXLIFE); break;
					default:bigPlane->bindEnemySprite("bigenemy5.png", BIG_MAXLIFE); break;
				}
				bigVec.pushBack(bigPlane);
				addChild(bigPlane);

				float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - bigPlane->getContentSize().width) + bigPlane->getContentSize().width / 2;
				float y = SCREEN_SIZE.height + bigPlane->getContentSize().height / 3;

				Point bigBirth = Vec2(x, y);
				bigPlane->setPosition(bigBirth);
				MoveTo *	to = MoveTo::create(10, Vec2(bigBirth.x,
														 bigBirth.y - SCREEN_SIZE.height - bigPlane->getContentSize().height));
				auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeBigEnemy, this, bigPlane));
				Sequence * sequence = Sequence::create(to, actionDone, NULL);
				bigPlane->runAction(sequence);
				break;
			}
	}
}

void  EnemyLayer::bigEnemyBlowUp(Enemy * bigEnemy)		//大敌机爆炸
{
	GET_MUSIC_INSTANCE->playEffect("music/smallenemyboom.wav");
	Animate * bigAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("BlowUp"));
	auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeBigEnemy, this, bigEnemy));
	Sequence *sequence = Sequence::create(bigAnimate, actionDone, NULL);
	bigEnemy->runAction(sequence);
}

void  EnemyLayer::removeBigEnemy(Enemy* enemy)		//删除大敌机
{
	if (enemy)
	{
		enemy->removeFromParentAndCleanup(true);
		bigVec.eraseObject(enemy);
	}
}
void EnemyLayer::removeAllBigEnemy()
{
	for (auto enemy : bigVec)
	{
		if (enemy->getLife() >= 1)
		{
			bigEnemyBlowUp(enemy);
		}
	}
}

//////////////////////////////////处理boss//////////////////////////////////////////
//
void EnemyLayer::addBossEnemy(float dt)
{
	is_boss_come = true;

	//用于选择boss飞机
	Enemy * bossPlane = Enemy::create();

	switch (level)
	{
		case 1:bossPlane->bindEnemySprite("boss1.png", BOSS_MAXLIFE1); break;
		case 2:bossPlane->bindEnemySprite("boss2.png", BOSS_MAXLIFE2); break;
		case 3:bossPlane->bindEnemySprite("boss3.png", BOSS_MAXLIFE3); break;
		case 4:bossPlane->bindEnemySprite("boss4.png", BOSS_MAXLIFE4); break;
		case 5:bossPlane->bindEnemySprite("boss5.png", BOSS_MAXLIFE5); break;
		case 6:bossPlane->bindEnemySprite("boss6.png", BOSS_MAXLIFE6); break;
	}
	bossVec.pushBack(bossPlane);
	addChild(bossPlane);

	float x = SCREEN_SIZE.width / 2;
	float y = SCREEN_SIZE.height + bossPlane->getBoundingBox().size.height / 5;

	Point bossBirth = Vec2(x, y);
	bossPlane->setPosition(bossBirth);

	//运功
	MoveTo *to = MoveTo::create(2, Vec2(SCREEN_SIZE.width / 2,
										SCREEN_SIZE.height - bossPlane->getContentSize().height / 2));

	auto left = MoveTo::create(2, Vec2(bossPlane->getContentSize().width / 2, SCREEN_SIZE.height - bossPlane->getContentSize().height / 2));
	auto right = MoveTo::create(4, Vec2(SCREEN_SIZE.width - bossPlane->getContentSize().width / 2, SCREEN_SIZE.height - bossPlane->getContentSize().height / 2));
	auto sequence = Sequence::create(left, right, NULL);

	bossPlane->runAction(Sequence::create(to, NULL));
	bossPlane->runAction(RepeatForever::create(sequence));
}

void EnemyLayer::bossEnemyBlowUp(Enemy * bossEnemy)
{
	is_boss_come = false;
	GET_MUSIC_INSTANCE->playEffect("music/effect_bigBoom.wav");
	Animate * bossAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("BlowUp"));
	auto actionDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeBossEnemy, this, bossEnemy));
	auto stop = CallFunc::create(CC_CALLBACK_0(EnemyLayer::callUnschedule, this));
	Sequence *sequence = Sequence::create(bossAnimate, actionDone, stop, NULL);
	bossEnemy->runAction(sequence);
	scheduleOnce(schedule_selector(EnemyLayer::callWin), 3.0f);
	unscheduleUpdate();
	removeAllEnemyBullet();
	removeAllEnemy();
}

void EnemyLayer::removeBossEnemy(Enemy* enemy)
{
	if (enemy)
	{
		enemy->removeFromParentAndCleanup(true);
		bossVec.eraseObject(enemy);
	}
}

void EnemyLayer::callWin(float dt)
{
	if (level == 6)
	{
		Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, WinAllScene::createScene()));
	}
	else
	{
		Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, WinScene::createScene()));
	}
}

void EnemyLayer::callUnschedule()
{
	unschedule(schedule_selector(EnemyLayer::addNormalSmallEnemy));
	unschedule(schedule_selector(EnemyLayer::addTraceSmallEnemy));
	unschedule(schedule_selector(EnemyLayer::addNormalBigEnemy));
	unschedule(schedule_selector(EnemyLayer::shoot));
}