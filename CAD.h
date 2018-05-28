#ifndef CAD_H
#define CAD_H

#define SCREEN_LENGTH 1024                    //���ڳ���
#define SCREEN_HEIGHT 768                     //���ڿ��
#define BUTTON_LENGTH 100                     //��ť����
#define BUTTON_HEIGHT 50                      //��ť�߶�
#define BUTTON_DISTANCE 40
#define IS_INPUT 1
#define NOT_INPUT 0
#define IS_IN 1                               //�����ж����λ���Ƿ���������
#define IS_OUT 0
#define IS_SELECT 1                            //�ж�ͼ���Ƿ�ѡ��
#define NOT_SELECT 0
#define LINE 1                               //ģʽ����
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
#define END_WITHOUT_ERROR 0               //�����ɹ�����
#define PALETTE_WIDTH 20
#define PALETTE_HEIGHT 20
#define TEXT_SIZE 25              //�ı������С
#define COLOR_DEFAULT 1
#define COLOR_DECIDED 2
#define COLOR_INIT 0                     //Ĭ����ɫ

#include "acllib.h"
typedef struct { //��ɫ����
	int R;
	int G;
	int B;
}Color;

typedef struct Line {/*ֱ������*/
	int x1, y1;/*��һ��������*/
	int x2, y2;/*�ڶ���������*/
	int isSelected; /*ѡ��*/
	int R;
	int G;
	int B;
	struct Line *next;
} LineT;

typedef struct Rect {/*��������*/
	int x1, y1;/*���Ͻ�����*/
	int x2, y2;/*���½�����*/
	int isSelected; /*ѡ��*/
	int R;
	int G;
	int B;
	struct Rect *next;
} RectT;

typedef struct Ellipse {/*��Բ����*/
	int x1, y1;/*���Ͻ�����*/
	int x2, y2;/*���½�����*/
	int isSelected; /*ѡ��*/
	int R;
	int G;
	int B;
	struct Ellipse *next;
} EllipseT;

typedef struct _Text {//�ַ������洢ÿ���ı�����е��ַ�����
	char* value;
	struct _Text* next;
}Text;

typedef struct Text {/*�ı�����*/
	POINT LT;
	POINT RB;
	INT isSelected;
	Color color;
	int cnt;
	int size;
	Text* text;
	struct Text* next;
}TextT;

typedef struct button_positon {                 //��ť����ṹ����������Ǹ�����ұ��Ǹ��������
	int left_x;
	int left_y;
	int right_x;
	int right_y;
}coordinate;

typedef struct location {                        //���λ�ýṹ
	int mouse_x;
	int mouse_y;
}_position;

coordinate _line;                      //ֱ�߰�ť������ṹ
coordinate _rectangle;                 //���ΰ�ť������ṹ
coordinate _ellipse;                   //��Բ��ť������ṹ
coordinate _text;                      //���ְ�ť������ṹ
coordinate _move;                      //�ƶ���ť������ṹ
coordinate _change;                     //���Ű�ť������ṹ
coordinate _clearscreen;               // ������ť������ṹ
coordinate color_1;                    //��ɫ��λ��
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
_position mouse_position;              //��¼��ǰ��������
int button_model;                       //��¼��ǰ��ģʽ
int check_color;                       
int R, G, B;                            //��ɫ����   
int isInput;                           
LineT *head_line, *p_line, *q_line, *curline;                       //��¼����ֱ�ߵ�����ֵ
RectT *head_rectangle, *p_rectangle, *q_rectangle, *currectangle;                   //��¼�������������ֵ
EllipseT *head_ellipse, *p_ellipse, *q_ellipse, *curellipse;                   //��¼������Բ������ֵ
TextT *head_text, *p_text, *q_text, *curtext;                                 //��¼�������ֵ�����ֵ
ACL_Image Map_1_init, Map_1_end, Map_2_init, Map_2_end, Map_3_init, Map_3_end, Map_4_init, Map_4_end, Map_5_init, Map_5_end, Map_6_init, Map_6_end, Map_7;

POINT caretPos;   //���
POINT textEnd;
char* curText;


//��������

void init_static_variable(void);                  //��ʼ��һЩȫ�ֱ�������Щ�����Ժ��ֵ����ı�
void init_static_chain(void);                 //��ʼ��һЩͼ������ֵ
void reset_screen(void);                              //���ڳ�ʼ������ 
void initInterface(void);                         //���ڳ�ʼ��ͼ�ΰ�ť
void button_line_init(const coordinate *p);       //����ֱ�߰�ť�ĵ�һ��״̬
void button_rectangle_init(const coordinate *p);  //���ƾ���ť�ĵ�һ��״̬
void button_ellipse_init(const coordinate *p);    //������Բ��ť�ĵ�һ��״̬
void button_text_init(const coordinate *p);       //�������ְ�ť�ĵ�һ��״̬
void button_move_init(const coordinate *p);       //�����ƶ���ť�ĵ�һ��״̬
void button_change_init(const coordinate *p);     //�������Ű�ť�ĵ�һ��״̬
void button_line_end(const coordinate *p);        //����ֱ�߰�ť�ĵڶ���״̬
void button_rectangle_end(const coordinate *p);   //���ƾ���ť�ĵڶ���״̬
void button_ellipse_end(const coordinate *p);     //������Բ��ť�ĵڶ���״̬
void button_text_end(const coordinate *p);         //�������ְ�ť�ĵڶ���״̬
void button_move_end(const coordinate *p);         //�����ƶ���ť�ĵڶ���״̬
void button_change_end(const coordinate *p);       //�������Ű�ť�ĵڶ���״̬
void button_clearscreen(const coordinate *p);      //�������ð�ť(ֻ��һ��״̬����)
void button_palette(const coordinate *p, int R, int G, int B);          //���Ƶ�ɫ��,���ܲ���ΪRGB�Լ���ťλ��
int check_position(const _position *mouse_position, const coordinate *p);   //��һ������Ϊ���ĵ�ǰλ�ã��ڶ�������Ϊ�������򣬺����ж�����Ƿ��������ڲ�
void Paint_line(const int x, const int y, const int button, const int event);    //����ֱ��ģ��
void Paint_rectangle(const int x, const int y, const int button, const int event);  //���ƾ���ģ��
void Paint_ellipse(const int x, const int y, const int button, const int event);    //������Բģ��
void PrintText(Text*, int, int);                                                    //��������ģ��
void Move(const int x, const int y, const int button, const int event);             //�����ƶ�ģ��
void Change(const int x, const int y, const int button, const int event);          //��������ģ��
void DrawAll(void);                              //�������м�¼��ͼ��
void ChangeCaretPos(int, int);                 //�ڹ��λ�øı�ʱ�ı��¼�Ĺ��λ��ֵ
void AddChar(char*);                    //���ģ��  
void DeleteChar();                     //ɾ���ַ�

int distLine(int x, int y, LineT *line);            //����ͼ�ξ���
int distRect(int x, int y, RectT *Rec);
int distEllipse(int x, int y, EllipseT *ellipse);
int distText(int x, int y, TextT *text);
int PickAll(int mx, int my);              //ѡ�������ͼ��
LineT *SelectNearestL(int mx, int my);
RectT *SelectNearestR(int mx, int my);
EllipseT *SelectNearestE(int mx, int my);
TextT *SelectNearestT(int mx, int my);

#endif
