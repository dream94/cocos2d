#include "Pipe.h"

USING_NS_CC;

Pipe::Pipe(void)
{
}
Pipe::~Pipe(void)
{
}

bool Pipe::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addPipe();

	return true;
}

void Pipe::addPipe()
{
	//启动定时器，移动管子
	schedule(schedule_selector(Pipe::movePipe),0.01f);

	//每次出现2根管子
	for (int i = 0; i < 2; i++) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite *pipUp = Sprite::create("D:\\hello\\Bird\\Resources\\pipe_up.png");
		Sprite *pipDown = Sprite::create("D:\\hello\\Bird\\Resources\\pipe_down.png");
        Node *singlePip = Node::create();
        
        // 把2跟根子合成一个Node对象
        pipDown->setPosition(0, 320 + 100);
		singlePip->addChild(pipDown, 0, 12);
        singlePip->addChild(pipUp, 0, 21);
        singlePip->setPosition(visibleSize.width + i*180 + 100, this->getRandomHeight());
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, 320 + 100));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
		body->setDynamic(false);
        body->setCategoryBitmask(0x1<<2);
        body->setCollisionBitmask(0x1);
        body->setContactTestBitmask(0x1);
		singlePip->setPhysicsBody(body);
        singlePip->setTag(31);
        
        this->addChild(singlePip);
        this->pips.push_back(singlePip);
    }
}

void Pipe::movePipe(float t)
{
	for (auto singlePip : this->pips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -52) {
            singlePip->setTag(31);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
        }
    }
}

void Pipe::stopPipe()
{
	this->unschedule(schedule_selector(Pipe::movePipe));
}


int Pipe::getRandomHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand()%(int)(2*320 + 100 - visibleSize.height);
}

