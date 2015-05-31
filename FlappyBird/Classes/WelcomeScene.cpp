#include "WelcomeScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	//加载Plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("D:\\hello\\Bird\\Resources\\birdSucai.plist","D:\\hello\\Bird\\Resources\\birdSucai.png");
    
	//添加背景
	auto bg = Sprite::createWithSpriteFrameName("bg_day.png");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(bg);

	//添加标题
	auto title = Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(visibleSize.width/2,visibleSize.height/2+100);
	addChild(title);

	//添加小鸟动画
	auto bird_animation = Animation::create();
	bird_animation->setDelayPerUnit(0.1f);
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_0.png"));
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_1.png"));
	bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird0_2.png"));

	auto bird_animate = Animate::create(bird_animation);
	auto repeat = RepeatForever::create(bird_animate);

	auto bird = Sprite::createWithSpriteFrameName("bird0_0.png");
	bird->setPosition(visibleSize.width/2,visibleSize.height/2);
	bird->runAction(repeat);
	addChild(bird);

	//添加菜单项
	auto menuImage = Sprite::createWithSpriteFrameName("button_play.png");
	auto start_btn = MenuItemSprite::create(menuImage,menuImage,CC_CALLBACK_0(WelcomeScene::startGame,this));
	auto menu = Menu::create(start_btn,NULL);
	menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu->setPosition(Point(80,150));
	this->addChild(menu);

	auto menuImage2 = Sprite::createWithSpriteFrameName("button_score.png");
	auto end_btn = MenuItemSprite::create(menuImage2,menuImage2,CC_CALLBACK_1(WelcomeScene::menuCloseCallback,this));
	auto menu2 = Menu::create(end_btn,NULL);
	menu2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu2->setPosition(Point(200,150));
	this->addChild(menu2);

	//添加陆地
	auto land = Land::create();
	land->landMove(1);
	addChild(land);

	//添加版权
	auto copyRight = Sprite::createWithSpriteFrameName("brand_copyright.png");
	copyRight->setPosition(visibleSize.width/2,80);
	addChild(copyRight);

    return true;
}



void WelcomeScene::startGame()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
}

void WelcomeScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
