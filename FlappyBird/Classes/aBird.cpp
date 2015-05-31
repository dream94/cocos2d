#include "aBird.h"

USING_NS_CC;

bool aBird::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	visibleSize=Director::getInstance()->getVisibleSize();
	origin=Director::getInstance()->getVisibleOrigin();
	
	//创建小鸟动画
	auto bird_animation = Animation::create();
	bird_animation->setDelayPerUnit(0.1f);
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_0.png"));
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_1.png"));
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_2.png"));

	auto bird_animate = Animate::create(bird_animation);
	auto repeat = RepeatForever::create(bird_animate);

    bird = Sprite::createWithSpriteFrameName("bird0_0.png");
	bird->setPosition(visibleSize.width/2,visibleSize.height/2);
	bird->runAction(repeat);

	//创建小鸟Body
	auto bird_body = PhysicsBody::create();
	auto bird_shape = PhysicsShapeCircle::create(15);
	bird_body->addShape(bird_shape);
	bird_body->setDynamic(true);
	bird_body->setGravityEnable(false);
	bird_body->setLinearDamping(0.7f);
	bird_body->setCategoryBitmask(1);
	bird_body->setCollisionBitmask(-1);
	bird_body->setContactTestBitmask(-1);
	bird->setPhysicsBody(bird_body);
	bird->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.6));
	addChild(bird);

	//添加点击事件
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [this](Touch *t, Event *e)
	{
		return true;//设成true,启动往下的touch方法
	};

	listener->onTouchEnded = [this](Touch *t, Event *e)
	{
		//每点击一下向上飞
		bird->getPhysicsBody()->setVelocity(Point(0,260));	
	};

	//开启定时器监听,防止小鸟飞出边界
	this->scheduleUpdate();
	
	return true;
}


aBird* aBird::createBird()
{
	aBird *temp = new aBird();
	temp->init();
	return temp;
}

void aBird::stateChange(birdState st)
{
	switch (st)
	{
	case IDLE:
		idle();break;
	case FLY:
		fly();break;
	case DIE:
		die();break;
	default:
		break;
	}
}

void aBird::idle()
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,bird);
	bird->getPhysicsBody()->setGravityEnable(false);
}

void aBird::fly()
{
	bird->getPhysicsBody()->setGravityEnable(true);
}

void aBird::die()
{
	//关闭定时器
	this->unscheduleUpdate();
	//移除点击侦听
	_eventDispatcher->removeEventListener(listener);
	//开启重力感应（因为死亡后会自由落体.....）
	bird->getPhysicsBody()->setGravityEnable(true);
	//停止小鸟的所有动画
	bird->stopAllActions();
	//设置角度，头向下...
	bird->setRotation(90);
}

void aBird::update(float)
{
	//防止飞出边界
	if (bird->getPositionY()>(origin.y+visibleSize.height))
	{
		bird->setPositionY(origin.y+visibleSize.height);
	}
	//小鸟的飞行头部的角度，根据飞行的Y轴速度决定
	bird->setRotation(bird->getPhysicsBody()->getVelocity().y*-0.1);

}