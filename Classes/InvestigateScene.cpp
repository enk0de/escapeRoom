#include "InvestigateScene.h"

using namespace experimental;
// INSTEAD OF CREATE_FUNC(~);
InvestigateScene* InvestigateScene::create()
{
	InvestigateScene* pRet = new(std::nothrow) InvestigateScene();
	if (pRet && pRet->init())
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

Scene* InvestigateScene::createScene()
{
	return InvestigateScene::create();
}

bool InvestigateScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	return true;
}

void InvestigateScene::EndScene(float f = 0)
{
	Director::getInstance()->popScene();
}

bool InvestigateScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	InvestigateScene::EndScene(0);
	return true;
}

void InvestigateScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void InvestigateScene::onTouchCancelled(Touch * touch, Event * unused_event)
{
}

void InvestigateScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}