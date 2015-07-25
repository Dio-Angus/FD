#ifndef StartScene_H
#define StartScene_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include"cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ��� 
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣 
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline���� 
using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;
class StartScene : public Layer
{
public:
	~StartScene();
	static Scene* scene();
	CREATE_FUNC(StartScene);
	virtual bool init();
	void LoadUI();
	virtual void onExit() override;
	void toStart(cocos2d::Ref* sender, TouchEventType type);
	void toExit(cocos2d::Ref* sender, TouchEventType type);
	void toEdit(cocos2d::Ref* sender, TouchEventType type);
};
#endif