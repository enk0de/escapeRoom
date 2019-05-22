//#include "TextView.h"
//
//USING_NS_CC;
//
//bool TextView::init(cocos2d::Scene * gameScene)
//{
//	ptrThis = gameScene;
//
//	changeType(CONV); // Conversation is DEFAULT
//	changeName("");
//	changeText("");
//	isEnable = false;
//
//	TTFConfig textTTF("fonts/NanumBarunGothic.ttf", 50);
//	
////	TextBox = LayerColor::create(Color4B(255, 255, 255, 0));
//	v_Text = Label::createWithTTF(textTTF, text);
//	v_Text->setTextColor(Color4B(255, 255, 255, 255));
//	v_Name = Label::createWithTTF(textTTF, name);
//	v_Name->setTextColor(Color4B(255, 255, 255, 255));
//	ptrThis->addChild(TextBox);
//	ptrThis->addChild(v_Name);
//	ptrThis->addChild(v_Text);
//
//	return true;
//}
//
//std::string TextView::changeText(std::string pText)
//{
//	return text = pText;
//}
//
//std::string TextView::changeName(std::string pName)
//{
//	return name = pName;
//}
//
//CHAT_TYPE TextView::changeType(CHAT_TYPE pType)
//{
//	return type = pType;
//}
//
//void TextView::show()
//{
//	isEnable = true;
//}
//
//void TextView::hide()
//{
//	isEnable = false;
//}
//
//void TextView::update(float delta)
//{
//	if (isEnable)
//	{
//		TextBox->setOpacity(255);
//		v_Text->setOpacity(255);
//		v_Name->setOpacity(255);
//	}
//	else if (!isEnable)
//	{
//		TextBox->setOpacity(0);
//		v_Text->setOpacity(0);
//		v_Name->setOpacity(0);
//		
//	}
//}
//
//// 소멸자 없으면 오류뜨는 이유 확인핟기 REV 1
//TextView::~TextView()
//{
//
//}