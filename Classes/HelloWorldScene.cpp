#include "HelloWorldScene.h"
#include "AudioEngine.h"
#include "MainGameScene.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

USING_NS_CC;
using namespace experimental;

const std::string BGM_PATH = "Sounds/Backgrounds/Fallen Sailor.mp3";

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	HelloWorld::PlayBGM(this);

	// 배경
	auto wlayer = LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(wlayer);

	auto mainBg = Sprite::create("Images/mainBg.png");
	mainBg->setPosition(Vec2(960, 540));
	mainBg->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainBg);

	// 메인 로고의 출력
	TTFConfig mainTTF("fonts/NanumBarunGothic.ttf", 30);

	auto mainLogo = Sprite::create("Images/logo.png");
	mainLogo->setPosition(Vec2(960, 630));
	mainLogo->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainLogo);

	// 메뉴의 생성
	auto mainMenu_item1_btn = Label::createWithTTF(mainTTF, "START");
	mainMenu_item1_btn->setTextColor(Color4B(255, 255, 255, 255));
	mainMenu_item1_btn->setPosition(Vec2(960, 300));
	mainMenu_item1_btn->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainMenu_item1_btn);

	auto mainMenu_item1 = MenuItemFont::create("START", CC_CALLBACK_1(HelloWorld::DoStart, this));
	mainMenu_item1->setColor(Color3B(255, 255, 255));
	mainMenu_item1->setPosition(Vec2(960, 300));
	mainMenu_item1->setAnchorPoint(Vec2(0.5, 0.5));
	mainMenu_item1->setOpacity(0);

	auto mainMenu_item2_btn = Label::createWithTTF(mainTTF, "EXIT");
	mainMenu_item2_btn->setTextColor(Color4B(255, 255, 255, 255));
	mainMenu_item2_btn->setPosition(Vec2(960, 250));
	mainMenu_item2_btn->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainMenu_item2_btn);

	auto mainMenu_item2 = MenuItemFont::create("EXIT", CC_CALLBACK_1(HelloWorld::DoExit, this));
	mainMenu_item2->setColor(Color3B(255, 255, 255));
	mainMenu_item2->setPosition(Vec2(960, 250));
	mainMenu_item2->setAnchorPoint(Vec2(0.5, 0.5));
	mainMenu_item2->setOpacity(0);

	Menu * mainMenu = Menu::create(mainMenu_item1, mainMenu_item2, nullptr);
	mainMenu->setPosition(Vec2::ZERO);
	
	this->addChild(mainMenu);
	return true;
}

void HelloWorld::DoStart(Ref* pSender)
{
	auto MainGameScene = MainGameScene::createScene();
	AudioEngine::stop(audioId);

	Director::getInstance()->replaceScene(MainGameScene);
}

void HelloWorld::DoExit(Ref* pSender)
{
	AudioEngine::stop(audioId);
	exit(0);
}

void HelloWorld::PlayBGM(Ref* pSender)
{
	if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING)
		audioId = AudioEngine::play2d(BGM_PATH, true, 1.0);
}

HelloWorld::~HelloWorld()
{
	AudioEngine::end();
}