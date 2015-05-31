#pragma once

#include "cocos2d.h"
#include "Score.h"
#include "GameScene.h"

USING_NS_CC;

class GameOver:public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();
	bool init();
	//回调函数
	void callBack();
	//再来一次
	void gameAgain();
	//获取排名
	void getRank();
	//显示分数
	void showScore(float);
	CREATE_FUNC(GameOver);

private:

	Size visibleSize;
	Point origin;

	Sprite *panel ;

	Label * numberLabel;
	//用于初始化分数
	int scores;
	
};
