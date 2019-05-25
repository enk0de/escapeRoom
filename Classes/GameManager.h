#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <string>
#include <fstream>

USING_NS_CC;

using namespace experimental;

class GameManager : public cocos2d::Scene {
private:
	GameManager() {};
	~GameManager() {};
	static GameManager* instance;

	std::string now;
	std::string filename;
	std::string script[200];

	
	float m_stayingTime;
	int audioId;
	int effectId;


public:
	int m_Indicator;
	void initializing();

	static GameManager* GetInstance()
	{
		if (instance == nullptr) instance = new GameManager();
		return instance;
	}

	static void PurgeInstance()
	{
		delete instance;
		instance = nullptr;
	}

	void ReadScript(std::ifstream* scr);
	void ScriptParser(float delta);

	float GetStayingTime();

	std::string GetNow();
	void GoToMonologueScene(float FadingTime, std::string String, bool IsAuto, bool IsType);
	void GoToDialogueScene(std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, bool);

	void DisableDelay(float f);

	std::string GetNextScript();
};
