#include "MyPlaneBulletLayer.h"

bool MyPlaneBulletLayer::init()
{
	if (!Layer::init()) { return false; };

	startShoot();

	return true;
}

void MyPlaneBulletLayer::startShoot()
{
	schedule(schedule_selector(MyPlaneBulletLayer::addBulletCallback), 0.10f);
}

void MyPlaneBulletLayer::stopShoot()
{
	unschedule(schedule_selector(MyPlaneBulletLayer::addBulletCallback));
}

void MyPlaneBulletLayer::addBulletCallback(float dt)
{
	if (MyplaneLayer::_hero)
	{
		//在另外一个层里，获得飞机的单例
		Sprite *hero = MyplaneLayer::getHero();
		if (hero)
		{
			Point birthPlace = hero->getPosition() + Vec2(0, hero->getContentSize().height / 2 + 15);
			Sprite * bullet;
			switch (Myplane::is_plane1)
			{
				case true:
					{
						bullet = Sprite::createWithSpriteFrameName("bullet1.png");
						bulletVec.pushBack(bullet);
						break;
					}
				default:
					{
						bullet = Sprite::createWithSpriteFrameName("bullet2.png");
						bulletVec.pushBack(bullet);
						break;
					}
			}
			addChild(bullet);
			bullet->setPosition(birthPlace);

			float ditance = SCREEN_SIZE.height - hero->getPositionY() - hero->getContentSize().height / 2;
			float velocity = SCREEN_SIZE.height / 1;
			float movedt = ditance / velocity;

			MoveTo *to = MoveTo::create(movedt, Vec2(birthPlace.x, SCREEN_SIZE.height - bullet->getContentSize().height / 2));
			auto actionDone = CallFunc::create(CC_CALLBACK_0(MyPlaneBulletLayer::removeBullet, this, bullet));

			Sequence * sequence = Sequence::create(to, actionDone, NULL);

			bullet->runAction(sequence);
		}
	}
}

void MyPlaneBulletLayer::removeBullet(Sprite* bullet)
{
	if (bullet)
	{
		bullet->removeFromParentAndCleanup(true);

		bulletVec.eraseObject(bullet);
	}
}