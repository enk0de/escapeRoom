#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Commons.h"
#include "MonologueScene.h"
#include "DialogueScene.h"
#include "AudioEngine.h"
#include <iostream>
#include <string>
#include <fstream>

enum ScriptingInd
{
	MONO_, AUTO_MONO_, DIAL_, MUSIC_PLAY_, MUSIC_STOP_, MUSIC_PAUSE_, MUSIC_RESUME_, SHOW_IMAGE_, HIDE_IMAGE_, DELAY_
};

class MainGameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainGameScene);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	void ReadScript(std::ifstream* scr);
	void Scripting(float delta);

	void DisableDelay(float f);
	void EndScene(float f);
	void GoToMonologueScene(Ref* pSender, float FadingTime, std::string String, bool IsAuto, bool IsType);
	void GoToDialogueScene(Ref* pSender, std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, std::string NextText, bool);

	~MainGameScene();

private:
	ScriptingInd ScrInd;
	int audioId;
	cocos2d::Size			winSize;
	cocos2d::Vec2			characterPosition;
	cocos2d::Sprite* character;
	cocos2d::TMXTiledMap* tilemap;

	std::string filename;
	std::string script[200];

	int m_Indicator;
	bool m_IsDelayStay;
};

#endif