#ifndef CAD_H
#define CAD_H

#define SCREEN_LENGTH 1024                    //窗口长度
#define SCREEN_HEIGHT 768                     //窗口宽度
#define BUTTON_LENGTH 100                     //按钮长度
#define BUTTON_HEIGHT 50                      //按钮高度
#define BUTTON_DISTANCE 40
#define IS_INPUT 1
#define NOT_INPUT 0
#define IS_IN 1                               //用于判断鼠标位置是否在区域内
#define IS_OUT 0
#define IS_SELECT 1                            //判断图形是否被选中
#define NOT_SELECT 0
#define LINE 1                               //模式类型
#define RECTANGLE 2
#define ELLIPSE 3
#define _TEXT 4
#define MOVE 5
#define CHANGE 6
#define CLEAR 7
#define NOT_IN_BUTTON 0
#define CLICK 1
#define NOT_CLICK 0
#define INIT_DOT -1
#define END_WITHOUT_ERROR 0               //函数成功返回
#define PALETTE_WIDTH 20
#define PALETTE_HEIGHT 20
#define TEXT_SIZE 25              //文本字体大小
#define COLOR_DEFAULT 1
#define COLOR_DECIDED 2
#define COLOR_INIT 0                     //默认颜色

#include "acllib.h"
typedef struct { //颜色类型
	int R;
	int G;
	int B;
}Color;

typedef struct Line {/*直线类型*/
	int x1, y1;/*第一个点坐标*/
	int x2, y2;/*第二个点坐标*/
	int isSelected; /*选中*/
	int R;
	int G;
	int B;
	struct Line *next;
} LineT;

typedef struct Rect {/*矩形类型*/
	int x1, y1;/*左上角坐标*/
	int x2, y2;/*右下角坐标*/
	int isSelected; /*选中*/
	int R;
	int G;
	int B;
	struct Rect *next;
} RectT;

typedef struct Ellipse {/*椭圆类型*/
	int x1, y1;/*左上角坐标*/
	int x2, y2;/*右下角坐标*/
	int isSelected; /*选中*/
	int R;
	int G;
	int B;
	struct Ellipse *next;
} EllipseT;

typedef struct _Text {//字符链表，存储每个文本结点中的字符内容
	char* value;
	struct _Text* next;
}Text;

typedef struct Text {/*文本类型*/
	POINT LT;
	POINT RB;
	INT isSelected;
	Color color;
	int cnt;
	int size;
	Text* text;
	struct Text* next;
}TextT;

typedef struct button_positon {                 //按钮坐标结构，代表左边那个点和右边那个点的坐标
	int left_x;
	int left_y;
	int right_x;
	int right_y;
}coordinate;

typedef struct location {                        //鼠标位置结构
	int mouse_x;
	int mouse_y;
}_position;

coordinate _line;                      //直线按钮的坐标结构
coordinate _rectangle;                 //矩形按钮的坐标结构
coordinate _ellipse;                   //椭圆按钮的坐标结构
coordinate _text;                      //文字按钮的坐标结构
coordinate _move;                      //移动按钮的坐标结构
coordinate _change;                     //缩放按钮的做表结构
coordinate _clearscreen;               // 清屏按钮的坐标结构
coordinate color_1;                    //调色板位置
coordinate color_2;
coordinate color_3;
coordinate color_4;
coordinate color_5;
coordinate color_6;
coordinate color_7;
coordinate color_8;
coordinate color_9;
coordinate color_10;
coordinate color_11;
coordinate color_12;
_position mouse_position;              //记录当前鼠标的坐标
int button_model;                       //记录当前的模式
int check_color;                       
int R, G, B;                            //颜色参数   
int isInput;                           
LineT *head_line, *p_line, *q_line, *curline;                       //记录各条直线的特征值
RectT *head_rectangle, *p_rectangle, *q_rectangle, *currectangle;                   //记录各个矩阵的特征值
EllipseT *head_ellipse, *p_ellipse, *q_ellipse, *curellipse;                   //记录各个椭圆的特征值
TextT *head_text, *p_text, *q_text, *curtext;                                 //记录各个文字的特征值
ACL_Image Map_1_init, Map_1_end, Map_2_init, Map_2_end, Map_3_init, Map_3_end, Map_4_init, Map_4_end, Map_5_init, Map_5_end, Map_6_init, Map_6_end, Map_7;

POINT caretPos;   //光标
POINT textEnd;
char* curText;


//函数申明

void init_static_variable(void);                  //初始化一些全局变量，这些变量以后的值不会改变
void init_static_chain(void);                 //初始化一些图形特征值
void reset_screen(void);                              //用于初始化界面 
void initInterface(void);                         //用于初始化图形按钮
void button_line_init(const coordinate *p);       //绘制直线按钮的第一种状态
void button_rectangle_init(const coordinate *p);  //绘制矩阵按钮的第一种状态
void button_ellipse_init(const coordinate *p);    //绘制椭圆按钮的第一种状态
void button_text_init(const coordinate *p);       //绘制文字按钮的第一种状态
void button_move_init(const coordinate *p);       //绘制移动按钮的第一种状态
void button_change_init(const coordinate *p);     //绘制缩放按钮的第一种状态
void button_line_end(const coordinate *p);        //绘制直线按钮的第二种状态
void button_rectangle_end(const coordinate *p);   //绘制矩阵按钮的第二种状态
void button_ellipse_end(const coordinate *p);     //绘制椭圆按钮的第二种状态
void button_text_end(const coordinate *p);         //绘制文字按钮的第二种状态
void button_move_end(const coordinate *p);         //绘制移动按钮的第二种状态
void button_change_end(const coordinate *p);       //绘制缩放按钮的第二种状态
void button_clearscreen(const coordinate *p);      //绘制重置按钮(只需一种状态即可)
void button_palette(const coordinate *p, int R, int G, int B);          //绘制调色板,接受参数为RGB以及按钮位置
int check_position(const _position *mouse_position, const coordinate *p);   //第一个参数为鼠标的当前位置，第二个参数为矩形区域，函数判断鼠标是否处于区域内部
void Paint_line(const int x, const int y, const int button, const int event);    //绘制直线模块
void Paint_rectangle(const int x, const int y, const int button, const int event);  //绘制矩形模块
void Paint_ellipse(const int x, const int y, const int button, const int event);    //绘制椭圆模块
void PrintText(Text*, int, int);                                                    //绘制文字模块
void Move(const int x, const int y, const int button, const int event);             //绘制移动模块
void Change(const int x, const int y, const int button, const int event);          //绘制缩放模块
void DrawAll(void);                              //画出已有记录的图形
void ChangeCaretPos(int, int);                 //在光标位置改变时改变记录的光标位置值
void AddChar(char*);                    //添加模块  
void DeleteChar();                     //删除字符

int distLine(int x, int y, LineT *line);            //计算图形距离
int distRect(int x, int y, RectT *Rec);
int distEllipse(int x, int y, EllipseT *ellipse);
int distText(int x, int y, TextT *text);
int PickAll(int mx, int my);              //选中最近的图形
LineT *SelectNearestL(int mx, int my);
RectT *SelectNearestR(int mx, int my);
EllipseT *SelectNearestE(int mx, int my);
TextT *SelectNearestT(int mx, int my);

#endif
