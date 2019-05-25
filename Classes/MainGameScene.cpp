/*

	ToDo List//

	1. 그 다음 명령어가 그 전의 명령어와 같을 경우 페이드아웃-페이드인 없이
	2. 씬 전환에 Transition effect 사용 시 오류 발생하는 문제 해결하기
	3. HelloWorld -> MainGame 전환 시 음악 부드럽게 정지

*/

#include "MainGameScene.h"

using namespace experimental;

Scene* MainGameScene::createScene()
{
	return MainGameScene::create();
}

bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	IsStay = false;
	   
	Game = GameManager::GetInstance();
	Game->initializing();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MainGameScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 배경  
	auto wlayer = LayerColor::create(Color4B(0, 0, 0, 255));

	//this->scheduleOnce(schedule_selector(MainGameScene::GoScript), 0.1f);
	this->scheduleUpdate();
	this->addChild(wlayer);

	return true;
}

void MainGameScene::update(float f)
{
	std::string now = Game->GetNow();

	if (now == "START!" || (now != "MONO_" && now != "AUTO_MONO_" && now != "DIAL_" && now != "DELAY_STAY_" && now != "DELAY_"))
	{
		GoScript(0);
	}
	else if (now == "DELAY_STAY_") { IsStay = true; }
	else if (now == "DELAY_" && IsStay == false)
	{
		IsStay = true;
		this->scheduleOnce(schedule_selector(MainGameScene::GoScript), Game->GetStayingTime());
	}
}

void MainGameScene::GoScript(float f)
{
	IsStay = false;
	Game->ScriptParser(0);
}

bool MainGameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (IsStay && Game->GetNow() == "DELAY_STAY_")
	{
		GoScript(0);
		return true;
	}
	else
		return false;
}


void MainGameScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void MainGameScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
}

void MainGameScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}

MainGameScene::~MainGameScene()
{
	Game->PurgeInstance();
	AudioEngine::end();
}

