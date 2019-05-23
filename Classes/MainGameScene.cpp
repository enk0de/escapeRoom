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

	// Initializing
	m_Indicator = 0;
	m_IsDelayStay = false;
	filename = "001.txt";
	TTFConfig mainTTF("fonts/NanumBarunGothic.ttf", 30);

	std::ifstream scr(filename);
	ReadScript(&scr);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MainGameScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 배경  
	auto wlayer = LayerColor::create(Color4B(0, 0, 0, 255));

	this->addChild(wlayer);
	this->schedule(schedule_selector(MainGameScene::Scripting));

	return true;
}

bool MainGameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (m_IsDelayStay)
	{
		m_IsDelayStay = false;
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

void MainGameScene::ReadScript(std::ifstream* scr)
{
	int i = 0;

	for (int i = 0; i < 200; i++)
		script[i] = "BLANK";

	while (scr->peek() != EOF)
	{
		std::getline(*scr, script[i]);
		CCLOG("%s", script[i]);
		i += 1;
	}


}

MainGameScene::~MainGameScene()
{
	AudioEngine::end();
}


void MainGameScene::Scripting(float delta)
{
	TTFConfig mainTTF("fonts/NanumBarunGothic.ttf", 30);

	CCLOG("-- %d --", m_Indicator);

	if (!m_IsDelayStay && m_Indicator < 200)
	{
		if (script[m_Indicator].find("AUTO_MONO_") == 0)
		{
			ScrInd = AUTO_MONO_;
			script[m_Indicator].erase(0, 11);

			int ind_time, ind_str, ind_istype;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != ' '; ind_time++) {}
			CCLOG("--> %d", ind_time);
			for (ind_str = ind_time + 1; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}
			for (ind_istype = ind_str + 1; (script[m_Indicator])[ind_istype] != '$'; ind_istype++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; } // 예외 처리 - 마지막에 $가 없으면 for문 탈출하여 무한루프 막음
			}

			MainGameScene::GoToMonologueScene(this, atof(script[m_Indicator].substr(0, ind_time).c_str()), script[m_Indicator].substr(ind_time + 1, ind_str - (ind_time + 1)), true, atoi(script[m_Indicator].substr(ind_str + 1, ind_istype - (ind_str + 1)).c_str()));
		}
		else if (script[m_Indicator].find("MONO_") == 0)
		{
			ScrInd = MONO_;
			script[m_Indicator].erase(0, 6);

			int ind_time, ind_str, ind_istype;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != ' '; ind_time++) {}

			for (ind_str = ind_time + 1; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}
			for (ind_istype = ind_str + 1; (script[m_Indicator])[ind_istype] != '$'; ind_istype++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; } // 예외 처리 - 마지막에 $가 없으면 for문 탈출하여 무한루프 막음
			}

			MainGameScene::GoToMonologueScene(this, atof(script[m_Indicator].substr(0, ind_time).c_str()), script[m_Indicator].substr(ind_time + 1, ind_str - (ind_time + 1)), false, atoi(script[m_Indicator].substr(ind_str + 1, ind_istype - (ind_str + 1)).c_str()));
		}
		else if (script[m_Indicator].find("DIAL_") == 0)
		{
			script[m_Indicator].erase(0, 6);

			int ind_where, ind_name, ind_text, ind_bgurl, ind_charurl;
			for (ind_where = 0; (script[m_Indicator])[ind_where] != ' '; ind_where++) {}
			for (ind_name = ind_where + 1; (script[m_Indicator])[ind_name] != '$'; ind_name++) {}
			for (ind_text = ind_name + 1; (script[m_Indicator])[ind_text] != '$'; ind_text++) {} // 예외 처리 없음..ㅠㅠ
			for (ind_bgurl = ind_text + 1; (script[m_Indicator])[ind_bgurl] != '$'; ind_bgurl++) {}
			for (ind_charurl = ind_bgurl + 1; (script[m_Indicator])[ind_charurl] != '$'; ind_charurl++) {}

			if (script[m_Indicator + 1].find("DIAL_") == 0)
			{
				MainGameScene::GoToDialogueScene(this, script[m_Indicator].substr(0, ind_where), script[m_Indicator].substr(ind_where + 1, ind_name - (ind_where + 1)), script[m_Indicator].substr(ind_name + 2, ind_text - (ind_name + 2)), script[m_Indicator].substr(ind_text + 2, ind_bgurl - (ind_text + 2)), script[m_Indicator].substr(ind_bgurl + 2, ind_charurl - (ind_bgurl + 2)), script[m_Indicator + 1], false);
			}
			else
				MainGameScene::GoToDialogueScene(this, script[m_Indicator].substr(0, ind_where), script[m_Indicator].substr(ind_where + 1, ind_name - (ind_where + 1)), script[m_Indicator].substr(ind_name + 2, ind_text - (ind_name + 2)), script[m_Indicator].substr(ind_text + 2, ind_bgurl - (ind_text + 2)), script[m_Indicator].substr(ind_bgurl + 2, ind_charurl - (ind_bgurl + 2)), "non$", true);

			ScrInd = DIAL_;
		}
		else if (script[m_Indicator].find("EFFECTS_") == 0)
		{
			script[m_Indicator].erase(0, 9);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			std::string a = script[m_Indicator].substr(0, ind_str);
			effectId = AudioEngine::play2d(script[m_Indicator].substr(0, ind_str), false, 1.0);
		}
		else if (script[m_Indicator].find("MUSIC_PLAY_") == 0)
		{
			ScrInd = MUSIC_PLAY_;
			script[m_Indicator].erase(0, 12);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			std::string a = script[m_Indicator].substr(0, ind_str);

			audioId = AudioEngine::play2d(script[m_Indicator].substr(0, ind_str), true, 1.0);
		}
		else if (script[m_Indicator].find("SHOW_IMAGE_") == 0)
		{
			ScrInd = SHOW_IMAGE_;
			script[m_Indicator].erase(0, 12);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			auto TempImage = Sprite::create(script[m_Indicator].substr(0, ind_str));
			TempImage->setPosition(Vec2(960, 540));
			TempImage->setName("TempImage");

			this->addChild(TempImage);
		}
		else if (script[m_Indicator].find("HIDE_IMAGE_") == 0)
		{
			ScrInd = HIDE_IMAGE_;
			this->removeChildByName("TempImage");
		}
		else if (script[m_Indicator].find("MUSIC_STOP_") == 0)
		{
			ScrInd = MUSIC_STOP_;
			AudioEngine::stop(audioId);
		}
		else if (script[m_Indicator].find("MUSIC_PAUSE_") == 0)
		{
			ScrInd = MUSIC_PAUSE_;
			AudioEngine::pause(audioId);
		}
		else if (script[m_Indicator].find("MUSIC_RESUME_") == 0)
		{
			ScrInd = MUSIC_RESUME_;
			AudioEngine::resume(audioId);
		}
		else if (script[m_Indicator].find("DELAY_") == 0)
		{
			ScrInd = DELAY_;
			script[m_Indicator].erase(0, 7);

			int ind_time;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != '$'; ind_time++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; }
			}

			if (script[m_Indicator].substr(0, ind_time) != "STAY")
			{
				m_IsDelayStay = true;
				this->scheduleOnce(schedule_selector(MainGameScene::DisableDelay), atof(script[m_Indicator].substr(0, ind_time).c_str()));
			}
			else if (script[m_Indicator].substr(0, ind_time) == "STAY")
			{
				m_IsDelayStay = true;
			}

		}
		m_Indicator++;
	}
}

void MainGameScene::DisableDelay(float f)
{
	m_IsDelayStay = false;
}

void MainGameScene::GoToMonologueScene(Ref * pSender, float FadingTime, std::string String, bool IsAuto, bool IsType)
{
	auto MonologueScene = MonologueScene::createScene(FadingTime, String, IsAuto, IsType);
	Director::getInstance()->pushScene(MonologueScene);
}

void MainGameScene::GoToDialogueScene(Ref * pSender, std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, std::string NextText, bool IsAnimation)
{
	auto DialogueScene = DialogueScene::createScene(Where, Name, Text, BgURL, CharURL, NextText, IsAnimation);
	Director::getInstance()->pushScene(DialogueScene);
}
