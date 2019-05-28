#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "GameManager.h"
class HelloWorldScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorldScene);

	void DoStart(Ref* pSender);
	void DoExit(Ref* pSender);
	void PlayBGM(Ref* pSender);
	~HelloWorldScene();

	int audioId;

private:
	GameManager* Game;
};

#endif