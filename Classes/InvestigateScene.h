#include "cocos2d.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif
class InvestigateScene : public cocos2d::Scene
{
public:
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	static InvestigateScene* create();

	static cocos2d::Scene* createScene();

	virtual bool init();

	void EndScene(float f);
private:
	bool m_IsTouched;
};

