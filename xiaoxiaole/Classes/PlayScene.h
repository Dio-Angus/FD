#ifndef PlayScene_H
#define PlayScene_H
#include "StartScene.h"
#include "SpriteShape.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;
class PlayScene : public Layer
{
public:
	~PlayScene();
	static Scene* scene();
	CREATE_FUNC(PlayScene);
	virtual bool init();
	virtual void onEnter();
	void LoadUI();
	std::string its(int i);
	void initMap();
	void createSprite(int row, int col);
	void createBlock(int row, int col,int index);
	Point positionOfItem(int row, int col);
	virtual void onExit() override;
	void backToStartScene(cocos2d::Ref* sender, TouchEventType type);

	/***** 检查移除填补相关 *****/
	// 检测是否有可消除精灵  
	void checkAndRemoveSprite();
	// 检测是否精灵
	bool isSprite(int r, int c);
	// 标记可以移除的精灵  
	void markRemove(SpriteShape* spr);
	// 移除精灵  
	void removeSprite();
	// 精灵的爆炸移除  
	void explodeSprite(SpriteShape* spr);
	// 砖块毁坏
	void blockCheck(int r, int c);
	// 对移除的精灵进行的操作  
	void actionEndCallback(Node *node);
	// 纵向检查  
	void getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// 横向检查  
	void getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// 填补空缺  
	void fillSprite();
	//移动精灵spr至（r,c）
	void moveSpriteTo(int r1, int c1, int r2, int c2);
	//精灵下落
	void drop(bool& isAction);
	// 更新函数，每帧执行
	void update(float t);
	// 根据触摸的点位置，返回是地图中哪个精灵
	SpriteShape* spriteOfPoint(Point *point);
	//按照text重新布局
	void resetSpritesByText(std::string text);

	/***** 触摸事件 *****/
	bool onTouchBegan(Touch *touch, Event *unused);
	void onTouchMoved(Touch *touch, Event *unused);
	// 交换精灵
	void swapSprite();

private:
	// 二维数组
	SpriteShape* map[ROWS][COLS];
	//布局
	int disMap[ROWS][COLS];
	std::string disText;
	
	// 绘图的最下角坐标位置
	float mapLBX, mapLBY;

	// 源精灵，目标精灵
	SpriteShape* staSprite;
	SpriteShape* endSprite;

	/***** 标志变量 ****/
	// 标志 是否在执行动作
	bool isAction;
	// 标志 是否有空缺需要填补
	bool isFillSprite;
	// 标志 是否可以触摸
	bool isTouchEna;
	// 标志 产生的四消精灵是否为横向
	bool isRow;
	//本局游戏是否结束
	bool isOver;

	int score;
	int step;
	int perScore;
	int targetScore;
	Text* scoreTxt;
	Text* stepTxt;
	Text* conTxt;
	Text* failTxt;
};
#endif