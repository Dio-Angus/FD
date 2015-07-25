#include "StartScene.h"
#include "PlayScene.h"
#include "EditScene.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include"cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ��� 
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣 
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline���� 
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

	//���뱳����ui
	Node *rootNode = CSLoader::createNode("StartScene.csb");//����Studio2.x����Դ·�� 
	this->addChild(rootNode);//����this�Ǽ�����ʾ��scene 

	//��ȡ��ť����ӻص�
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