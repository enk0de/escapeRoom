#pragma once
#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "MonologueScene.h"
#include "DialogueScene.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <fstream>

USING_NS_CC;

class MainGameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainGameScene);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	void DisableDelay(float f);
	void EndScene(float f);

	void update(float f);

	void GoScript(float f);
	~MainGameScene();

private:
	GameManager* Game;
};

#endif