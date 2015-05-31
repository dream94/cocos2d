#pragma once
#include "cocos2d.h"
#include <cstdlib>

USING_NS_CC;
using namespace std;

class Pipe : public Layer
{
public:
	Pipe(void);
	~Pipe(void);

	virtual bool init();
	CREATE_FUNC(Pipe);

	//添加管子
	void addPipe();
	//移动管子，类似Land层里面的moveLand
	void movePipe(float t);
	//停止移动管子
	void stopPipe();
	//获取随机高度
	int getRandomHeight();

private:
	
	//用来储存pipe对象
	 vector<Node *> pips;

};

