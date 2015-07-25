#ifndef EditScene_H
#define EditScene_H
#include "cocos2d.h"
#include "GameDefine.h"
#include "SpriteShape.h"
//#include "cocos-ext.h"//����cocos��չ�⣬ʹ��cocostudio���ֱ�����Ӹ�����
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ� 
#include"cocostudio/CocoStudio.h"//��CocosStudio.h ͷ�ļ����Ѿ�������Studio����Ҫ�ĸ���ͷ�ļ�(��CocosGUI)�������ʹ��Studio����Ҫ�������Ϳ��� 
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣 
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline���� 
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
	// ����ש��,index 0 Ϊ�����ƻ���index 1 Ϊ���ƻ�,index 2Ϊ��״̬,3Ϊ����
	void createBlock(int row, int col, int index);
	// �������У���ȡ����ֵ  
	Point positionOfItem(int row, int col);
	void initMap();
	void chooseBlock1(cocos2d::Ref* sender, TouchEventType type);
	void chooseBlock2(cocos2d::Ref* sender, TouchEventType type);
	bool onTouchBegan(Touch *touch, Event *unused);
	// ���ݴ����ĵ�λ�ã������ǵ�ͼ���ĸ�����
	SpriteShape *spriteOfPoint(Point *point);
	std::string its(int i);
private:
	//��������
	int disMap[ROWS][COLS];
	// ��ά����
	SpriteShape* map[ROWS][COLS];
	// ��ͼ�����½�����λ��
	float mapLBX, mapLBY;
	//��ʾѡ�е�block,1Ϊ���ɴݻ٣�2Ϊ�ɴݻ�
	int chosedBlock;
	//�ϰ���ť
	Button* block1Btn,* block2Btn;
	TextField* scoreBox, *stepBox;
};
#endif
