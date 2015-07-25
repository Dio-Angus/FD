#ifndef  _Inkmoo_Elimination_h_  
#define  _Inkmoo_Elimination_h_  

// 定义屏幕宽高，这与所做的图片有关  
#define GAME_SCREEN_WIDTH 480  
#define GAME_SCREEN_HEIGHT 800  

// 定义每个精灵大小与边框大小  
#define SPRITE_WIDTH 48  
#define BOADER_WIDTH 2  

//精灵最左下角位置
#define START_WIDTH 40
#define START_HIGHT 100

// 游戏精灵行数和列数  
#define ROWS 12  
#define COLS 8  

//测试布局,0为精灵，1为不可破坏，2为可破坏
//#define testText "002000010012000020100020001200002000100002001000000000000002000000000100000000000000000200000000"
static std::string str = "000000000000000000000000002222000200002000000000000000001010010101000010000000000000000000000000";

// 精灵种类总数  
#define TOTAL_SPRITE 8

// 普通的精灵  
static const char *spriteNormal[TOTAL_SPRITE] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"Block0.png",//固定砖块
	"Block1.png",//可摧毁砖块完整状态
	"Block2.png",//可摧毁砖块毁坏状态

};

/*游戏规则*/
//步数
#define GAMESTEPS 10
//目标分
#define TARGETSCORE 2000
//每个精灵消除得分
#define PERSCORE 10

#endif  