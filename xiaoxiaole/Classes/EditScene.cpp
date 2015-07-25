#include "EditScene.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "SpriteShape.h"
#include "math.h"
#include "ui/CocosGUI.h"//UI相关的头文件 
//#include "cocos-ext.h"//引入cocos扩展库，使用cocostudio部分必须添加该引用
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d::ui;
using namespace cocostudio;

EditScene::~EditScene()
{
}
Scene* EditScene::scene()
{
	auto scene = Scene::create();
	auto layer = EditScene::create();
	scene->addChild(layer, 10);
	return scene;
}
bool EditScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//初始化精灵
	mapLBX = START_WIDTH;
	mapLBY = START_HIGHT;
	chosedBlock = 0;
	// 加载plist和png
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist", "icon.png");
	//载入背景和ui
	Node *rootNode = CSLoader::createNode("EditScene.csb");//传入Studio2.x的资源路径 
	this->addChild(rootNode);//假设this是即将显示的scene 
	//添加输入框
	TextField* ScoreBox = (TextField*)rootNode->getChildByName("Score");
	TextField* StepBox = (TextField*)rootNode->getChildByName("Step");
	//获取按钮，添加回调
	Button* BackButton = (Button*)rootNode->getChildByName("backBtn");
	Button* DoneButton = (Button*)rootNode->getChildByName("doneBtn");
	BackButton->addTouchEventListener(this, toucheventselector(EditScene::goBack));
	DoneButton->addTouchEventListener(this, toucheventselector(EditScene::goDone));
	Button* Block1Button = (Button*)rootNode->getChildByName("block1Btn");
	Button* Block2Button = (Button*)rootNode->getChildByName("block2Btn");
	Block1Button->addTouchEventListener(this, toucheventselector(EditScene::chooseBlock1));
	Block2Button->addTouchEventListener(this, toucheventselector(EditScene::chooseBlock2));

	scoreBox = ScoreBox;
	stepBox = StepBox;
	block1Btn = Block1Button;
	block2Btn = Block2Button;

	// 触摸事件处理
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(EditScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	initMap();
	
	//初始化分数和步数
	int targetScore = 23333333;
	int stepLimit = 69;
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("flag", false)){
		targetScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("score", 0);
		stepLimit = CCUserDefault::sharedUserDefault()->getIntegerForKey("step", 0);
	}
	//显示步数
	ScoreBox->setText(its(targetScore));
	StepBox->setText(its(stepLimit));

	return true;
}
void EditScene::initMap(){
	for (int r = 0; r < ROWS; ++r){
		for (int c = 0; c < COLS; ++c){
			createBlock(r, c, 3);
		}
	}
}
//int转string
std::string EditScene::its(int i)
{
	std::stringstream ss;
	std::string s;
	ss << i;
	ss >> s;
	return s;
}
// 创建砖块,index 0 为不可破坏，index 1 为可破坏,index 2为损坏状态,index 3为普通精灵
void EditScene::createBlock(int row, int col, int index){
	if (index == 3){
		SpriteShape* spr = SpriteShape::create(row, col);
		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		map[row][col] = spr;
		this->addChild(spr, 10);
	}
	else{
		SpriteShape* spr = SpriteShape::createBlock(row, col, index);
		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		map[row][col] = spr;
		this->addChild(spr, 10);
	}	
	// 数组相应位置，置上寿司对象  
	if (index == 0){
		disMap[row][col] = 1;
	}
	else if (index == 1){
		disMap[row][col] = 2;
	}
	else if (index == 3){
		disMap[row][col] = 0;
	}
}
// 根据行列，获取坐标值  
Point EditScene::positionOfItem(int row, int col)
{
	float x = mapLBX + (SPRITE_WIDTH + BOADER_WIDTH) * col + SPRITE_WIDTH / 2;
	float y = mapLBY + (SPRITE_WIDTH + BOADER_WIDTH) * row + SPRITE_WIDTH / 2;
	return Point(x, y);
}
void EditScene::goBack(cocos2d::Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto scene = StartScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
		break;
	}
}
void EditScene::goDone(cocos2d::Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		std::string disText="";
		//std::stringstream ss;
		for (int r = 0; r < ROWS; ++r){
			for (int c = 0; c < COLS; ++c){
				char* s = new char;
				//ss << disMap[r][c];
				//itoa(disMap[r][c], s, 10);
				sprintf(s, "%d", disMap[r][c]);
				//std::string ss = s;
				disText += s;
			}
		}
		//str = disText;
		//ss >> disText;
		//String dText = disText;
		//没有数据
		std::string sScore = scoreBox->getStringValue();
		std::string sStep = stepBox->getStringValue();
		int iScore = 0;
		int iStep = 0;
		for (int i = 0; i < sScore.size();i++){
			iScore += ((int)sScore[i] - 48)*pow(10,sScore.size()-1-i);
		}
		for (int i = 0; i < sStep.size(); i++){
			iStep += ((int)sStep[i] - 48)*pow(10, sStep.size() - 1 - i);
		}
		CCUserDefault::sharedUserDefault()->setStringForKey("str", disText);   //写入字符串
		CCUserDefault::sharedUserDefault()->setIntegerForKey("score",iScore );//写入目标分数
		CCUserDefault::sharedUserDefault()->setIntegerForKey("step",iStep );//写入步数限制
		CCUserDefault::sharedUserDefault()->setBoolForKey("flag", true);        //写入bool
		CCUserDefault::sharedUserDefault()->flush();     //将数据存入xml里面, 不过现在貌似可以不加也可以
		auto scene=PlayScene::scene();
		//PlayScene* tmp=PlayScene::create();
		//tmp->disText = disText;
		//scene->addChild(tmp);
		CCDirector::sharedDirector()->replaceScene(scene);
		break;
	}
}
void EditScene::chooseBlock1(cocos2d::Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		chosedBlock = 1;
		block1Btn->loadTextures("Block0-p.png", "Block0-p.png","");
		block2Btn->loadTextures("Block1.png", "Block1.png", "");
		break;
	}
}
void EditScene::chooseBlock2(cocos2d::Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		chosedBlock = 2;
		block1Btn->loadTextures("Block0.png", "Block0.png", "");
		block2Btn->loadTextures("Block1-p.png", "Block1-p.png", "");
		break;
	}
}
bool EditScene::onTouchBegan(Touch *touch, Event *unused){
	auto location = touch->getLocation();
	SpriteShape* goalSpr = spriteOfPoint(&location);
	if (goalSpr == NULL)
		return true;
	int r = goalSpr->getRow();
	int c = goalSpr->getCol();
	if (goalSpr->getImgIndex() >= 5){
		map[r][c]->removeFromParent();
		createBlock(r, c, 3);
	}
	else{
		switch (chosedBlock){
		case 1:
			map[r][c]->removeFromParent();
			createBlock(r, c, 0);
			break;
		case 2:
			map[r][c]->removeFromParent();
			createBlock(r, c, 1);
			break;
		}
	}
	return true;
}
// 根据触摸的点位置，返回是地图中哪个精灵
SpriteShape *EditScene::spriteOfPoint(Point *point)
{
	SpriteShape *spr = NULL;
	Rect rect = Rect(0, 0, 0, 0);
	Size sz;
	sz.height = SPRITE_WIDTH;
	sz.width = SPRITE_WIDTH;

	for (int r = 0; r < ROWS; ++r)	{
		for (int c = 0; c < COLS; ++c)	{
			spr = map[r][c];
			if (spr)	{
				rect.origin.x = spr->getPositionX() - (SPRITE_WIDTH / 2);
				rect.origin.y = spr->getPositionY() - (SPRITE_WIDTH / 2);

				rect.size = sz;
				if (rect.containsPoint(*point)) {
					return spr;
				}
			}
		}
	}

	return NULL;
}
