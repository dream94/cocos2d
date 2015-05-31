#pragma once
#include "cocos2d.h"

USING_NS_CC;

//Ð¡ÄñµÄÈýÖÖ×´Ì¬
typedef enum 
{
	IDLE, //¿ÕÏÐ×´Ì¬£º²»ÊÜÖØÁ¦Ó°Ïì
	FLY,  //·ÉÐÐ×´Ì¬£ºÊÜÖØÁ¦Ó°Ïì
	DIE	  //ÉèÖÃÏÂÂä·½Ïò

}birdState;



class aBird : public Layer
{

public:

	static aBird* createBird();

	virtual bool init();
	CREATE_FUNC(aBird);

	void stateChange(birdState st);
	void idle();
	void fly();
	void die();

	void update(float);

private:

	Size visibleSize;
	Point origin;

	Sprite *bird;
	EventListenerTouchOneByOne *listener;


};