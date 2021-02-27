#include "FoodLayer.h"

bool FoodLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	schedule(schedule_selector(FoodLayer::addBomb), 15.0f);
	schedule(schedule_selector(FoodLayer::addLife), 11.0f);

	return true;
}

void FoodLayer::addBomb(float dt)
{
	switch (rand() % 5)
	{
		case 0:
		case 4:
			{
				auto bomb = Sprite::createWithSpriteFrameName("bomb.png");
				float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - bomb->getContentSize().width) + bomb->getContentSize().width / 2;
				float y = bomb->getContentSize().height + SCREEN_SIZE.height;
				Point birthplace = Vec2(x, y);
				bomb->setPosition(Vec2(birthplace));
				bombVec.pushBack(bomb);
				addChild(bomb, 1);
				auto to = MoveTo::create(2.5, Vec2(x, -bomb->getContentSize().height));
				auto func = CallFunc::create(CC_CALLBACK_0(FoodLayer::removeBomb, this, bomb));

				bomb->runAction(Sequence::create(to, func, NULL));
				break;
			}
		default:
			break;
	}
}
void FoodLayer::addLife(float dt)
{
	auto life = Sprite::createWithSpriteFrameName("heart.png");
	float x = CCRANDOM_0_1()*(SCREEN_SIZE.width - life->getContentSize().width) + life->getContentSize().width / 2;
	float y = life->getContentSize().height + SCREEN_SIZE.height;
	Point birthplace = Vec2(x, y);
	life->setPosition(Vec2(birthplace));
	lifeVec.pushBack(life);
	addChild(life, 1);
	auto to = MoveTo::create(2.5, Vec2(x, -life->getContentSize().height));
	auto func = CallFunc::create(CC_CALLBACK_0(FoodLayer::removeLife, this, life));

	life->runAction(Sequence::create(to, func, NULL));
}

void FoodLayer::removeBomb(Sprite * bomb)
{
	if (bomb)
	{
		bombVec.eraseObject(bomb);
		bomb->removeFromParentAndCleanup(true);
	}
}
void FoodLayer::removeLife(Sprite * life)
{
	if (life)
	{
		lifeVec.eraseObject(life);
		life->removeFromParentAndCleanup(true);
	}
}