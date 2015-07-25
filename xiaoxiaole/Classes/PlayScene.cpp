#include "PlayScene.h"
#include "StartScene.h"
#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d::ui;
using namespace cocostudio;
PlayScene::~PlayScene()
{
}
Scene* PlayScene::scene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer, 100);
	return scene;
}
bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//初始化精灵
	mapLBX = START_WIDTH;
	mapLBY = START_HIGHT;
	// 加载plist和png
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist", "icon.png");


	//载入背景和ui
	Node *rootNode = CSLoader::createNode("MainScene.csb");//传入Studio2.x的资源路径 
	this->addChild(rootNode);//假设this是即将显示的scene 

	//获取返回按钮，添加回调
	Button* backButton = (Button*)rootNode->getChildByName("backBtn");
	backButton->addTouchEventListener(this, toucheventselector(PlayScene::backToStartScene));

	//获取与初始化 分数、步数、目标分
	scoreTxt = (Text*)rootNode->getChildByName("Score");
	stepTxt = (Text*)rootNode->getChildByName("Step");
	conTxt = (Text*)rootNode->getChildByName("Congratulations");
	failTxt = (Text*)rootNode->getChildByName("Fail");
	score = 0;
	step = GAMESTEPS;
	//显示分数
	scoreTxt->setText(its(score));
	//显示步数
	stepTxt->setText(its(step));

	isOver = false;


	// 触摸事件处理
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	initMap();
	scheduleUpdate();
	disText = str;
	//resetSpritesByText(disText);

	return true;
}

//int转string
std::string PlayScene::its(int i)
{
	std::stringstream ss;
	std::string s;
	ss << i;
	ss >> s;
	return s;
}

// 初始化地图  
void PlayScene::initMap()  {
	for (int r = 0; r < ROWS; ++r){
		for (int c = 0; c < COLS; ++c){
			if (c == 0 || c == COLS - 1 || r == 0){
				createBlock(r, c, 0);
			}
			else{
				int p = rand() % 10;
				if (p == 0){
					createBlock(r, c, 1);
				}
			else
					createSprite(r, c);
			}
		}
	}
}
// 创建砖块,index 0 为不可破坏，index 1 为可破坏,index 2为损坏状态
void PlayScene::createBlock(int row, int col, int index){

		SpriteShape* spr = SpriteShape::createBlock(row, col,index);
		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		this->addChild(spr, 10);
		// 数组相应位置，置上寿司对象  
		map[row][col] = spr;
}
//按照text重新布局
void PlayScene::resetSpritesByText(std::string text){
	//disText = text.c_str();
	for (int r = 0; r < ROWS; ++r){
		for (int c = 0; c < COLS; ++c){
			disMap[r][c] = (int)text[r*COLS + c]-48;
			map[r][c]->removeFromParent();
			map[r][c] = NULL;
		}
	}

	for (int r = 0; r < ROWS; ++r){
		for (int c = 0; c < COLS; ++c){
			switch (disMap[r][c]){
			case 0:
				createSprite(r, c);
				break;
			case 1:
				createBlock(r, c, 0);
				break;
			case 2:
				createBlock(r, c, 1);
				break;
			default:
				break;
			}
		}
	}
}
// 创建精灵  
void PlayScene::createSprite(int row, int col)   {

	if (row == ROWS - 1){
		SpriteShape* spr = SpriteShape::create(row, col);

		Point startPosition = positionOfItem(row+1, col);
		spr->setPosition(startPosition);		
		Point endPosition = positionOfItem(row, col);
		float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
		spr->stopAllActions();
		spr->runAction(CCMoveTo::create(speed, endPosition));
		this->addChild(spr, 10);
		// 数组相应位置，置上寿司对象  
		map[row][col] = spr;
	}
	else{
		// 先创建一个寿司  
		SpriteShape* spr = SpriteShape::create(row, col);

		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		this->addChild(spr, 10);
		// 数组相应位置，置上寿司对象  
		map[row][col] = spr;
	}
}

// 根据行列，获取坐标值  
Point PlayScene::positionOfItem(int row, int col)
{
	float x = mapLBX + (SPRITE_WIDTH + BOADER_WIDTH) * col + SPRITE_WIDTH / 2;
	float y = mapLBY + (SPRITE_WIDTH + BOADER_WIDTH) * row + SPRITE_WIDTH / 2;
	return Point(x, y);
}



void PlayScene::backToStartScene(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto scene = StartScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
		break;
	}
}
void PlayScene::onExit()
{
	Layer::onExit();
	_eventDispatcher->removeEventListenersForTarget(this);
}
// 更新函数，每帧都执行
void PlayScene::update(float t)
{
	//检测分数和步数
	if (step == 0)
	{
		failTxt->setVisible(true);
		isOver = true;
	}
	if (score >= targetScore)
	{
		conTxt->setVisible(true);
		failTxt->setVisible(false);
		isOver = true;
	}

	// 检测是否在执行动作
	if (isAction) {
		// 设置为false
		isAction = false;
		// 扫描一遍所有精灵，看有没有可以消除的
		for (int r = 0; r < ROWS; ++r)	{
			for (int c = 0; c < COLS; ++c)	{
				SpriteShape* spr = map[r][c];
				if (spr && spr->getNumberOfRunningActions() > 0) {
					isAction = true;
					break;
				}
			}
		}
	}

	// 如果精灵正在移动中，忽视触摸事件
	isTouchEna = !isAction;

	// 如果没有动作执行    
	if (!isAction) {
		// 是否有精灵需要填补
		if (isFillSprite) {
			//爆炸效果结束后才掉落新寿司，增强打击感
			fillSprite();
			isFillSprite = false;
		}
		else
		{
			checkAndRemoveSprite();
		}
	}
}

// 检测是否有精灵可以移除
void PlayScene::checkAndRemoveSprite()
{
	int sum;
	SpriteShape *spr;
	// 设定寿司的忽视检查，之前可能有精灵设置忽视检查，但这次检查要将之前所有的检查都不能忽视
	for (int r = 0; r < ROWS; ++r)	{
		for (int c = 0; c < COLS; ++c)	{
			spr = map[r][c];
			if (!spr||spr->getAtlasIndex()>=5)	{
				continue;
			}
			if (spr->getImgIndex()<5)
				spr->setIgnoreCheck(false);
		}
	}


	sum = 0;
	// 从头遍历，检查是否有可以消除的精灵
	for (int r = 0; r < ROWS; ++r)	{
		for (int c = 0; c < COLS; ++c)	{
			spr = map[r][c];
			if (!spr || spr->getIgnoreCheck() == true)	{
				continue;
			}
			// 如果该精灵已经被扔到 要删除的List中，则不需要再检测它
			if (spr->getIsNeedRemove())	{
				continue;
			}

			// 建立一个list 存储在本精灵周围（上下）与本精灵相同的精灵
			std::list< SpriteShape *> colChainList;
			getColChain(spr, colChainList);

			// 建立一个list 存储在本精灵周围（左右）与本精灵相同的精灵
			std::list< SpriteShape *> rowChainList;
			getRowChain(spr, rowChainList);

			// 将可消除精灵的list 赋值 给longerList
			std::list< SpriteShape *> longerList;
			SpriteShape *spr1;

			bool exist1 = false;
			bool exist2 = false;
			if (colChainList.size() >= 3)	{
				//longerList = colChainList;
				exist1 = true;
				sum += colChainList.size();

				std::list<SpriteShape *>::iterator itList;
				for (itList = colChainList.begin(); itList != colChainList.end(); ++itList) {
					spr1 = (SpriteShape *)* itList;
					if (!spr1)	{
						continue;
					}
					longerList.push_back(spr1);
					
					//检测分支
					std::list< SpriteShape *> perList;
					if (spr != spr1){
						getRowChain(spr1, perList);
						if (perList.size() >= 3){
							sum += perList.size();
							std::list<SpriteShape *>::iterator itList1;
							for (itList1 = perList.begin(); itList1 != perList.end(); ++itList1) {
								spr1 = (SpriteShape *)* itList1;
								if (!spr1)	{
									continue;
								}
								longerList.push_back(spr1);
							}
						}
					}
					// 标记要消除的精灵
					//markRemove(spr);
				}
			}
			if (rowChainList.size() >= 3){
				//longerList = rowChainList;
				exist2 = true;
				sum += rowChainList.size();


				std::list<SpriteShape *>::iterator itList;
				for (itList = rowChainList.begin(); itList != rowChainList.end(); ++itList) {
					spr1 = (SpriteShape *)* itList;
					if (!spr1)	{
						continue;
					}
					longerList.push_back(spr1);
					// 标记要消除的精灵
					//markRemove(spr);
					//检测分支
					std::list< SpriteShape *> perList;
					if (spr != spr1){
						getColChain(spr1, perList);
						if (perList.size() >= 3){
							sum += perList.size();
							std::list<SpriteShape *>::iterator itList2;
							for (itList2 = perList.begin(); itList2 != perList.end(); ++itList2) {
								spr1 = (SpriteShape *)* itList2;
								if (!spr1)	{
									continue;
								}
								longerList.push_back(spr1);
							}
						}
					}
				}
			}
			if (exist1&&exist2)
			sum --;
			if (longerList.size() >= 3){
				std::list<SpriteShape *>::iterator itList;
				for (itList = longerList.begin(); itList != longerList.end(); ++itList) {
					spr = (SpriteShape *)* itList;
					if (!spr)	{
						continue;
					}
					// 标记要消除的精灵
					markRemove(spr);
				}
			}
		}
	}

	// 消除标记了的精灵
	removeSprite();
	score += sum*PERSCORE;
	//显示分数
	scoreTxt->setText(its(score));

}


// 标记可以移除的精灵
void PlayScene::markRemove(SpriteShape* spr)
{

	// 如果已经标记了要移除，就不需要再标记
	if (spr->getIsNeedRemove()) {
		return;
	}
	// 标记该精灵可以被移除
	spr->setIsNeedRemove(true);
}

// 移除精灵
void PlayScene::removeSprite()
{
	// 做一套移除的动作
	isAction = true;

	for (int r = 0; r < ROWS; ++r)	{
		for (int c = 0; c < COLS; ++c)	{
			SpriteShape* spr = map[r][c];
			if (!spr)	{
				continue;
			}

			if (spr->getIsNeedRemove())	{
				isFillSprite = true;
				explodeSprite(spr);
				if (c == 0){
					if (r == 0){
						blockCheck(r + 1, c);
						blockCheck(r, c + 1);
					}
					else if (r == ROWS - 1){
						blockCheck(r - 1, c);
						blockCheck(r, c + 1);
					}
					else{
						blockCheck(r - 1, c);
						blockCheck(r + 1, c);
						blockCheck(r, c + 1);
					}
				}
				else if (c == COLS - 1){
					if (r == 0){
						blockCheck(r + 1, c);
						blockCheck(r, c - 1);
					}
					else if (r == ROWS - 1){
						blockCheck(r - 1, c);
						blockCheck(r, c - 1);
					}
					else{
						blockCheck(r - 1, c);
						blockCheck(r + 1, c);
						blockCheck(r, c - 1);
					}
				}
				else if (r == 0){
					blockCheck(r + 1, c);
					blockCheck(r, c - 1);
					blockCheck(r, c + 1);
				}
				else if (r == ROWS - 1){
					blockCheck(r - 1, c);
					blockCheck(r, c - 1);
					blockCheck(r, c + 1);
				}
				else{
					blockCheck(r - 1, c);
					blockCheck(r + 1, c);
					blockCheck(r, c - 1);
					blockCheck(r, c + 1);
				}
			}
		}
	}
}

// 精灵的爆炸移除
void PlayScene::explodeSprite(SpriteShape* spr)	{

	// 精灵的动作
	spr->runAction(Sequence::create(
		ScaleTo::create(0.2f, 0.0),
		CallFuncN::create(CC_CALLBACK_1(PlayScene::actionEndCallback, this)),
		NULL));
}

//爆炸毁坏砖块
void PlayScene::blockCheck(int r, int c){
	SpriteShape* spr = map[r][c];
	if (spr != NULL){
		if (spr->getImgIndex() == 6)
		{
			map[r][c] = NULL;
			spr->removeFromParent();
			createBlock(r, c, 2);
		}
		else if (spr->getImgIndex() == 7){
			map[r][c] = NULL;
			spr->removeFromParent();
		}
	}
}

// 对移除的精灵进行的操作
void PlayScene::actionEndCallback(Node *node)	{
	SpriteShape *spr = (SpriteShape *)node;
	map[spr->getRow()][spr->getCol()] = NULL;
	spr->removeFromParent();
}

// 纵向检查
void PlayScene::getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)	{
	// 添加第一个精灵（自己）
	chainList.push_back(spr);

	// 向左查找
	int neighborCol = spr->getCol() - 1;
	while (neighborCol >= 0) {
		SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			&& !neighborSprite->getIsNeedRemove()) {
			chainList.push_back(neighborSprite);
			neighborCol--;
		}
		else {
			break;
		}
	}

	// 向右查找
	neighborCol = spr->getCol() + 1;
	while (neighborCol < COLS) {
		SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			&& !neighborSprite->getIsNeedRemove()) {
			chainList.push_back(neighborSprite);
			neighborCol++;
		}
		else {
			break;
		}
	}
}

// 横向检查
void PlayScene::getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)	{
	// 先将第一个精灵加入进去
	chainList.push_back(spr);

	// 向上查找
	int neighborRow = spr->getRow() - 1;
	while (neighborRow >= 0) {
		SpriteShape *neighborSprite = map[neighborRow][spr->getCol()];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			&& !neighborSprite->getIsNeedRemove()) {
			chainList.push_back(neighborSprite);
			neighborRow--;
		}
		else {
			break;
		}
	}

	// 向下查找
	neighborRow = spr->getRow() + 1;
	while (neighborRow < ROWS) {
		SpriteShape *neighborSprite = map[neighborRow][spr->getCol()];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			&& !neighborSprite->getIsNeedRemove()) {
			chainList.push_back(neighborSprite);
			neighborRow++;
		}
		else {
			break;
		}
	}
}

// 填补空缺位置
void PlayScene::fillSprite()	{

	// 重置移动方向标志
	isAction = true;
	bool isFilling = true;

	int *colEmptyInfo = (int *)malloc(sizeof(int) * COLS);
	memset((void *)colEmptyInfo, 0, sizeof(int) * COLS);
	/*
	int nullSprite = 0;
	for (int c = 0; c < COLS; ++c) {
		for (int r =0; r < ROWS; ++r){
			if (map[r][c] == NULL)
				nullSprite++;
		}
	}
	*/
	//for (int i = 0; i < ROWS; i++)
	//	drop(isAction);
	while (isFilling){
		drop(isFilling);
	}

	/*
	// 将存在的精灵降落下来
	SpriteShape *spr = NULL;
	int removedSpriteOfCol[COLS];
	for (int i = 0; i < COLS; i++)
		removedSpriteOfCol[i] = 0;
	for (int c = 0; c < COLS; c++) {
		// 自底向上
		for (int r = 0; r < ROWS; r++) {
			spr = map[r][c];
			if (spr == NULL) {
				++removedSpriteOfCol[c];
			}
			else {
				if (removedSpriteOfCol[c] > 0) {
					if (spr->getImgIndex()<5)
					{
						int newRow = r - removedSpriteOfCol[c];
						map[newRow][c] = spr;
						map[r][c] = NULL;

						Point startPosition = spr->getPosition();
						Point endPosition = positionOfItem(newRow, c);
						float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
						spr->stopAllActions();
						spr->runAction(CCMoveTo::create(speed, endPosition));

						spr->setRow(newRow);
					}
					else
					{
						if (c == 0)
						{
							if (map[r][c + 1]->getImgIndex()<5)
							{
								spr = map[r][c + 1];
								int newRow = r - removedSpriteOfCol[c];
								int newColumn = c + 1;
								map[newRow][newColumn] = spr;
								map[r][c + 1] = NULL;

								Point startPosition = spr->getPosition();
								Point endPosition = positionOfItem(newRow, newColumn);
								float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
								spr->stopAllActions();
								spr->runAction(CCMoveTo::create(speed, endPosition));
							}
						}
						else if (c == COLS - 1)
						{
							if (map[r][c - 1]->getImgIndex()<5)
							{
								spr = map[r][c - 1];
								int newRow = r - removedSpriteOfCol[c];
								int newColumn = c - 1;
								map[newRow][newColumn] = spr;
								map[r][c - 1] = NULL;

								Point startPosition = spr->getPosition();
								Point endPosition = positionOfItem(newRow, newColumn);
								float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
								spr->stopAllActions();
								spr->runAction(CCMoveTo::create(speed, endPosition));
							}
						}
						else
						{
							if (map[r][c - 1]->getImgIndex()<5)
							{
								spr = map[r][c - 1];
								int newRow = r - removedSpriteOfCol[c];
								int newColumn = c - 1;
								map[newRow][newColumn] = spr;
								map[r][c - 1] = NULL;

								Point startPosition = spr->getPosition();
								Point endPosition = positionOfItem(newRow, newColumn);
								float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
								spr->stopAllActions();
								spr->runAction(CCMoveTo::create(speed, endPosition));
							}
							else if (map[r][c - 1]->getImgIndex()<5)
							{
								spr = map[r][c - 1];
								int newRow = r - removedSpriteOfCol[c];
								int newColumn = c - 1;
								map[newRow][newColumn] = spr;
								map[r][c - 1] = NULL;

								Point startPosition = spr->getPosition();
								Point endPosition = positionOfItem(newRow, newColumn);
								float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
								spr->stopAllActions();
								spr->runAction(CCMoveTo::create(speed, endPosition));
							}
						}
					}
					
				}
			}
		}

		// 记录相应列数移除的数量
		//colEmptyInfo[c] = removedSpriteOfCol;
	}

	// 新建新的精灵，并降落
	for (int c = 0; c < COLS; ++c) {
		for (int r = ROWS - colEmptyInfo[c]; r < ROWS; ++r) {
			createSprite(r, c);
		}
	}

	free(colEmptyInfo);
	*/
}
//精灵下落
void PlayScene::drop(bool& isFilling){
	SpriteShape *spr = NULL;
	bool isDone = true;
	isAction = true;
	for (int r = ROWS - 1; r > 0; r--){
		for (int c = 0; c < COLS; c++){
			spr = map[r][c];
			if (spr == NULL){
				if (r == ROWS - 1)
					{
						createSprite(r, c);
						isDone = false;
					}
				//为空时也要判断左右
				else if (map[r - 1][c] == NULL){
					if (c == 0){
						if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
							if (map[r][c + 1]->getImgIndex() < 5){
								moveSpriteTo(r, c + 1, r - 1, c);
								isDone = false;
							}
						}
					}
					else if (c == COLS - 1){
						if (map[r][c - 1] != NULL&&map[r - 1][c - 1] != NULL){
							if (map[r][c - 1]->getImgIndex() < 5){
								moveSpriteTo(r, c - 1, r - 1, c);
								isDone = false;
							}
						}
					}
					else{
						if (map[r][c - 1] != NULL&&map[r - 1][c - 1] != NULL){
							if (map[r][c - 1]->getImgIndex() < 5){
								moveSpriteTo(r, c - 1, r - 1, c);
								isDone = false;
							}
							else if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
								if (map[r][c + 1]->getImgIndex() < 5){
									moveSpriteTo(r, c + 1, r - 1, c);
									isDone = false;
								}
							}
						}
						else if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
							if (map[r][c + 1]->getImgIndex() < 5){
								moveSpriteTo(r, c + 1, r - 1, c);
								isDone = false;
							}
						}
					}
				}
			}
			else if (map[r - 1][c] == NULL){
				//精灵直接下落
				if (spr->getImgIndex() < 5){
					map[r - 1][c] = spr;
					map[r][c] = NULL;

					Point startPosition = spr->getPosition();
					Point endPosition = positionOfItem(r - 1, c);
					float speed = 0.2f;//(startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
					spr->stopAllActions();
					spr->runAction(CCMoveTo::create(speed, endPosition));
					spr->setRow(r - 1);
					spr->setCol(c);
					isDone = false;
				}
				//砖块则旁边的精灵下落，先左后右
				else if (spr->getImgIndex() >= 5){
					//if (c==0)
					if (c == 0){
						if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
							if (map[r][c + 1]->getImgIndex() < 5){
								moveSpriteTo(r, c + 1, r - 1, c);
								isDone = false;
							}
						}
					}
					else if (c == COLS - 1){
						if (map[r][c - 1] != NULL&&map[r - 1][c - 1] != NULL){
							if (map[r][c - 1]->getImgIndex() < 5){
								moveSpriteTo(r, c - 1, r - 1, c);
								isDone = false;
							}
						}
					}
					else{
						if (map[r][c - 1] != NULL&&map[r-1][c-1]!=NULL){
							if (map[r][c - 1]->getImgIndex() < 5){
								moveSpriteTo(r, c - 1, r - 1, c);
								isDone = false;
							}
							else if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
								if (map[r][c + 1]->getImgIndex() < 5){
									moveSpriteTo(r, c + 1, r - 1, c);
									isDone = false;
								}
							}
						}
						else if (map[r][c + 1] != NULL&&map[r - 1][c + 1] != NULL){
							if (map[r][c + 1]->getImgIndex() < 5){
								moveSpriteTo(r, c + 1, r - 1, c);
								isDone = false;
							}
						}
					}//*/
				}
			}
		}
	}
	/*
	bool isActionNow = true;
	while (!isActionNow){
	bool action = false;
	for (int r = 0; r < ROWS; r++)
	for (int c = 0; c < COLS; c++){
	if (!map[r][c]->getActionByTag(0)->isDone())
	action = true;
	}
	if (!action)
	isActionNow = false;
	}
	*/
	if (isDone)
		isFilling = false;

}

//判断是否精灵
bool PlayScene::isSprite(int r, int c){
	if (map[r][c] == NULL){
		return false;
	}
	else if (map[r][c]->getImgIndex() < 5){
		return true;
	}
	else{
		return false;
	}
}
//移动精灵
void PlayScene::moveSpriteTo(int r1,int c1, int r2, int c2){
	SpriteShape *spr0 = NULL;
	spr0 = map[r1][c1];
	map[r2][c2] = spr0;
	map[r1][c1] = NULL;
	Point startPosition = spr0->getPosition();
	Point endPosition = positionOfItem(r2, c2);
	float speed = 0.2f;//(startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 2;
	spr0->stopAllActions();
	spr0->runAction(CCMoveTo::create(speed, endPosition));
	spr0->setRow(r2);
	spr0->setCol(c2);
}
// 开始触摸
bool PlayScene::onTouchBegan(Touch *touch, Event *unused)	{

	if (isOver)
	{
		auto scene = StartScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
		return isOver;
	}

	staSprite = NULL;
	endSprite = NULL;

	if (isTouchEna) {
		auto location = touch->getLocation();
		if (location.x >= 0 && location.y >= 0)
			staSprite = spriteOfPoint(&location);
	}
	return isTouchEna;
}

// 触摸后移动的方向
void PlayScene::onTouchMoved(Touch *touch, Event *unused)	{
	// 如果没有初始精灵 或者 触摸事件不可行，直接返回
	if (!staSprite || !isTouchEna) {
		return;
	}
	int row = 0;
	int col = 0;
	try{
		// 获取 初始精灵 的行列
		row = staSprite->getRow();
		col = staSprite->getCol();
	}
	catch (std::exception& e){
		return;
	}
// 获取移动到的 点 的位置
	auto location = touch->getLocation();
	auto halfSpriteWidth = SPRITE_WIDTH / 2;
	auto halfSpriteHeight = SPRITE_WIDTH / 2;

	auto  upRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() + halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);

	// 判断是在向哪个方向移动，
	if (upRect.containsPoint(location)) {
		++row;
		if (row < ROWS) {
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

	auto  downRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() - (halfSpriteHeight * 3),
		SPRITE_WIDTH,
		SPRITE_WIDTH);

	if (downRect.containsPoint(location)) {
		--row;
		if (row >= 0) {
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

	auto  leftRect = Rect(staSprite->getPositionX() - (halfSpriteWidth * 3),
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);

	if (leftRect.containsPoint(location)) {
		--col;
		if (col >= 0) {
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

	auto  rightRect = Rect(staSprite->getPositionX() + halfSpriteWidth,
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);

	if (rightRect.containsPoint(location)) {
		++col;
		if (col < COLS) {
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

	// 否则，并非一个有效的移动
}

// 根据触摸的点位置，返回是地图中哪个精灵
SpriteShape *PlayScene::spriteOfPoint(Point *point)
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

// 交换精灵
void PlayScene::swapSprite()	{
	// 移动中，不允许再次触摸，执行动作设置为true
	isAction = true;
	isTouchEna = false;

	// 初始精灵 和 终止精灵 均不能为空
	if (!staSprite || !endSprite || staSprite->getIgnoreCheck() == true || endSprite->getIgnoreCheck() == true) {
		return;
	}

	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

	float time = 0.2;

	// 在数组中交换位置
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	int tmpRow = staSprite->getRow();
	int tmpCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tmpRow);
	endSprite->setCol(tmpCol);

	// 检查是否能消除
	std::list<SpriteShape *> colChainListOfFirst;
	getColChain(staSprite, colChainListOfFirst);

	std::list<SpriteShape *> rowChainListOfFirst;
	getRowChain(staSprite, rowChainListOfFirst);

	std::list<SpriteShape *> colChainListOfSecond;
	getColChain(endSprite, colChainListOfSecond);

	std::list<SpriteShape *> rowChainListOfSecond;
	getRowChain(endSprite, rowChainListOfSecond);

	if (colChainListOfFirst.size() >= 3
		|| rowChainListOfFirst.size() >= 3
		|| colChainListOfSecond.size() >= 3
		|| rowChainListOfSecond.size() >= 3) {
		// 如果能够消除，仅仅进行移动（不会移动回来）
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		step--;
		//显示步数
		stepTxt->setText(its(step));

		return;
	}

	// 不能消除，则移动过去还要返回
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	tmpRow = staSprite->getRow();
	tmpCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tmpRow);
	endSprite->setCol(tmpCol);

	staSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfDest),
		MoveTo::create(time, posOfSrc),
		NULL));
	endSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfSrc),
		MoveTo::create(time, posOfDest),
		NULL));
}
void PlayScene::onEnter(){
	Layer::onEnter();
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("flag", false)){
		disText = CCUserDefault::sharedUserDefault()->getStringForKey("str", "null");   //取出string
		targetScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("score", 0);
		step = CCUserDefault::sharedUserDefault()->getIntegerForKey("step", 0);
	}
	//显示步数
	stepTxt->setText(its(step));
	resetSpritesByText(disText);
}