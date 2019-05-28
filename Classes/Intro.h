#ifndef __INTRO_H__
#define __INTRO_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
class Intro : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float);
	~Intro();
	CREATE_FUNC(Intro);

private:
	bool isSceneOn;
	int opacity;
};

#endif