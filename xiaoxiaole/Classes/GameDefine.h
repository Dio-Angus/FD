#ifndef  _Inkmoo_Elimination_h_  
#define  _Inkmoo_Elimination_h_  

// ������Ļ��ߣ�����������ͼƬ�й�  
#define GAME_SCREEN_WIDTH 480  
#define GAME_SCREEN_HEIGHT 800  

// ����ÿ�������С��߿��С  
#define SPRITE_WIDTH 48  
#define BOADER_WIDTH 2  

//���������½�λ��
#define START_WIDTH 40
#define START_HIGHT 100

// ��Ϸ��������������  
#define ROWS 12  
#define COLS 8  

//���Բ���,0Ϊ���飬1Ϊ�����ƻ���2Ϊ���ƻ�
//#define testText "002000010012000020100020001200002000100002001000000000000002000000000100000000000000000200000000"
static std::string str = "000000000000000000000000002222000200002000000000000000001010010101000010000000000000000000000000";

// ������������  
#define TOTAL_SPRITE 8

// ��ͨ�ľ���  
static const char *spriteNormal[TOTAL_SPRITE] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"Block0.png",//�̶�ש��
	"Block1.png",//�ɴݻ�ש������״̬
	"Block2.png",//�ɴݻ�ש��ٻ�״̬

};

/*��Ϸ����*/
//����
#define GAMESTEPS 10
//Ŀ���
#define TARGETSCORE 2000
//ÿ�����������÷�
#define PERSCORE 10

#endif  