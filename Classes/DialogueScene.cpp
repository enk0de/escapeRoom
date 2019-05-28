#include "DialogueScene.h"
#include "LabelTypingEffect.h"

using namespace experimental;
// INSTEAD OF CREATE_FUNC(~);
DialogueScene* DialogueScene::create(std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, bool IsAnimation)
{
	DialogueScene* pRet = new(std::nothrow) DialogueScene();
	if (pRet && pRet->init(Where, Name, Text, BgURL, CharURL, IsAnimation))
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

Scene* DialogueScene::createScene(std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, bool IsAnimation)
{
	return DialogueScene::create(Where, Name, Text, BgURL, CharURL, IsAnimation);
}

bool DialogueScene::init(std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, bool IsAnimation)
{
	if (!Scene::init())
	{
		return false;
	}

	this->setName("Dialogue");
	auto a =
	this->getName();
	Game = GameManager::GetInstance();

	TTFConfig Name_Font("fonts/NanumBarunGothic.ttf", 60);
	TTFConfig Text_Font("fonts/NanumBarunGothic.ttf", 50);
	
	m_Where = Where;
	m_IsTouched = false;
	changeName(Name);
	changeText(Text);
	changeBgURL(BgURL);
	changeCharURL(CharURL);

	// Touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(DialogueScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(DialogueScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(DialogueScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(DialogueScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Objects
	auto dialogueBg = Sprite::create(m_BgURL); // 검은 배경
	auto chatBg = Sprite::create("Images/Dialogue.png");
	auto name = Label::createWithTTF(Name_Font, m_Name, TextHAlignment::LEFT);
	auto text = Label::createWithTTF(Text_Font, m_Text, TextHAlignment::LEFT);
	auto character = Sprite::create(m_CharURL);


	auto fadein = FadeIn::create(0.4f);
	auto fadein_name = FadeIn::create(0.6f);
	auto fadein_char = FadeIn::create(0.6f);
	auto up = MoveTo::create(0.2f, Vec2(0, 0));
	auto up_name = MoveTo::create(0.2f, Vec2(50, 166));
	auto up_text = MoveTo::create(0.2f, Vec2(50, 50));
	auto up_char = MoveTo::create(0.3f, Vec2(1400, 440));
	auto easeinout = EaseInOut::create(up->clone(), 3.0f);
	auto easeinout_name = EaseInOut::create(up_name->clone(), 3.0f);
	auto easeinout_text = EaseInOut::create(up_text->clone(), 3.0f);
	auto easeinout_char = EaseInOut::create(up_char->clone(), 3.0f);

	// Value
	dialogueBg->setPosition(Vec2(960, 540));
	dialogueBg->setAnchorPoint(Vec2(0.5, 0.5));

	if (IsAnimation)
	{
		chatBg->setPosition(Vec2(0, -40));
		chatBg->setOpacity(0);
		chatBg->setAnchorPoint(Vec2(0, 0));
		chatBg->runAction(fadein);
		chatBg->runAction(easeinout);
		name->setTextColor(Color4B(181, 166, 166, 255));
		name->setOpacity(0);
		name->setPosition(Vec2(50, 126));
		name->setAnchorPoint(Vec2(0, 0));
		name->runAction(fadein_name);
		name->runAction(easeinout_name);
		text->setTextColor(Color4B(255, 255, 255, 255));
		text->setPosition(Vec2(50, 10));
		text->setAnchorPoint(Vec2(0, 0));
		text->runAction(easeinout_text);
		character->setPosition(Vec2(1480, 440));
		character->setOpacity(0);
		character->runAction(fadein_char);
		character->runAction(easeinout_char);
	}
	else
	{
		chatBg->setPosition(Vec2(0, 0));
		chatBg->setAnchorPoint(Vec2(0, 0));
		name->setTextColor(Color4B(181, 166, 166, 255));
		name->setPosition(Vec2(50, 166));
		name->setAnchorPoint(Vec2(0, 0));
		name->runAction(fadein_name);
		name->runAction(easeinout_name);
		text->setTextColor(Color4B(255, 255, 255, 255));
		text->setPosition(Vec2(50, 50));
		text->setAnchorPoint(Vec2(0, 0));
		character->setPosition(Vec2(1480, 440));
		character->setOpacity(0);
		character->runAction(fadein_char);
		character->runAction(easeinout_char);
	}

	LabelTypingEffect::typeMessage(text, m_Text, 0.04f);

	// Childize
	this->addChild(dialogueBg);
	this->addChild(character);
	this->addChild(chatBg);
	this->addChild(text);
	this->addChild(name);

	return true;
}

void DialogueScene::changeBgURL(std::string p)
{
	m_BgURL = p;
}

void DialogueScene::changeName(std::string p)
{
	m_Name = p;
}

void DialogueScene::changeText(std::string p)
{
	m_Text = p;
}

void DialogueScene::changeCharURL(std::string p)
{
	m_CharURL = p;
}


bool DialogueScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (Game->m_IsSelection == false)
	{
		Director::getInstance()->popScene();
		Game->ScriptParser(0);
	}
	return true;
}

void DialogueScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void DialogueScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
}

void DialogueScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}