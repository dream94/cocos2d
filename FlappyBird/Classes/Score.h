#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Score : public Layer
{
public:
	Score(void);
	~Score(void);

	virtual bool init();
	CREATE_FUNC(Score);

	//加分
	void addScore();
	//重置分数,同时移除分数对象
	void resetScore();
	//获取分数
	int getScore();
	////获得单例对象
	static Score *getInstance();

private:
	
	int score;
	LabelBMFont *label;

};

