#ifndef PlayScene_H
#define PlayScene_H
#include "StartScene.h"
#include "SpriteShape.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include"cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ��� 
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣 
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline���� 
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

	/***** ����Ƴ����� *****/
	// ����Ƿ��п���������  
	void checkAndRemoveSprite();
	// ����Ƿ���
	bool isSprite(int r, int c);
	// ��ǿ����Ƴ��ľ���  
	void markRemove(SpriteShape* spr);
	// �Ƴ�����  
	void removeSprite();
	// ����ı�ը�Ƴ�  
	void explodeSprite(SpriteShape* spr);
	// ש��ٻ�
	void blockCheck(int r, int c);
	// ���Ƴ��ľ�����еĲ���  
	void actionEndCallback(Node *node);
	// ������  
	void getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// ������  
	void getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// ���ȱ  
	void fillSprite();
	//�ƶ�����spr����r,c��
	void moveSpriteTo(int r1, int c1, int r2, int c2);
	//��������
	void drop(bool& isAction);
	// ���º�����ÿִ֡��
	void update(float t);
	// ���ݴ����ĵ�λ�ã������ǵ�ͼ���ĸ�����
	SpriteShape* spriteOfPoint(Point *point);
	//����text���²���
	void resetSpritesByText(std::string text);

	/***** �����¼� *****/
	bool onTouchBegan(Touch *touch, Event *unused);
	void onTouchMoved(Touch *touch, Event *unused);
	// ��������
	void swapSprite();

private:
	// ��ά����
	SpriteShape* map[ROWS][COLS];
	//����
	int disMap[ROWS][COLS];
	std::string disText;
	
	// ��ͼ�����½�����λ��
	float mapLBX, mapLBY;

	// Դ���飬Ŀ�꾫��
	SpriteShape* staSprite;
	SpriteShape* endSprite;

	/***** ��־���� ****/
	// ��־ �Ƿ���ִ�ж���
	bool isAction;
	// ��־ �Ƿ��п�ȱ��Ҫ�
	bool isFillSprite;
	// ��־ �Ƿ���Դ���
	bool isTouchEna;
	// ��־ ���������������Ƿ�Ϊ����
	bool isRow;
	//������Ϸ�Ƿ����
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