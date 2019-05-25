#include "GameManager.h"
#include "MonologueScene.h"
#include "DialogueScene.h"
#include "AudioEngine.h"

GameManager* GameManager::instance = nullptr;
TTFConfig mainTTF("fonts/NanumBarunGothic.ttf", 30);

void GameManager::initializing()
{
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
	if (m_Indicator < 200)
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
		else if (script[m_Indicator].find("EFFECTS_") == 0)
		{
			now = "EFFECTS_";
			script[m_Indicator].erase(0, 9);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			std::string a = script[m_Indicator].substr(0, ind_str);
			effectId = AudioEngine::play2d(script[m_Indicator].substr(0, ind_str), true, 1.0);

			ScriptParser(0);
		}
		else if (script[m_Indicator].find("MUSIC_PLAY_") == 0)
		{
			now = "MUSIC_PLAY_";
			script[m_Indicator].erase(0, 12);

			int ind_str;
			for (ind_str = 0; (script[m_Indicator])[ind_str] != '$'; ind_str++) {}

			std::string a = script[m_Indicator].substr(0, ind_str);

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
			now = "DELAY_";
			script[m_Indicator].erase(0, 7);

			int ind_time;
			for (ind_time = 0; (script[m_Indicator])[ind_time] != '$'; ind_time++)
			{
				if ((script[m_Indicator])[script[m_Indicator].length() - 1] != '$') { break; }
			}

			if (script[m_Indicator].substr(0, ind_time) != "STAY")
			{
				m_IsDelayStay = true;
			//	Director::getInstance()->getRunningScene()->scheduleOnce(schedule_selector(GameManager::DisableDelay), atof(script[m_Indicator].substr(0, ind_time).c_str()));
			}
			else if (script[m_Indicator].substr(0, ind_time) == "STAY")
			{
				m_IsDelayStay = true;
			}

		}
		m_Indicator++;
	}
}

void GameManager::DisableDelay(float f)
{
	m_IsDelayStay = false;
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