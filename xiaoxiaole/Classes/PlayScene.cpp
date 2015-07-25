#include "PlayScene.h"
#include "StartScene.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include"cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ��� 
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣 
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline���� 
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

	//��ʼ������
	mapLBX = START_WIDTH;
	mapLBY = START_HIGHT;
	// ����plist��png
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist", "icon.png");


	//���뱳����ui
	Node *rootNode = CSLoader::createNode("MainScene.csb");//����Studio2.x����Դ·�� 
	this->addChild(rootNode);//����this�Ǽ�����ʾ��scene 

	//��ȡ���ذ�ť����ӻص�
	Button* backButton = (Button*)rootNode->getChildByName("backBtn");
	backButton->addTouchEventListener(this, toucheventselector(PlayScene::backToStartScene));

	//��ȡ���ʼ�� ������������Ŀ���
	scoreTxt = (Text*)rootNode->getChildByName("Score");
	stepTxt = (Text*)rootNode->getChildByName("Step");
	conTxt = (Text*)rootNode->getChildByName("Congratulations");
	failTxt = (Text*)rootNode->getChildByName("Fail");
	score = 0;
	step = GAMESTEPS;
	//��ʾ����
	scoreTxt->setText(its(score));
	//��ʾ����
	stepTxt->setText(its(step));

	isOver = false;


	// �����¼�����
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

//intתstring
std::string PlayScene::its(int i)
{
	std::stringstream ss;
	std::string s;
	ss << i;
	ss >> s;
	return s;
}

// ��ʼ����ͼ  
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
// ����ש��,index 0 Ϊ�����ƻ���index 1 Ϊ���ƻ�,index 2Ϊ��״̬
void PlayScene::createBlock(int row, int col, int index){

		SpriteShape* spr = SpriteShape::createBlock(row, col,index);
		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		this->addChild(spr, 10);
		// ������Ӧλ�ã�������˾����  
		map[row][col] = spr;
}
//����text���²���
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
// ��������  
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
		// ������Ӧλ�ã�������˾����  
		map[row][col] = spr;
	}
	else{
		// �ȴ���һ����˾  
		SpriteShape* spr = SpriteShape::create(row, col);

		Point endPosition = positionOfItem(row, col);
		spr->setPosition(endPosition);
		this->addChild(spr, 10);
		// ������Ӧλ�ã�������˾����  
		map[row][col] = spr;
	}
}

// �������У���ȡ����ֵ  
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
// ���º�����ÿ֡��ִ��
void PlayScene::update(float t)
{
	//�������Ͳ���
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

	// ����Ƿ���ִ�ж���
	if (isAction) {
		// ����Ϊfalse
		isAction = false;
		// ɨ��һ�����о��飬����û�п���������
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

	// ������������ƶ��У����Ӵ����¼�
	isTouchEna = !isAction;

	// ���û�ж���ִ��    
	if (!isAction) {
		// �Ƿ��о�����Ҫ�
		if (isFillSprite) {
			//��ըЧ��������ŵ�������˾����ǿ�����
			fillSprite();
			isFillSprite = false;
		}
		else
		{
			checkAndRemoveSprite();
		}
	}
}

// ����Ƿ��о�������Ƴ�
void PlayScene::checkAndRemoveSprite()
{
	int sum;
	SpriteShape *spr;
	// �趨��˾�ĺ��Ӽ�飬֮ǰ�����о������ú��Ӽ�飬����μ��Ҫ��֮ǰ���еļ�鶼���ܺ���
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
	// ��ͷ����������Ƿ��п��������ľ���
	for (int r = 0; r < ROWS; ++r)	{
		for (int c = 0; c < COLS; ++c)	{
			spr = map[r][c];
			if (!spr || spr->getIgnoreCheck() == true)	{
				continue;
			}
			// ����þ����Ѿ����ӵ� Ҫɾ����List�У�����Ҫ�ټ����
			if (spr->getIsNeedRemove())	{
				continue;
			}

			// ����һ��list �洢�ڱ�������Χ�����£��뱾������ͬ�ľ���
			std::list< SpriteShape *> colChainList;
			getColChain(spr, colChainList);

			// ����һ��list �洢�ڱ�������Χ�����ң��뱾������ͬ�ľ���
			std::list< SpriteShape *> rowChainList;
			getRowChain(spr, rowChainList);

			// �������������list ��ֵ ��longerList
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
					
					//����֧
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
					// ���Ҫ�����ľ���
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
					// ���Ҫ�����ľ���
					//markRemove(spr);
					//����֧
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
					// ���Ҫ�����ľ���
					markRemove(spr);
				}
			}
		}
	}

	// ��������˵ľ���
	removeSprite();
	score += sum*PERSCORE;
	//��ʾ����
	scoreTxt->setText(its(score));

}


// ��ǿ����Ƴ��ľ���
void PlayScene::markRemove(SpriteShape* spr)
{

	// ����Ѿ������Ҫ�Ƴ����Ͳ���Ҫ�ٱ��
	if (spr->getIsNeedRemove()) {
		return;
	}
	// ��Ǹþ�����Ա��Ƴ�
	spr->setIsNeedRemove(true);
}

// �Ƴ�����
void PlayScene::removeSprite()
{
	// ��һ���Ƴ��Ķ���
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

// ����ı�ը�Ƴ�
void PlayScene::explodeSprite(SpriteShape* spr)	{

	// ����Ķ���
	spr->runAction(Sequence::create(
		ScaleTo::create(0.2f, 0.0),
		CallFuncN::create(CC_CALLBACK_1(PlayScene::actionEndCallback, this)),
		NULL));
}

//��ը�ٻ�ש��
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

// ���Ƴ��ľ�����еĲ���
void PlayScene::actionEndCallback(Node *node)	{
	SpriteShape *spr = (SpriteShape *)node;
	map[spr->getRow()][spr->getCol()] = NULL;
	spr->removeFromParent();
}

// ������
void PlayScene::getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)	{
	// ��ӵ�һ�����飨�Լ���
	chainList.push_back(spr);

	// �������
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

	// ���Ҳ���
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

// ������
void PlayScene::getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)	{
	// �Ƚ���һ����������ȥ
	chainList.push_back(spr);

	// ���ϲ���
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

	// ���²���
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

// ���ȱλ��
void PlayScene::fillSprite()	{

	// �����ƶ������־
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
	// �����ڵľ��齵������
	SpriteShape *spr = NULL;
	int removedSpriteOfCol[COLS];
	for (int i = 0; i < COLS; i++)
		removedSpriteOfCol[i] = 0;
	for (int c = 0; c < COLS; c++) {
		// �Ե�����
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

		// ��¼��Ӧ�����Ƴ�������
		//colEmptyInfo[c] = removedSpriteOfCol;
	}

	// �½��µľ��飬������
	for (int c = 0; c < COLS; ++c) {
		for (int r = ROWS - colEmptyInfo[c]; r < ROWS; ++r) {
			createSprite(r, c);
		}
	}

	free(colEmptyInfo);
	*/
}
//��������
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
				//Ϊ��ʱҲҪ�ж�����
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
				//����ֱ������
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
				//ש�����Աߵľ������䣬�������
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

//�ж��Ƿ���
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
//�ƶ�����
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
// ��ʼ����
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

// �������ƶ��ķ���
void PlayScene::onTouchMoved(Touch *touch, Event *unused)	{
	// ���û�г�ʼ���� ���� �����¼������У�ֱ�ӷ���
	if (!staSprite || !isTouchEna) {
		return;
	}
	int row = 0;
	int col = 0;
	try{
		// ��ȡ ��ʼ���� ������
		row = staSprite->getRow();
		col = staSprite->getCol();
	}
	catch (std::exception& e){
		return;
	}
// ��ȡ�ƶ����� �� ��λ��
	auto location = touch->getLocation();
	auto halfSpriteWidth = SPRITE_WIDTH / 2;
	auto halfSpriteHeight = SPRITE_WIDTH / 2;

	auto  upRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() + halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);

	// �ж��������ĸ������ƶ���
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

	// ���򣬲���һ����Ч���ƶ�
}

// ���ݴ����ĵ�λ�ã������ǵ�ͼ���ĸ�����
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

// ��������
void PlayScene::swapSprite()	{
	// �ƶ��У��������ٴδ�����ִ�ж�������Ϊtrue
	isAction = true;
	isTouchEna = false;

	// ��ʼ���� �� ��ֹ���� ������Ϊ��
	if (!staSprite || !endSprite || staSprite->getIgnoreCheck() == true || endSprite->getIgnoreCheck() == true) {
		return;
	}

	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

	float time = 0.2;

	// �������н���λ��
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	int tmpRow = staSprite->getRow();
	int tmpCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tmpRow);
	endSprite->setCol(tmpCol);

	// ����Ƿ�������
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
		// ����ܹ����������������ƶ��������ƶ�������
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		step--;
		//��ʾ����
		stepTxt->setText(its(step));

		return;
	}

	// �������������ƶ���ȥ��Ҫ����
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
		disText = CCUserDefault::sharedUserDefault()->getStringForKey("str", "null");   //ȡ��string
		targetScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("score", 0);
		step = CCUserDefault::sharedUserDefault()->getIntegerForKey("step", 0);
	}
	//��ʾ����
	stepTxt->setText(its(step));
	resetSpritesByText(disText);
}