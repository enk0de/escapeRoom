//#ifndef __TEXTVIEW_H__
//#define __TEXTVIEW_H__
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#pragma execution_character_set("utf-8")
//#endif
//
//#include "cocos2d.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//
//enum CHAT_TYPE {
//	MONO = 1, CONV = 2, LEFT = 3, RIGHT = 4
//};
//
//class TextView : public cocos2d::Scene {
//public:
//	TextView() : type(CONV), text(""), name("") {};
//	virtual bool init(cocos2d::Scene * );
//	virtual void show();
//	virtual void hide();
//	virtual CHAT_TYPE changeType(CHAT_TYPE);
//	virtual std::string changeText(std::string);
//	virtual std::string changeName(std::string);
//
//	void update(float delta);
//	~TextView();
//
//private:
//	cocos2d::Label* v_Text;
//	cocos2d::Label* v_Name;
//	cocos2d::LayerColor* TextBox;
//	bool isEnable;
//	cocos2d::Scene * ptrThis;
//	CHAT_TYPE type;
//	std::string text;
//	std::string name;
//};
//
//#endif