#ifndef StartScene_H
#define StartScene_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
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