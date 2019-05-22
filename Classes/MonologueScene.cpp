#include "MonologueScene.h"

// INSTEAD OF CREATE_FUNC(~);
MonologueScene* MonologueScene::create(float f, std::string s, bool IsAuto, bool IsType)
{
	MonologueScene* pRet = new(std::nothrow) MonologueScene();
	if (pRet && pRet->init(f, s, IsAuto, IsType))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

Scene* MonologueScene::createScene(float f, std::string s, bool IsAuto, bool IsType)
{
	return MonologueScene::create(f, s, IsAuto, IsType);
}

bool MonologueScene::init(float f, std::string s, bool IsAuto, bool IsType)
{
	if (!Scene::init())
	{
		return false;
	}

	// Initializing
	m_IsType = IsType;
	m_IsTouched = false;
	m_IsAuto = IsAuto;
	m_Time = f;
	ChangeText(s);

	TTFConfig Text_Font("fonts/NanumBarunGothic.ttf", 50);

	// Objects
	auto bg = LayerColor::create(Color4B(0, 0, 0, 255)); // 검은 배경
	auto text = Label::createWithTTF(Text_Font, m_Text, TextHAlignment::LEFT);
	auto fadein = FadeIn::create(1.0f);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(MonologueScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MonologueScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MonologueScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MonologueScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Value
	text->setTextColor(Color4B(255, 255, 255, 255));
	text->setPosition(Vec2(960, 540));
	text->setAnchorPoint(Vec2(0.5, 0.5));
	if (m_IsType)
	{
		LabelTypingEffect::typeMessage(text, m_Text, 0.1f);
	}
	else
	{
		text->setOpacity(0);
		text->runAction(fadein);
	}
	text->setName("MonologueText");

	// Childize
	this->addChild(bg);
	this->addChild(text);



	// Scheduler
	if (IsAuto)
	{
		this->scheduleOnce(schedule_selector(MonologueScene::FadeOut), m_Time + 1.0f);
		this->scheduleOnce(schedule_selector(MonologueScene::EndScene), m_Time + 2.0f);
	}

	return true;
}

bool MonologueScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!m_IsTouched && this->getChildByName("MonologueText")->getOpacity() == 255)
	{
		MonologueScene::FadeOut(0);
		this->scheduleOnce(schedule_selector(MonologueScene::EndScene), 1.0f);
		return true;
	}
	else
		return false;
}

void MonologueScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void MonologueScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
}

void MonologueScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}



void MonologueScene::ChangeText(std::string p)
{
	m_Text = p;
}

void MonologueScene::FadeOut(float f)
{
	auto fadeout = FadeOut::create(1.0f);
	this->getChildByName("MonologueText")->runAction(fadeout);
}

void MonologueScene::EndScene(float f = 0)
{
	Director::getInstance()->popScene();
}

void MonologueScene::SetTime(float f)
{
	m_Time = f;
}