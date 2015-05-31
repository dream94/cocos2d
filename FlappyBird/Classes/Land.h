#pragma once
#include "cocos2d.h"
#include "Pipe.h"

USING_NS_CC;

class Land : public Layer 
{
public:
	Land(void);
	~Land(void);

	virtual bool init();
	CREATE_FUNC(Land);

	//地面开始滚动
	void landMove(float);
	//地面停止滚动
	void landStop();

private:
	Sprite *land1;
	Sprite *land2;
	
};

