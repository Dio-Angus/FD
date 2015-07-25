#include "StartScene.h"
#include "PlayScene.h"
#include "EditScene.h"
#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d::ui;
using namespace cocostudio;
StartScene::~StartScene()
{
}
Scene* StartScene::scene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer, 10);
	return scene;
}
bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//载入背景和ui
	Node *rootNode = CSLoader::createNode("StartScene.csb");//传入Studio2.x的资源路径 
	this->addChild(rootNode);//假设this是即将显示的scene 

	//获取按钮，添加回调
	Button* StartButton = (Button*)rootNode->getChildByName("StartBtn");
	Button* ExitButton = (Button*)rootNode->getChildByName("ExitBtn");
	Button* EditButton = (Button*)rootNode->getChildByName("EditBtn");
	StartButton->addTouchEventListener(this, toucheventselector(StartScene::toStart));
	ExitButton->addTouchEventListener(this, toucheventselector(StartScene::toExit));
	EditButton->addTouchEventListener(this, toucheventselector(StartScene::toEdit));

	return true;
}
void StartScene::toStart(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto scene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
		break;
	}
}
void StartScene::toEdit(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto scene = EditScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
		break;
	}
}
void StartScene::toExit(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;

	}
}
void StartScene::onExit()
{
	Layer::onExit();
	_eventDispatcher->removeEventListenersForTarget(this);
}