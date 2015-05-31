#include "Score.h"

USING_NS_CC;
//唯一静态对象，类似WelcomeScene
static Score *instance = NULL;

Score::Score(void)
{
}
Score::~Score(void)
{
}

Score *Score::getInstance()
{
	//判断这个对象是否存在
	if (instance==NULL)
	{
		//如果不存在，那就创建
		Score *temp=new Score();
		//然后初始化
		temp->init();
		instance=temp;
	}
	//如果已经存在了，那就直接返回
	return instance;
}

bool Score::init()
{
	auto origin=Director::getInstance()->getVisibleOrigin();
    auto visibleSize=Director::getInstance()->getVisibleSize();
	//一开始显示0
	score = 0;
	auto str=__String::createWithFormat("%d",score);
	label = LabelBMFont::create(str->getCString(),"D:\\hello\\Bird\\Resources\\num.fnt");
	label->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.85));
	this->addChild(label);

	return true;
}


void Score::addScore()
{
	++score;
	auto str=__String::createWithFormat("%d",score);
	label->setString(str->getCString());
}

void Score::resetScore()
{
	score = 0;
	auto str=__String::createWithFormat("%d",score);
	label->setString(str->getCString());
}

int Score::getScore()
{
	return score;
}