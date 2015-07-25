#ifndef EditScene_H
#define EditScene_H
#include "cocos2d.h"
#include "GameDefine.h"
#include "SpriteShape.h"
//#include "cocos-ext.h"//引入cocos扩展库，使用cocostudio部分必须添加该引用
#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;
//USING_NS_CC_EXT;
class EditScene : public Layer
{
public:
	~EditScene();
	static Scene* scene();
	CREATE_FUNC(EditScene);
	virtual bool init();
	void LoadUI();
	void goBack(Ref* sender, TouchEventType type);
	void goDone(Ref* sender, TouchEventType type);
	// 创建砖块,index 0 为不可破坏，index 1 为可破坏,index 2为损坏状态,3为精灵
	void createBlock(int row, int col, int index);
	// 根据行列，获取坐标值  
	Point positionOfItem(int row, int col);
	void initMap();
	void chooseBlock1(cocos2d::Ref* sender, TouchEventType type);
	void chooseBlock2(cocos2d::Ref* sender, TouchEventType type);
	bool onTouchBegan(Touch *touch, Event *unused);
	// 根据触摸的点位置，返回是地图中哪个精灵
	SpriteShape *spriteOfPoint(Point *point);
	std::string its(int i);
private:
	//布局数组
	int disMap[ROWS][COLS];
	// 二维数组
	SpriteShape* map[ROWS][COLS];
	// 绘图的最下角坐标位置
	float mapLBX, mapLBY;
	//标示选中的block,1为不可摧毁，2为可摧毁
	int chosedBlock;
	//障碍按钮
	Button* block1Btn,* block2Btn;
	TextField* scoreBox, *stepBox;
};
#endif
