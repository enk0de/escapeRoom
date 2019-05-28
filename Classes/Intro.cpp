#include "Intro.h"
#include "HelloWorldScene.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

USING_NS_CC;
Scene* Intro::createScene()
{
	return Intro::create();
}

bool Intro::init()
{
	if (!Scene::init())
	{
		return false;
	}

	int opacity = 0;
	isSceneOn = false;

	auto Intro_1 = Sprite::create("Images/Intro_1.png");
	Intro_1->setOpacity(0);
	Intro_1->setPosition(Vec2(960, 540));
	Intro_1->setAnchorPoint(Vec2(0.5, 0.5));
	Intro_1->setName("Intro_1");
	this->addChild(Intro_1);
	this->scheduleUpdate();

	return true;
}

void Intro::update(float f)
{
	if (!isSceneOn)
	{
		if (opacity < 254)
			this->getChildByName("Intro_1")->setOpacity(opacity += 2);
		else if (opacity >= 254 && opacity < 354)
			opacity++;
		else if (opacity == 354)
		{
			isSceneOn = true;
			opacity = 254;
		}
	}
	else if (isSceneOn)
	{
		if (opacity > 0)
			this->getChildByName("Intro_1")->setOpacity(opacity-=2);
		else if (opacity == 0)
		{
			auto scene = HelloWorldScene::create();
			Director::getInstance()->replaceScene(scene);
		}
	}
}

Intro::~Intro()
{
}