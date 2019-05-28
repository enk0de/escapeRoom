#include "GameManager.h"
#include "MonologueScene.h"
#include "DialogueScene.h"
#include "AudioEngine.h"

GameManager* GameManager::instance = nullptr;
TTFConfig mainTTF("fonts/NanumBarunGothic.ttf", 30);

void GameManager::initializing()
{
	now = "START!";
	m_IsSelection = false;
	m_Indicator = 1;
	filename = "001.txt";
	std::ifstream scr(filename);
	ReadScript(&scr);
}

void GameManager::ReadScript(std::ifstream* scr)
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

void GameManager::ScriptParser(float delta)
{
	if (m_Indicator < 200 && !m_IsSelection)
	{
		if (script[m_Indicator].find("AUTO_MONO_") == 0)
		{
			now = "AUTO_MONO_";
			script[m_Indicator].erase(0, 11);

			int ind_time, ind_str, ind_istype;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != ' '; ind_time++) {}
			CCLOG("--> %d", ind_time);
			for (ind_str = ind_time + 1; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}
			for (ind_istype = ind_str + 1; (script[m_Indicator])[ind_istype] != '$'; ind_istype++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; } // 예외 처리 - 마지막에 $가 없으면 for문 탈출하여 무한루프 막음
			}


			GameManager::GoToMonologueScene(atof(script[m_Indicator].substr(0, ind_time).c_str()), script[m_Indicator].substr(ind_time + 1, ind_str - (ind_time + 1)), true, atoi(script[m_Indicator].substr(ind_str + 1, ind_istype - (ind_str + 1)).c_str()));
		}
		else if (script[m_Indicator].find("MONO_") == 0)
		{
			now = "MONO_";
			script[m_Indicator].erase(0, 6);

			int ind_time, ind_str, ind_istype;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != ' '; ind_time++) {}

			for (ind_str = ind_time + 1; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}
			for (ind_istype = ind_str + 1; (script[m_Indicator])[ind_istype] != '$'; ind_istype++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; } // 예외 처리 - 마지막에 $가 없으면 for문 탈출하여 무한루프 막음
			}

			GameManager::GoToMonologueScene(atof(script[m_Indicator].substr(0, ind_time).c_str()), script[m_Indicator].substr(ind_time + 1, ind_str - (ind_time + 1)), false, atoi(script[m_Indicator].substr(ind_str + 1, ind_istype - (ind_str + 1)).c_str()));
		}
		else if (script[m_Indicator].find("DIAL_") == 0)
		{
			now = "DIAL_";
			script[m_Indicator].erase(0, 6);

			int ind_where, ind_name, ind_text, ind_bgurl, ind_charurl;
			for (ind_where = 0; (script[m_Indicator])[ind_where] != ' '; ind_where++) {}
			for (ind_name = ind_where + 1; (script[m_Indicator])[ind_name] != '$'; ind_name++) {}
			for (ind_text = ind_name + 1; (script[m_Indicator])[ind_text] != '$'; ind_text++) {} // 예외 처리 없음..ㅠㅠ
			for (ind_bgurl = ind_text + 1; (script[m_Indicator])[ind_bgurl] != '$'; ind_bgurl++) {}
			for (ind_charurl = ind_bgurl + 1; (script[m_Indicator])[ind_charurl] != '$'; ind_charurl++) {}

			if (script[m_Indicator + 1].find("DIAL_") == 0)
			{
				GameManager::GoToDialogueScene(script[m_Indicator].substr(0, ind_where), script[m_Indicator].substr(ind_where + 1, ind_name - (ind_where + 1)), script[m_Indicator].substr(ind_name + 2, ind_text - (ind_name + 2)), script[m_Indicator].substr(ind_text + 2, ind_bgurl - (ind_text + 2)), script[m_Indicator].substr(ind_bgurl + 2, ind_charurl - (ind_bgurl + 2)), true);
			}
			else
			{
				GameManager::GoToDialogueScene(script[m_Indicator].substr(0, ind_where), script[m_Indicator].substr(ind_where + 1, ind_name - (ind_where + 1)), script[m_Indicator].substr(ind_name + 2, ind_text - (ind_name + 2)), script[m_Indicator].substr(ind_text + 2, ind_bgurl - (ind_text + 2)), script[m_Indicator].substr(ind_bgurl + 2, ind_charurl - (ind_bgurl + 2)), false);
			}
		}
		else if (script[m_Indicator].find("SELECTION_") == 0)
		{
			now = "SELECTION_";
			script[m_Indicator].erase(0, 11);

			int ind_many, ind_text1, ind_goto1, ind_text2, ind_goto2, ind_text3 = NULL, ind_goto3 = NULL;

			for (ind_many = 0; (script[m_Indicator])[ind_many] != ' '; ind_many++) {}

			if ((script[m_Indicator])[0] == '2')
			{
				for (ind_text1 = ind_many + 1; (script[m_Indicator])[ind_text1] != '$'; ind_text1++) {}
				for (ind_goto1 = ind_text1 + 1; (script[m_Indicator])[ind_goto1] != '$'; ind_goto1++) {} // 예외 처리 없음..ㅠㅠ
				for (ind_text2 = ind_goto1 + 1; (script[m_Indicator])[ind_text2] != '$'; ind_text2++) {}
				for (ind_goto2 = ind_text2 + 1; (script[m_Indicator])[ind_goto2] != '$'; ind_goto2++) {}

				Selection(script[m_Indicator].substr(ind_many + 1, ind_text1 - (ind_many + 1)), script[m_Indicator].substr(ind_text1 + 2, ind_goto1 - (ind_text1 + 2)), script[m_Indicator].substr(ind_goto1 + 2, ind_text2 - (ind_goto1 + 2)), script[m_Indicator].substr(ind_text2 + 2, ind_goto2 - (ind_text2 + 2)));
				m_IsSelection = true;
			}
			else if ((script[m_Indicator])[0] == '3')
			{
				for (ind_text1 = ind_many + 1; (script[m_Indicator])[ind_text1] != '$'; ind_text1++) {}
				for (ind_goto1 = ind_text1 + 1; (script[m_Indicator])[ind_goto1] != '$'; ind_goto1++) {} // 예외 처리 없음..ㅠㅠ
				for (ind_text2 = ind_goto1 + 1; (script[m_Indicator])[ind_text2] != '$'; ind_text2++) {}
				for (ind_goto2 = ind_text2 + 1; (script[m_Indicator])[ind_goto2] != '$'; ind_goto2++) {}
				for (ind_text3 = ind_goto2 + 1; (script[m_Indicator])[ind_text3] != '$'; ind_text3++) {}
				for (ind_goto3 = ind_text3 + 1; (script[m_Indicator])[ind_goto3] != '$'; ind_goto3++) {}

				Selection(script[m_Indicator].substr(ind_many + 1, ind_text1 - (ind_many + 1)), script[m_Indicator].substr(ind_text1 + 2, ind_goto1 - (ind_text1 + 2)), script[m_Indicator].substr(ind_goto1 + 2, ind_text2 - (ind_goto1 + 2)), script[m_Indicator].substr(ind_text2 + 2, ind_goto2 - (ind_text2 + 2)), script[m_Indicator].substr(ind_goto2 + 2, ind_text3 - (ind_goto2 + 2)), script[m_Indicator].substr(ind_text3 + 2, ind_goto3 - (ind_text3 + 2)));
				m_IsSelection = true;
			}
			// 최대 4개 까지 출력하고 함수 오버로딩으로 처리한다.
		}
		else if (script[m_Indicator].find("EFFECTS_") == 0)
		{
			now = "EFFECTS_";
			script[m_Indicator].erase(0, 9);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			effectId = AudioEngine::play2d(script[m_Indicator].substr(0, ind_str), false, 1.0);
		}
		else if (script[m_Indicator].find("MUSIC_PLAY_") == 0)
		{
			now = "MUSIC_PLAY_";
			script[m_Indicator].erase(0, 12);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			audioId = AudioEngine::play2d(script[m_Indicator].substr(0, ind_str), true, 1.0);
		}
		else if (script[m_Indicator].find("SHOW_IMAGE_") == 0)
		{
			now = "SHOW_IMAGE_";
			script[m_Indicator].erase(0, 12);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			auto TempImage = Sprite::create(script[m_Indicator].substr(0, ind_str));
			TempImage->setPosition(Vec2(960, 540));
			TempImage->setName("TempImage");

			Director::getInstance()->getRunningScene()->addChild(TempImage);
		}
		else if (script[m_Indicator].find("HIDE_IMAGE_") == 0)
		{
			now = "HIDE_IMAGE_";
			Director::getInstance()->getRunningScene()->removeChildByName("TempImage");
		}
		else if (script[m_Indicator].find("MUSIC_STOP_") == 0)
		{
			now = "MUSIC_STOP_";
			AudioEngine::stop(audioId);
		}
		else if (script[m_Indicator].find("MUSIC_PAUSE_") == 0)
		{
			now = "MUSIC_PAUSE_";
			AudioEngine::pause(audioId);
		}
		else if (script[m_Indicator].find("MUSIC_RESUME_") == 0)
		{
			now = "MUSIC_RESUME_";
			AudioEngine::resume(audioId);
		}
		else if (script[m_Indicator].find("DELAY_") == 0)
		{
			script[m_Indicator].erase(0, 7);

			int ind_time;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != '$'; ind_time++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; }
			}

			if (script[m_Indicator].substr(0, ind_time) != "STAY")
			{
				now = "DELAY_";
				m_stayingTime = atof(script[m_Indicator].substr(0, ind_time).c_str());
			}
			else if (script[m_Indicator].substr(0, ind_time) == "STAY")
			{
				now = "DELAY_STAY_";
			}

		}
		m_Indicator++;
	}
}

float GameManager::GetStayingTime()
{
	return m_stayingTime;
}

void GameManager::Selection(std::string Text1, std::string GoTo1, std::string Text2, std::string GoTo2)
{
	auto selection1 = LayerColor::create(Color4B(255, 255, 255, 200), 1920, 120);
	selection1->setPosition(Vec2(960, 620));
	selection1->setAnchorPoint(Vec2(0.5, 0.5));
	auto selection2 = LayerColor::create(Color4B(255, 255, 255, 200), 1920, 120);
	selection2->setPosition(Vec2(960, 460));
	selection2->setAnchorPoint(Vec2(0.5, 0.5));
	auto text1 = Label::createWithTTF(mainTTF, Text1, TextHAlignment::CENTER);
	text1->setPosition(Vec2(960, 620));
	text1->setAnchorPoint(Vec2(0.5, 0.5));
	text1->setTextColor(Color4B(255, 255, 255, 255));
	auto text2 = Label::createWithTTF(mainTTF, Text2, TextHAlignment::CENTER);
	text2->setPosition(Vec2(960, 460));
	text2->setAnchorPoint(Vec2(0.5, 0.5));
	text2->setTextColor(Color4B(255, 255, 255, 255));

	Director::getInstance()->getRunningScene()->addChild(selection1);
	Director::getInstance()->getRunningScene()->addChild(selection2);
	Director::getInstance()->getRunningScene()->addChild(text1);
	Director::getInstance()->getRunningScene()->addChild(text2);
}

void GameManager::Selection(std::string Text1, std::string GoTo1, std::string Text2, std::string GoTo2, std::string Text3, std::string GoTo3)
{
	auto selection1 = LayerColor::create(Color4B(0, 0, 0, 200), 1920, 120);
	selection1->setPosition(Vec2(960, 700));
	selection1->setAnchorPoint(Vec2(0.5, 0.5));
	auto selection2 = LayerColor::create(Color4B(0, 0, 0, 200), 1920, 120);
	selection2->setPosition(Vec2(960, 540));
	selection2->setAnchorPoint(Vec2(0.5, 0.5));
	auto selection3 = LayerColor::create(Color4B(0, 0, 0, 200), 1920, 120);
	selection3->setPosition(Vec2(960, 380));
	selection3->setAnchorPoint(Vec2(0.5, 0.5));
	auto text1 = Label::createWithTTF(mainTTF, Text1, TextHAlignment::CENTER);
	text1->setPosition(Vec2(960, 700));
	text1->setAnchorPoint(Vec2(0.5, 0.5));
	text1->setTextColor(Color4B(255, 255, 255, 255));
	auto text2 = Label::createWithTTF(mainTTF, Text2, TextHAlignment::CENTER);
	text2->setPosition(Vec2(960, 540));
	text2->setAnchorPoint(Vec2(0.5, 0.5));
	text2->setTextColor(Color4B(255, 255, 255, 255));
	auto text3 = Label::createWithTTF(mainTTF, Text3, TextHAlignment::CENTER);
	text3->setPosition(Vec2(960, 380));
	text3->setAnchorPoint(Vec2(0.5, 0.5));
	text3->setTextColor(Color4B(255, 255, 255, 255));

	Director::getInstance()->getRunningScene()->addChild(selection1);
	Director::getInstance()->getRunningScene()->addChild(selection2);
	Director::getInstance()->getRunningScene()->addChild(selection3);
	Director::getInstance()->getRunningScene()->addChild(text1);
	Director::getInstance()->getRunningScene()->addChild(text2);
	Director::getInstance()->getRunningScene()->addChild(text3);

}
void GameManager::GoToMonologueScene(float FadingTime, std::string String, bool IsAuto, bool IsType)
{
	auto MonologueScene = MonologueScene::createScene(FadingTime, String, IsAuto, IsType);
	Director::getInstance()->pushScene(MonologueScene);
}

void GameManager::GoToDialogueScene(std::string Where, std::string Name, std::string Text, std::string BgURL, std::string CharURL, bool IsAnimation)
{
	auto DialogueScene = DialogueScene::createScene(Where, Name, Text, BgURL, CharURL, IsAnimation);
	Director::getInstance()->pushScene(DialogueScene);

	auto a = Director::getInstance();
	auto b = Director::getInstance()->getRunningScene()->getName();
}

std::string GameManager::GetNextScript()
{
	return script[m_Indicator];
}

std::string GameManager::GetNow()
{
	return now;
}