#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//ÉèÖÃÊÀ½çÖØÁ¦¼ÓËÙ¶È£¨0£¬-980£©
	scene->getPhysicsWorld()->setGravity(Point(0,-980));
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;

} 

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    origin=Director::getInstance()->getVisibleOrigin();
	visibleSize=Director::getInstance()->getVisibleSize();

	//Ìí¼Ó±³¾°²ã
	auto bg = Sprite::createWithSpriteFrameName("bg_day.png");
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	addChild(bg);

	//Ìí¼ÓÍæ·¨Ö¸µ¼ºÍ±êÌâ
	auto guide = Guide::create();
	addChild(guide);

	//Ìí¼Ó²ÝµØ²ã
	auto land = Land::create();
	land->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	land->setPosition(Point::ZERO);
	this->addChild(land,2);

	//Ìí¼ÓÐ¡Äñ²ã
	bird = aBird::createBird();
	bird->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	bird->setPosition(Point::ZERO);
	bird->setTag(10);
	this->addChild(bird);
	bird->stateChange(IDLE);


	//´´½¨µã»÷¼àÌý£¬µã»÷ÁË¾Í¿ªÊ¼ÓÎÏ·£¬²¢ÒÆ³ý¼àÌý
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [=](Touch *t, Event *e)
	{
		return true;
	};
	listener->onTouchEnded = [=](Touch *t, Event *e)
	{
		guide->rmGuide();
		startGame();
		//Ìí¼Ó·ÖÊý
		score = Score::create();
		addChild(score);

		//Ìí¼ÓË®¹Ü²ã
		pipe = Pipe::create();
		pipe->setTag(5);
		this->addChild(pipe);
		_eventDispatcher->removeEventListener(listener);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	//´´½¨Åö×²¼àÌý
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](const PhysicsContact& contact)
	{
		land->landStop();
		pipe->stopPipe();
		bird->stateChange(DIE);

		//Ìí¼ÓGameOver²ã
		auto over = GameOver::create();
		addChild(over);

	    //½áÊøµÃ·Ö¼àÌý
		this->unscheduleUpdate();
	
		//½áÊøÅö×²¼àÌý
		_eventDispatcher->removeEventListener(contactListener);

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	return true;
}

void GameScene::startGame()
{
	//ÓÎÏ·¿ªÊ¼£¬Ð¡Äñ×ª»»µ½·ÉÐÐ×´Ì¬
	bird->stateChange(FLY);
	this->scheduleUpdate();
}

//¼àÌýµÃ·ÖÇé¿ö
void GameScene::update(float dt)
{
	float positionX;
	positionX = this->getChildByTag(5)->getChildByTag(31)->getPositionX();
	if (positionX < visibleSize.width/2-50)
		score->addScore();
}