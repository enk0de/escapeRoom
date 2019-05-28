#include "HelloWorldScene.h"
#include "AudioEngine.h"
#include "MainGameScene.h"

USING_NS_CC;
using namespace experimental;

const std::string BGM_PATH = "Sounds/Background/Castles of Ice.mp3";

Scene* HelloWorldScene::createScene()
{
	return HelloWorldScene::create();
}

bool HelloWorldScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Game = GameManager::GetInstance();
	Game->initializing();

	HelloWorldScene::PlayBGM(this);

	// 배경
	auto wlayer = LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(wlayer);

	auto mainBg = Sprite::create("Images/mainBg.png");
	mainBg->setPosition(Vec2(960, 540));
	mainBg->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainBg);


	// 메인 로고의 출력
	TTFConfig mainTTF("fonts/Jura-Regular.ttf", 30);

	auto mainLogo = Sprite::create("Images/logo.png");
	mainLogo->setPosition(Vec2(960, 630));
	mainLogo->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainLogo);

	// 메뉴의 생성
	auto mainMenu_item1_btn = Label::createWithTTF(mainTTF, "S T A R T");
	mainMenu_item1_btn->setTextColor(Color4B(255, 255, 255, 255));
	mainMenu_item1_btn->setPosition(Vec2(960, 350));
	mainMenu_item1_btn->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainMenu_item1_btn);

	auto mainMenu_item1 = MenuItemFont::create("START", CC_CALLBACK_1(HelloWorldScene::DoStart, this));
	mainMenu_item1->setColor(Color3B(255, 255, 255));
	mainMenu_item1->setPosition(Vec2(960, 350));
	mainMenu_item1->setAnchorPoint(Vec2(0.5, 0.5));
	mainMenu_item1->setOpacity(0);

	auto mainMenu_item2_btn = Label::createWithTTF(mainTTF, "L O A D");
	mainMenu_item2_btn->setTextColor(Color4B(255, 255, 255, 255));
	mainMenu_item2_btn->setPosition(Vec2(960, 300));
	mainMenu_item2_btn->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainMenu_item2_btn);

	auto mainMenu_item2 = MenuItemFont::create("LOAD", CC_CALLBACK_1(HelloWorldScene::DoStart, this));
	mainMenu_item2->setColor(Color3B(255, 255, 255));
	mainMenu_item2->setPosition(Vec2(960, 300));
	mainMenu_item2->setAnchorPoint(Vec2(0.5, 0.5));
	mainMenu_item2->setOpacity(0);

	auto mainMenu_item3_btn = Label::createWithTTF(mainTTF, "E X I T");
	mainMenu_item3_btn->setTextColor(Color4B(255, 255, 255, 255));
	mainMenu_item3_btn->setPosition(Vec2(960, 250));
	mainMenu_item3_btn->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainMenu_item3_btn);

	auto mainMenu_item3 = MenuItemFont::create("EXIT", CC_CALLBACK_1(HelloWorldScene::DoExit, this));
	mainMenu_item3->setColor(Color3B(255, 255, 255));
	mainMenu_item3->setPosition(Vec2(960, 250));
	mainMenu_item3->setAnchorPoint(Vec2(0.5, 0.5));
	mainMenu_item3->setOpacity(0);

	Menu * mainMenu = Menu::create(mainMenu_item1, mainMenu_item2, mainMenu_item3, nullptr);
	mainMenu->setPosition(Vec2::ZERO);
	
	this->addChild(mainMenu);
	return true;
}

void HelloWorldScene::DoStart(Ref* pSender)
{
	auto MainGameScene = MainGameScene::createScene();
	AudioEngine::stop(audioId);

	Director::getInstance()->replaceScene(MainGameScene);
}

void HelloWorldScene::DoExit(Ref* pSender)
{
	AudioEngine::stop(audioId);
	exit(0);
}

void HelloWorldScene::PlayBGM(Ref* pSender)
{
	if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING)
		audioId = AudioEngine::play2d(BGM_PATH, true, 1.0);
}

HelloWorldScene::~HelloWorldScene()
{
	AudioEngine::end();
}