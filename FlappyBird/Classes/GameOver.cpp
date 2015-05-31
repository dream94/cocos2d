#include "GameOver.h"

USING_NS_CC;

GameOver::GameOver(void)
{
}


GameOver::~GameOver(void)
{
}


bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	//计分板
	panel = Sprite::createWithSpriteFrameName("score_panel.png");
	panel->setPosition(Point(origin.x+visibleSize.width/2,origin.y-visibleSize.height/2));
	this->addChild(panel);

	//计分板动画
	auto moveto = MoveTo::create(0.6f,Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.5));
	auto callback = CallFuncN::create(CC_CALLBACK_0(GameOver::callBack,this));
	auto sequence = Sequence::create(moveto,callback,NULL);
	panel->runAction(sequence);

	//gameover标题
	auto gameover = Sprite::createWithSpriteFrameName("text_game_over.png");
	gameover->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height+gameover->getContentSize().height/2));

	//gameover精灵也要执行相同的动画，不过它是从上到下运动
	auto moveto2 = MoveTo::create(0.6f,Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.7));

	gameover->runAction(moveto2);
	this->addChild(gameover);

	return true;
}

void GameOver::callBack()
{
	//排名和再来一次按钮
	//计分板和gameover精灵执行完动画后，出现按钮
	auto again = Sprite::createWithSpriteFrameName("button_play.png");
	auto menuAgain = MenuItemSprite::create(again,again,CC_CALLBACK_0(GameOver::gameAgain,this));

	auto rank = Sprite::createWithSpriteFrameName("button_score.png");
	auto menuRank = MenuItemSprite::create(rank,rank,CC_CALLBACK_0(GameOver::getRank,this));

	//两个按钮坐标的设定
	int l = (visibleSize.width-again->getContentSize().width*2)/3;

	menuAgain->setPosition(Point(origin.x+l+again->getContentSize().width/2,origin.y+visibleSize.height*0.3));
	menuRank->setPosition(Point(origin.x+visibleSize.width-l-again->getContentSize().width/2,origin.y+visibleSize.height*0.3));

	//把按钮放到菜单中去
	auto menu = Menu::create(menuAgain,menuRank,NULL);
	menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//分数显示
	scores = 0;
	auto str = __String::createWithFormat("%d",scores);
	numberLabel = Label::createWithBMFont("D:\\hello\\Bird\\Resources\\num2.fnt",str->getCString());
	numberLabel->setPosition(Point(origin.x+visibleSize.width/2+65,origin.y+visibleSize.height*0.5+10));
	this->addChild(numberLabel);

	//设置奖牌
	int l2 = (visibleSize.width-panel->getContentSize().width)/2;
	Sprite * medals;
	medals = Sprite::createWithSpriteFrameName("medals_1.png");
	medals->setPosition(Point(origin.x+l2+54,origin.y+visibleSize.height*0.49));
	this->addChild(medals);
}

//切换回游戏场景
void GameOver::gameAgain()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,GameScene::createScene()));
}

//结束游戏
void GameOver::getRank()
{
	Director::getInstance()->end();
}
