#pragma once
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif
class DialogueScene : public cocos2d::Scene
{
public:
	static DialogueScene* create(std::string, std::string, std::string, std::string, std::string, bool);
	static cocos2d::Scene* createScene(std::string, std::string, std::string, std::string, std::string, bool);
	virtual bool init(std::string, std::string, std::string, std::string, std::string, bool);

	void EndScene(float f);
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	void changeBgURL(std::string);
	void changeName(std::string);
	void changeText(std::string);
	void changeCharURL(std::string);

	GameManager* Game;

	//CREATE_FUNC(DialogueScene);

private:
	bool m_IsTouched;
	std::string m_NextText;
	std::string m_Where;
	std::string m_BgURL;
	std::string m_Name;
	std::string m_Text;
	std::string m_CharURL;
};

