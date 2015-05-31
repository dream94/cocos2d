#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Guide : public Layer
{
public:
	Guide(void);
	~Guide(void);
	
	virtual bool init();
	CREATE_FUNC(Guide);
	
	void rmGuide();

private:
	
	EventListenerTouchOneByOne * listener;
	Sprite * title;
	Sprite * guide;
};

