#pragma once
#include "cocos2d.h"
#include "LabelTypingEffect.h"
#include "GameManager.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif
class MonologueScene : public cocos2d::Scene
{
public:
	float m_Time;
	
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	static MonologueScene* create(float, std::string, bool, bool);

	static cocos2d::Scene* createScene(float, std::string, bool, bool);

	virtual bool init(float, std::string, bool, bool);

	void EndScene(float f);
	void ChangeText(std::string);
	void FadeOut(float f);
	void SetTime(float f);
	
	//CREATE_FUNC(MonologueScene);

private:
	GameManager* Game;
	bool m_IsType;
	bool m_IsTouched;
	bool m_IsAuto;
	std::string m_Text;
};

