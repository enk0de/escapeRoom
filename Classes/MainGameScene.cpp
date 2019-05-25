/*

	ToDo List//

	1. �� ���� ��ɾ �� ���� ��ɾ�� ���� ��� ���̵�ƿ�-���̵��� ����
	2. �� ��ȯ�� Transition effect ��� �� ���� �߻��ϴ� ���� �ذ��ϱ�
	3. HelloWorld -> MainGame ��ȯ �� ���� �ε巴�� ����

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
	   
	Game = GameManager::GetInstance();
	Game->initializing();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MainGameScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// ���  
	auto wlayer = LayerColor::create(Color4B(0, 0, 0, 255));

	this->scheduleOnce(schedule_selector(MainGameScene::GoScript), 0.1f);
	this->scheduleUpdate();
	this->addChild(wlayer);

	return true;
}

void MainGameScene::update(float f)
{
	std::string now = Game->GetNow();

	if (now != "MONO_" && now != "AUTO_MONO_" && now != "DIAL_")
		GoScript(0);
}

void MainGameScene::GoScript(float f)
{
	Game->ScriptParser(0);
}

bool MainGameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	/*
	if (m_IsDelayStay)
	{
		m_IsDelayStay = false;
		return true;
	}
	else
		return false;*/

	return true;
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

