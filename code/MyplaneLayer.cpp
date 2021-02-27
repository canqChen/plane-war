#include "MyplaneLayer.h"
Myplane * MyplaneLayer::_hero = NULL;
bool MyplaneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addHero();

	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	return true;
}

void MyplaneLayer::addHero()
{
	if (level != 1)
	{
		_hero = NULL;
	}
	if (!_hero)
	{
		_hero = Myplane::create();
		_hero->setPosition(Vec2(SCREEN_SIZE.width / 2, _hero->getContentSize().height / 2 + 42));
		addChild(_hero);
	}
}

Myplane* MyplaneLayer::getHero()
{
	return _hero;
}

bool MyplaneLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Rect planeRect = _hero->getBoundingBox();
	planeRect.origin.x -= 30;
	planeRect.origin.y -= 40;
	planeRect.size.width += 60;
	planeRect.size.height += 80;
	if (planeRect.containsPoint(pTouch->getLocation()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void MyplaneLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	if (_hero)
	{
		Point positon = _hero->getPosition() + pTouch->getDelta();
		if (positon.x < _hero->getBoundingBox().size.width / 2 ||
			positon.x > SCREEN_SIZE.width - _hero->getBoundingBox().size.width / 2 ||
			positon.y <_hero->getBoundingBox().size.height / 2 + 42 ||
			positon.y > SCREEN_SIZE.height - _hero->getBoundingBox().size.height / 2)
		{
			return;
		}
		else
		{
			_hero->setPosition(positon);
		}
	}
}