#pragma once
#include "cocos2d.h"
#include "Land.h"
#include "aBird.h"
#include "Pipe.h"
#include "Guide.h"
#include "Score.h"
#include "GameOver.h"
#include <cstdlib>

USING_NS_CC;

class GameScene : public Layer
{
public:
	GameScene(void);
	~GameScene(void);

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	void startGame();
	
	//¼àÌýÐ¡ÄñÊÇ·ñµÃ·Ö£¬»òÔòËµ¹Ü×ÓµÄxÊÇ·ñ¹ýÆÁÄ»ÖÐÏß
	void update(float dt);


private:

	Size visibleSize;
	Point origin;

	aBird *bird;
	Pipe  *pipe;
	Score *score;

	EventListenerPhysicsContact *contactListener;
};

