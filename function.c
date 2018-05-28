#include"CAD.h"
#include"acllib.h"
#include<malloc.h>
#include<math.h>
#include<stdio.h>

int minDistance[5] = { 100000000, 100000000, 1000000000, 1000000000, 1000000000 };

int check_position(const _position *mouse_position, const coordinate *p) {    //��һ������Ϊ���ĵ�ǰλ�ã��ڶ�������Ϊ�������򣬺����ж�����Ƿ��������ڲ�
	int _flag;
	int x = mouse_position->mouse_x,
		y = mouse_position->mouse_y,
		x_1 = p->left_x,
		x_2 = p->right_x,
		y_1 = p->left_y <= p->right_y ? p->left_y : p->right_y,   //y_1Ϊ��С��y,y_2Ϊ�ϴ��y
		y_2 = p->left_y>p->right_y ? p->left_y : p->right_y;

	if (x >= x_1&&x <= x_2&&y >= y_1&&y <= y_2) _flag = IS_IN;
	else _flag = IS_OUT;

	return _flag;

}

void init_static_chain(void) {  //��ʼ����ͼ��Ԫ�صĽṹ����
	head_line = (LineT*)malloc(sizeof(LineT));          //����ֱ��ͷ���
	p_line = (LineT*)malloc(sizeof(LineT));
	head_line->next = p_line;
	p_line->x1 = INIT_DOT;
	p_line->x2 = INIT_DOT;
	p_line->y1 = INIT_DOT;
	p_line->y2 = INIT_DOT;
	p_line->R = COLOR_INIT;
	p_line->G = COLOR_INIT;
	p_line->B = COLOR_INIT;
	p_line->isSelected = NOT_SELECT;
	p_line->next = NULL;

	head_rectangle = (RectT*)malloc(sizeof(RectT));        //��������ͷ���	
	p_rectangle = (RectT*)malloc(sizeof(RectT));
	head_rectangle->next = p_rectangle;
	p_rectangle->x1 = INIT_DOT;
	p_rectangle->x2 = INIT_DOT;
	p_rectangle->y1 = INIT_DOT;
	p_rectangle->y2 = INIT_DOT;
	p_rectangle->R = COLOR_INIT;
	p_rectangle->G = COLOR_INIT;
	p_rectangle->B = COLOR_INIT;
	p_rectangle->isSelected = NOT_SELECT;
	p_rectangle->next = NULL;

	head_ellipse = (EllipseT*)malloc(sizeof(EllipseT));    //������Բͷ���	
	p_ellipse = (EllipseT*)malloc(sizeof(EllipseT));
	head_ellipse->next = p_ellipse;
	p_ellipse->x1 = INIT_DOT;
	p_ellipse->x2 = INIT_DOT;
	p_ellipse->y1 = INIT_DOT;
	p_ellipse->y2 = INIT_DOT;
	p_ellipse->R = COLOR_INIT;
	p_ellipse->G = COLOR_INIT;
	p_ellipse->B = COLOR_INIT;
	p_ellipse->isSelected = NOT_SELECT;
	p_ellipse->next = NULL;

	head_text = (TextT*)malloc(sizeof(TextT));     //��������ͷ���
	p_text = (TextT*)malloc(sizeof(TextT));
	head_text->next = p_text;
	p_text->LT.x = INIT_DOT;
	p_text->LT.y = INIT_DOT;
	p_text->RB.x = INIT_DOT;
	p_text->RB.y = INIT_DOT;
	p_text->color.R = COLOR_INIT;
	p_text->color.G = COLOR_INIT;
	p_text->color.B = COLOR_INIT;
	p_text->isSelected = NOT_SELECT;
	p_text->size = TEXT_SIZE;
	p_text->text = NULL;
	p_text->cnt = 0;
	p_text->next = NULL;

	button_model = NOT_IN_BUTTON;
	isInput = NOT_INPUT;
}

void init_static_variable(void) {  //��ʼ����ť������
	_line.left_x = 50;       //��ʼ��ֱ�߰�ť������ṹ
	_line.left_y = 50;
	_line.right_x = 50 + BUTTON_LENGTH;
	_line.right_y = 50 + BUTTON_HEIGHT;

	_rectangle.left_x = 50;  //��ʼ�����ε�����ṹ
	_rectangle.left_y = 50 + BUTTON_HEIGHT + BUTTON_DISTANCE;
	_rectangle.right_x = 50 + BUTTON_LENGTH;
	_rectangle.right_y = 50 + 2 * BUTTON_HEIGHT + BUTTON_DISTANCE;

	_ellipse.left_x = 50;  //��ʼ����Բ��ť������ṹ
	_ellipse.left_y = 50 + 2 * BUTTON_HEIGHT + 2 * BUTTON_DISTANCE;
	_ellipse.right_x = 50 + BUTTON_LENGTH;
	_ellipse.right_y = 50 + 3 * BUTTON_HEIGHT + 2 * BUTTON_DISTANCE;

	_text.left_x = 50;  //��ʼ�����ְ�ť������ṹ
	_text.left_y = 50 + 3 * BUTTON_HEIGHT + 3 * BUTTON_DISTANCE;
	_text.right_x = 50 + BUTTON_LENGTH;
	_text.right_y = 50 + 4 * BUTTON_HEIGHT + 3 * BUTTON_DISTANCE;

	_move.left_x = 50;   //��ʼ��ѡ��ť������ṹ
	_move.left_y = 50 + 4 * BUTTON_HEIGHT + 4 * BUTTON_DISTANCE;
	_move.right_x = 50 + BUTTON_LENGTH;
	_move.right_y = 50 + 5 * BUTTON_HEIGHT + 4 * BUTTON_DISTANCE;

	_change.left_x = 50;  //��ʼ�����Ű�ť������ṹ
	_change.left_y = 50 + 5 * BUTTON_HEIGHT + 5 * BUTTON_DISTANCE;
	_change.right_x = 50 + BUTTON_LENGTH;
	_change.right_y = 50 + 6 * BUTTON_HEIGHT + 5 * BUTTON_DISTANCE;

	_clearscreen.left_x = 50;    //��ʼ�����ð�ť������ṹ
	_clearscreen.left_y = 50 + 6 * BUTTON_HEIGHT + 6 * BUTTON_DISTANCE;
	_clearscreen.right_x = 50 + BUTTON_LENGTH;
	_clearscreen.right_y = 50 + 7 * BUTTON_HEIGHT + 6 * BUTTON_DISTANCE;

	loadImage("button/line_1.gif", &Map_1_init);
	Map_1_init.width = BUTTON_LENGTH;
	Map_1_init.height = BUTTON_HEIGHT;
	loadImage("button/line_2.gif", &Map_1_end);
	Map_1_end.width = BUTTON_LENGTH;
	Map_1_end.height = BUTTON_HEIGHT;

	loadImage("button/rectangle_1.gif", &Map_2_init);
	Map_2_init.width = BUTTON_LENGTH;
	Map_2_init.height = BUTTON_HEIGHT;
	loadImage("button/rectangle_2.gif", &Map_2_end);
	Map_2_end.width = BUTTON_LENGTH;
	Map_2_end.height = BUTTON_HEIGHT;

	loadImage("button/ellipse_1.gif", &Map_3_init);
	Map_3_init.width = BUTTON_LENGTH;
	Map_3_init.height = BUTTON_HEIGHT;
	loadImage("button/ellipse_2.gif", &Map_3_end);
	Map_3_end.width = BUTTON_LENGTH;
	Map_3_end.height = BUTTON_HEIGHT;

	loadImage("button/text_1.gif", &Map_4_init);
	Map_4_init.width = BUTTON_LENGTH;
	Map_4_init.height = BUTTON_HEIGHT;
	loadImage("button/text_2.gif", &Map_4_end);
	Map_4_end.width = BUTTON_LENGTH;
	Map_4_end.height = BUTTON_HEIGHT;

	loadImage("button/move_1.gif", &Map_5_init);
	Map_5_init.width = BUTTON_LENGTH;
	Map_5_init.height = BUTTON_HEIGHT;
	loadImage("button/move_2.gif", &Map_5_end);
	Map_5_end.width = BUTTON_LENGTH;
	Map_5_end.height = BUTTON_HEIGHT;

	loadImage("button/zoom_1.gif", &Map_6_init);
	Map_6_init.width = BUTTON_LENGTH;
	Map_6_init.height = BUTTON_HEIGHT;
	loadImage("button/zoom_2.gif", &Map_6_end);
	Map_6_end.width = BUTTON_LENGTH;
	Map_6_end.height = BUTTON_HEIGHT;

	loadImage("button/reset.gif", &Map_7);
	Map_7.width = BUTTON_LENGTH;
	Map_7.height = BUTTON_HEIGHT;

	check_color = COLOR_DEFAULT;                  //��ʼʱΪĬ����ɫ(��ɫ)
	R = COLOR_INIT;
	G = COLOR_INIT;
	B = COLOR_INIT;

	color_1.left_x = 800;
	color_1.left_y = 50;
	color_1.right_x = 800 + PALETTE_WIDTH;
	color_1.right_y = 50 + PALETTE_HEIGHT;

	color_2.left_x = 800 + PALETTE_WIDTH;
	color_2.left_y = 50;
	color_2.right_x = 800 + PALETTE_WIDTH * 2;
	color_2.right_y = 50 + PALETTE_HEIGHT;

	color_3.left_x = 800 + PALETTE_WIDTH * 2;
	color_3.left_y = 50;
	color_3.right_x = 800 + PALETTE_WIDTH * 3;
	color_3.right_y = 50 + PALETTE_HEIGHT;

	color_4.left_x = 800 + PALETTE_WIDTH * 3;
	color_4.left_y = 50;
	color_4.right_x = 800 + PALETTE_WIDTH * 4;
	color_4.right_y = 50 + PALETTE_HEIGHT;

	color_5.left_x = 800;
	color_5.left_y = 50 + PALETTE_HEIGHT;
	color_5.right_x = 800 + PALETTE_WIDTH;
	color_5.right_y = 50 + PALETTE_HEIGHT * 2;

	color_6.left_x = 800 + PALETTE_WIDTH;
	color_6.left_y = 50 + PALETTE_HEIGHT;
	color_6.right_x = 800 + PALETTE_WIDTH * 2;
	color_6.right_y = 50 + PALETTE_HEIGHT * 2;

	color_7.left_x = 800 + PALETTE_WIDTH * 2;
	color_7.left_y = 50 + PALETTE_HEIGHT;
	color_7.right_x = 800 + PALETTE_WIDTH * 3;
	color_7.right_y = 50 + PALETTE_HEIGHT * 2;

	color_8.left_x = 800 + PALETTE_WIDTH * 3;
	color_8.left_y = 50 + PALETTE_HEIGHT;
	color_8.right_x = 800 + PALETTE_WIDTH * 4;
	color_8.right_y = 50 + PALETTE_HEIGHT * 2;

	color_9.left_x = 800;
	color_9.left_y = 50 + PALETTE_HEIGHT * 2;
	color_9.right_x = 800 + PALETTE_WIDTH;
	color_9.right_y = 50 + PALETTE_HEIGHT * 3;

	color_10.left_x = 800 + PALETTE_WIDTH;
	color_10.left_y = 50 + PALETTE_HEIGHT * 2;
	color_10.right_x = 800 + PALETTE_WIDTH * 2;
	color_10.right_y = 50 + PALETTE_HEIGHT * 3;

	color_11.left_x = 800 + PALETTE_WIDTH * 2;
	color_11.left_y = 50 + PALETTE_HEIGHT * 2;
	color_11.right_x = 800 + PALETTE_WIDTH * 3;
	color_11.right_y = 50 + PALETTE_HEIGHT * 3;

	color_12.left_x = 800 + PALETTE_WIDTH * 3;
	color_12.left_y = 50 + PALETTE_HEIGHT * 2;
	color_12.right_x = 800 + PALETTE_WIDTH * 4;
	color_12.right_y = 50 + PALETTE_HEIGHT * 3;
}

void initInterface(void) {                  //��ʼ����ťͼ��

	button_line_init(&_line);
	button_rectangle_init(&_rectangle);
	button_ellipse_init(&_ellipse);
	button_text_init(&_text);
	button_move_init(&_move);
	button_change_init(&_change);
	button_clearscreen(&_clearscreen);

	button_palette(&color_1, 255, 128, 128);
	button_palette(&color_2, 255, 0, 0);
	button_palette(&color_3, 255, 255, 0);
	button_palette(&color_4, 0, 0, 0);
	button_palette(&color_5, 128, 255, 0);
	button_palette(&color_6, 0, 0, 255);
	button_palette(&color_7, 128, 0, 255);
	button_palette(&color_8, 255, 128, 255);
	button_palette(&color_9, 192, 192, 192);
	button_palette(&color_10, 0, 64, 128);
	button_palette(&color_11, 207, 16, 248);
	button_palette(&color_12, 11, 249, 242);
}

void button_line_init(const coordinate *p) {  //ֱ�߰�ť��һ��״̬
	beginPaint();
	putImage(&Map_1_init, p->left_x, p->left_y);
	endPaint();
}

void button_rectangle_init(const coordinate *p) {
	beginPaint();
	putImage(&Map_2_init, p->left_x, p->left_y);
	endPaint();
}

void button_ellipse_init(const coordinate *p) {
	beginPaint();
	putImage(&Map_3_init, p->left_x, p->left_y);
	endPaint();
}

void button_text_init(const coordinate *p) {
	beginPaint();
	putImage(&Map_4_init, p->left_x, p->left_y);
	endPaint();
}

void button_move_init(const coordinate *p) {
	beginPaint();
	putImage(&Map_5_init, p->left_x, p->left_y);
	endPaint();
}

void button_change_init(const coordinate *p) {
	beginPaint();
	putImage(&Map_6_init, p->left_x, p->left_y);
	endPaint();
}

void button_line_end(const coordinate *p) {   //ֱ�߰�ť�ڶ���״̬
	beginPaint();
	putImage(&Map_1_end, p->left_x, p->left_y);
	endPaint();
}

void button_rectangle_end(const coordinate *p) {
	beginPaint();
	putImage(&Map_2_end, p->left_x, p->left_y);
	endPaint();
}

void button_ellipse_end(const coordinate *p) {
	beginPaint();
	putImage(&Map_3_end, p->left_x, p->left_y);
	endPaint();
}

void button_text_end(const coordinate *p) {
	beginPaint();
	putImage(&Map_4_end, p->left_x, p->left_y);
	endPaint();
}

void button_move_end(const coordinate *p) {
	beginPaint();
	putImage(&Map_5_end, p->left_x, p->left_y);
	endPaint();
}

void button_change_end(const coordinate *p) {
	beginPaint();
	putImage(&Map_6_end, p->left_x, p->left_y);
	endPaint();
}

void button_clearscreen(const coordinate *p) {
	beginPaint();
	putImage(&Map_7, p->left_x, p->left_y);
	endPaint();
}

void button_palette(const coordinate *p, int R, int G, int B) {  //��ɫ�尴ť
	beginPaint();
	setBrushColor(RGB(R, G, B));
	setPenColor(EMPTY);
	rectangle(p->left_x, p->left_y, p->left_x + PALETTE_WIDTH, p->left_y + PALETTE_HEIGHT);
	endPaint();
}

void reset_screen(void) {  //���ý���
	beginPaint();
	clearDevice();
	endPaint();
	init_static_variable();
	init_static_chain();
	initInterface();
}

void Paint_line(const int x, const int y, const int button, const int event) {
	beginPaint();
	setPenWidth(1);
	endPaint();
	if (p_line->x1 != INIT_DOT && p_line->y1 != INIT_DOT && p_line->x2 != INIT_DOT && p_line->y2 != INIT_DOT) {
		q_line = (LineT*)malloc(sizeof(LineT));
		q_line->x1 = INIT_DOT;
		q_line->x2 = INIT_DOT;
		q_line->y1 = INIT_DOT;
		q_line->y2 = INIT_DOT;
		q_line->R = COLOR_INIT;
		q_line->G = COLOR_INIT;
		q_line->B = COLOR_INIT;
		q_line->isSelected = NOT_SELECT;
		q_line->next = NULL;
		p_line->next = q_line;
		p_line = q_line;
	}


	if (button == LEFT_BUTTON && event == BUTTON_UP && (x >= 150 || y >= 590)) {           //�������������
		if (p_line->x1 == INIT_DOT && p_line->y1 == INIT_DOT) {            //�����һ����δ��ֵ������µ����������ѵ�һ���㸳ֵ
			p_line->x1 = x;
			p_line->y1 = y;
			if (check_color == COLOR_DECIDED) {                       //����ɫ�Ѿ�������
				p_line->R = R;
				p_line->G = G;
				p_line->B = B;
			}
			else;
		}
		else if (p_line->x2 == INIT_DOT && p_line->y2 == INIT_DOT) {    //��һ���㴦�ڸ�ֵ״̬�ҵڶ��㴦��δ��ֵ������£��ѵڶ����㸳ֵ
			p_line->x2 = x;
			p_line->y2 = y;
		}
		else;
	}

	if (p_line->x1 != INIT_DOT && p_line->y1 != INIT_DOT) {       //�����һ�����Ѿ�����ֵ�ˣ���ʼ��ͼ
		if (p_line->x2 == INIT_DOT && p_line->y2 == INIT_DOT) {   //���ڶ�����δ��ֵ������ֱ̬��
			beginPaint();
			clearDevice();
			endPaint();
			initInterface();
			button_line_end(&_line);
			DrawAll();
			beginPaint();
			setPenColor(RGB(p_line->R, p_line->G, p_line->B));
			line(p_line->x1, p_line->y1, x, y);
			endPaint();
		}
		else {                                      //����ڶ������Ѿ���ֵ������ֱ�ߣ�������˳�����״̬���Ѱ�ť��Ϊ0,��ʼ����ť��ɫ
			beginPaint();
			setPenColor(RGB(p_line->R, p_line->G, p_line->B));
			line(p_line->x1, p_line->y1, p_line->x2, p_line->y2);
			endPaint();
		}
	}
	else;
}

void Paint_rectangle(const int x, const int y, const int button, const int event) {

	if (p_rectangle->x1 != INIT_DOT && p_rectangle->y1 != INIT_DOT && p_rectangle->x2 != INIT_DOT && p_rectangle->y2 != INIT_DOT) {
		q_rectangle = (RectT*)malloc(sizeof(RectT));
		q_rectangle->x1 = INIT_DOT;
		q_rectangle->x2 = INIT_DOT;
		q_rectangle->y1 = INIT_DOT;
		q_rectangle->y2 = INIT_DOT;
		q_rectangle->R = COLOR_INIT;
		q_rectangle->G = COLOR_INIT;
		q_rectangle->B = COLOR_INIT;
		q_rectangle->isSelected = NOT_SELECT;
		q_rectangle->next = NULL;
		p_rectangle->next = q_rectangle;
		p_rectangle = q_rectangle;
	}

	if (button == LEFT_BUTTON && event == BUTTON_UP && (x >= 150 || y >= 590)) {           //�������������
		if (p_rectangle->x1 == INIT_DOT && p_rectangle->y1 == INIT_DOT) {            //�����һ����δ��ֵ������µ����������ѵ�һ������ֵ�㸳ֵ
			p_rectangle->x1 = x;
			p_rectangle->y1 = y;
			if (check_color == COLOR_DECIDED) {                       //����ɫ�Ѿ�������
				p_rectangle->R = R;
				p_rectangle->G = G;
				p_rectangle->B = B;
			}
			else;
		}
		else if (p_rectangle->x2 == INIT_DOT && p_rectangle->y2 == INIT_DOT) {    //��һ���㴦�ڸ�ֵ״̬�ҵڶ��㴦��δ��ֵ������£��ѵڶ�������ֵ�㸳ֵ
			p_rectangle->x2 = x;
			p_rectangle->y2 = y;
		}
		else;
	}

	if (p_rectangle->x1 != INIT_DOT && p_rectangle->y1 != INIT_DOT) {       //�����һ�����Ѿ�����ֵ�ˣ���ʼ��ͼ
		if (p_rectangle->x2 == INIT_DOT && p_rectangle->y2 == INIT_DOT) {   //���ڶ�����δ��ֵ������̬����
			beginPaint();
			clearDevice();
			endPaint();
			initInterface();
			button_rectangle_end(&_rectangle);

			DrawAll();
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(p_rectangle->R, p_rectangle->G, p_rectangle->B));
			rectangle(p_rectangle->x1, p_rectangle->y1, x, y);
			endPaint();
		}
		else {                                      //����ڶ������Ѿ���ֵ���������󣬻�����˳�����״̬���Ѱ�ť��Ϊ0,��ʼ����ť��ɫ
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(p_rectangle->R, p_rectangle->G, p_rectangle->B));
			rectangle(p_rectangle->x1, p_rectangle->y1, p_rectangle->x2, p_rectangle->y2);
			endPaint();
		}
	}
	else;
	return END_WITHOUT_ERROR;
}

void Paint_ellipse(const int x, const int y, const int button, const int event) {
	if (p_ellipse->x1 != INIT_DOT && p_ellipse->y1 != INIT_DOT && p_ellipse->x2 != INIT_DOT && p_ellipse->y2 != INIT_DOT) {
		q_ellipse = (EllipseT*)malloc(sizeof(EllipseT));
		q_ellipse->x1 = INIT_DOT;
		q_ellipse->x2 = INIT_DOT;
		q_ellipse->y1 = INIT_DOT;
		q_ellipse->y2 = INIT_DOT;
		q_ellipse->R = COLOR_INIT;
		q_ellipse->G = COLOR_INIT;
		q_ellipse->B = COLOR_INIT;
		q_ellipse->isSelected = NOT_SELECT;
		q_ellipse->next = NULL;
		p_ellipse->next = q_ellipse;
		p_ellipse = q_ellipse;
	}


	if (button == LEFT_BUTTON && event == BUTTON_UP && (x >= 150 || y >= 590)) {           //�������������
		if (p_ellipse->x1 == INIT_DOT && p_ellipse->y1 == INIT_DOT) {            //�����һ����δ��ֵ������µ����������ѵ�һ���㸳ֵ
			p_ellipse->x1 = x;
			p_ellipse->y1 = y;
			if (check_color == COLOR_DECIDED) {                       //����ɫ�Ѿ�������
				p_ellipse->R = R;
				p_ellipse->G = G;
				p_ellipse->B = B;
			}
			else;
		}
		else if (p_ellipse->x2 == INIT_DOT && p_ellipse->y2 == INIT_DOT) {    //��һ���㴦�ڸ�ֵ״̬�ҵڶ��㴦��δ��ֵ������£��ѵڶ����㸳ֵ
			p_ellipse->x2 = x;
			p_ellipse->y2 = y;
		}
		else;
	}

	if (p_ellipse->x1 != INIT_DOT && p_ellipse->y1 != INIT_DOT) {       //�����һ�����Ѿ�����ֵ�ˣ���ʼ��ͼ
		if (p_ellipse->x2 == INIT_DOT && p_ellipse->y2 == INIT_DOT) {   //���ڶ�����δ��ֵ������̬��Բ
			beginPaint();
			clearDevice();
			endPaint();
			initInterface();
			button_ellipse_end(&_ellipse);

			DrawAll();
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(p_ellipse->R, p_ellipse->G, p_ellipse->B));
			ellipse(p_ellipse->x1, p_ellipse->y1, x, y);
			endPaint();
		}
		else {                                      //����ڶ������Ѿ���ֵ��������Բ��������˳�����״̬���Ѱ�ť��Ϊ0,��ʼ����ť��ɫ
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(p_ellipse->R, p_ellipse->G, p_ellipse->B));
			ellipse(p_ellipse->x1, p_ellipse->y1, p_ellipse->x2, p_ellipse->y2);
			endPaint();
		}
	}
	else;
	return END_WITHOUT_ERROR;
}

void Paint_text(const int x, const int y, const int button, const int event) {  //��¼������Ԫ�صĽṹ����
	if (p_text->LT.x != INIT_DOT&&p_text->LT.y != INIT_DOT&&p_text->RB.x != INIT_DOT&&p_text->RB.y != INIT_DOT) {//���������һ����������Ѿ�������ʱ�����һ���µĽڵ㲢��p_textָ�����β���
		q_text = (TextT*)malloc(sizeof(TextT));
		q_text->LT.x = INIT_DOT;
		q_text->LT.y = INIT_DOT;
		q_text->RB.x = INIT_DOT;
		q_text->RB.y = INIT_DOT;
		q_text->color.R = COLOR_INIT;
		q_text->color.G = COLOR_INIT;
		q_text->color.B = COLOR_INIT;
		q_text->isSelected = NOT_SELECT;
		q_text->size = TEXT_SIZE;
		q_text->text = NULL;
		q_text->cnt = 0;
		q_text->next = NULL;
		p_text->next = q_text;
		p_text = q_text;
	}
	if (button == LEFT_BUTTON&&event == BUTTON_DOWN && (x >= 150 || y >= 590)) {
		if (p_text->LT.x == INIT_DOT&&p_text->LT.y == INIT_DOT) {       //����������껹δ��ֵ����ʼ�ı�����
			beginPaint();
			setCaretPos(x, y);                                          //��������õ������λ��
			setCaretSize(1, TEXT_SIZE);                                 
			showCaret();
			endPaint();
			caretPos.x = x;
			caretPos.y = y;          //���¹��λ����Ϣ
			textEnd.x = x;
			textEnd.y = y;
			p_text->LT.x = x;                        
			p_text->LT.y = y;        //�洢�ı�����������
			if (check_color == COLOR_DECIDED) {                       //����ɫ�Ѿ�������
				p_text->color.R = R;
				p_text->color.G = G;
				p_text->color.B = B;
			}
			isInput = IS_INPUT;      //����״̬��Ϊ��������
		}
		else if (p_text->RB.x == INIT_DOT&&p_text->RB.y == INIT_DOT) {//������������Ѿ���ֵ����������δ��ֵ������ı�����
			p_text->RB.x = textEnd.x;
			p_text->RB.y = textEnd.y;      //�洢�ı�����������
			beginPaint();
			hideCaret();
			endPaint();
			isInput = NOT_INPUT;     //����״̬����Ϊ����������
		}
	}

	return END_WITHOUT_ERROR;
}

void  DrawAll(void) {
	q_line = head_line;                 //��ֱ��
	if (q_line->next != NULL && q_line->next->x2 != INIT_DOT && q_line->next->y2 != INIT_DOT) {
		q_line = q_line->next;
		beginPaint();
		setPenColor(RGB(q_line->R, q_line->G, q_line->B));
		line(q_line->x1, q_line->y1, q_line->x2, q_line->y2);
		endPaint();
		while (q_line->next && q_line->next->x2 != INIT_DOT && q_line->next->y2 != INIT_DOT) {
			beginPaint();
			setPenColor(RGB(q_line->R, q_line->G, q_line->B));
			line(q_line->x1, q_line->y1, q_line->x2, q_line->y2);
			endPaint();
			q_line = q_line->next;
		}
		beginPaint();
		setPenColor(RGB(q_line->R, q_line->G, q_line->B));
		line(q_line->x1, q_line->y1, q_line->x2, q_line->y2);
		endPaint();
	}
	//������
	q_rectangle = head_rectangle;
	if (q_rectangle->next != NULL && q_rectangle->next->x2 != INIT_DOT && q_rectangle->next->y2 != INIT_DOT) {
		q_rectangle = q_rectangle->next;
		beginPaint();
		setPenColor(EMPTY);
		setBrushColor(RGB(q_rectangle->R, q_rectangle->G, q_rectangle->B));
		rectangle(q_rectangle->x1, q_rectangle->y1, q_rectangle->x2, q_rectangle->y2);
		endPaint();
		while (q_rectangle->next && q_rectangle->next->x2 != INIT_DOT && q_rectangle->next->y2 != INIT_DOT) {
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(q_rectangle->R, q_rectangle->G, q_rectangle->B));
			rectangle(q_rectangle->x1, q_rectangle->y1, q_rectangle->x2, q_rectangle->y2);
			endPaint();
			q_rectangle = q_rectangle->next;
		}
		beginPaint();
		setPenColor(EMPTY);
		setBrushColor(RGB(q_rectangle->R, q_rectangle->G, q_rectangle->B));
		rectangle(q_rectangle->x1, q_rectangle->y1, q_rectangle->x2, q_rectangle->y2);
		endPaint();
	}
	//����Բ
	q_ellipse = head_ellipse;
	if (q_ellipse->next != NULL && q_ellipse->next->x2 != INIT_DOT && q_ellipse->next->y2 != INIT_DOT) {
		q_ellipse = q_ellipse->next;
		beginPaint();
		setPenColor(RGB(q_ellipse->R, q_ellipse->G, q_ellipse->B));
		setBrushColor(EMPTY);
		ellipse(q_ellipse->x1, q_ellipse->y1, q_ellipse->x2, q_ellipse->y2);
		endPaint();
		while (q_ellipse->next && q_ellipse->next->x2 != INIT_DOT && q_ellipse->next->y2 != INIT_DOT) {
			beginPaint();
			setPenColor(EMPTY);
			setBrushColor(RGB(q_ellipse->R, q_ellipse->G, q_ellipse->B));
			ellipse(q_ellipse->x1, q_ellipse->y1, q_ellipse->x2, q_ellipse->y2);
			endPaint();
			q_ellipse = q_ellipse->next;
		}
		beginPaint();
		setPenColor(EMPTY);
		setBrushColor(RGB(q_ellipse->R, q_ellipse->G, q_ellipse->B));
		ellipse(q_ellipse->x1, q_ellipse->y1, q_ellipse->x2, q_ellipse->y2);
		endPaint();
	}
	//���ı�
	q_text = head_text;
	while (q_text->next != NULL) {
		q_text = q_text->next;
		beginPaint();
		setTextBkColor(EMPTY);
		setTextColor(RGB(q_text->color.R, q_text->color.G, q_text->color.B));
		setTextSize(q_text->size);
		PrintText(q_text->text, q_text->LT.x, q_text->LT.y);
		endPaint();
	}
}

void PrintText(Text* text, int x, int y) {    //��������,��TextT�����д洢�ĵ���Text��Ϣ��ӡ��ָ��λ��
	int caretX = x;
	int caretY = y;
	Text *temp;
	if (text != NULL) {
		temp = text;
		while (temp != NULL) {
			char value = (temp->value)[0];
			if (value>= ' '&&value <= '~'||(!(value>=0&&value<=127))) {
				paintText(caretX, caretY, temp->value);
				caretX += p_text->size;
			}
			else switch (value) {
			case TEXT('\n'):
				caretX = x;
				caretY += p_text->size;
				break;
			}
			temp = temp->next;
		}
	}

}

int distLine(int x, int y, LineT *line) {

	int x0, y0;

	x0 = (line->x1 + line->x2) / 2;
	y0 = (line->y1 + line->y2) / 2;
	return (x - x0)*(x - x0) + (y - y0)*(y - y0);          //�����ĵ��Զ��
}

LineT *SelectNearestL(int mx, int my) {    //ȷ�������ֱ��ͼ��

	LineT *min;
	int dist, mindistance;
	q_line = head_line->next;
	min = q_line;

	if (q_line == NULL) return NULL;
	else
	{
		mindistance = distLine(mx, my, q_line);
	}

	while (q_line->next) {              //���αȽϣ�ȷ����С�����ֱ��Ԫ��

		dist = distLine(mx, my, q_line);
		if (dist < mindistance) {
			min = q_line;
			mindistance = dist;
		}
		q_line = q_line->next;
	}
	dist = distLine(mx, my, q_line);
	if (dist < mindistance) {
		min = q_line;
		mindistance = dist;
	}
	minDistance[LINE] = mindistance;

	return min;  //���������ͼ�νṹָ��
}

int distRect(int x, int y, RectT *Rect) {

	int x0, y0;

	x0 = (Rect->x1 + Rect->x2) / 2;
	y0 = (Rect->y1 + Rect->y2) / 2;
	return (x - x0)*(x - x0) + (y - y0)*(y - y0);          //�����ĵ��Զ��
}

RectT *SelectNearestR(int mx, int my) {      //ȷ������ľ���ͼ��

	RectT *min;
	int dist, mindistance;
	q_rectangle = head_rectangle->next;
	min = q_rectangle;

	if (q_rectangle == NULL) return NULL;
	else
	{
		mindistance = distRect(mx, my, q_rectangle);
	}

	while (q_rectangle->next) {

		dist = distRect(mx, my, q_rectangle);
		if (dist < mindistance) {
			min = q_rectangle;
			mindistance = dist;
		}
		q_rectangle = q_rectangle->next;
	}
	dist = distRect(mx, my, q_rectangle);
	if (dist < mindistance) {
		min = q_rectangle;
		mindistance = dist;
	}
	minDistance[RECTANGLE] = mindistance;

	return min;
}

int distEllipse(int x, int y, EllipseT *ellipse) {
	int x0, y0;

	x0 = (ellipse->x1 + ellipse->x2) / 2;
	y0 = (ellipse->y1 + ellipse->y2) / 2;
	return (x - x0)*(x - x0) + (y - y0)*(y - y0);          //�����ĵ��Զ��
}

EllipseT *SelectNearestE(int mx, int my) {    //ȷ���������Բͼ��

	EllipseT *min;
	int dist, mindistance;
	q_ellipse = head_ellipse->next;
	min = q_ellipse;

	if (q_ellipse == NULL) return NULL;
	else
	{
		mindistance = distEllipse(mx, my, q_ellipse);
	}

	while (q_ellipse->next) {

		dist = distEllipse(mx, my, q_ellipse);
		if (dist < mindistance) {
			min = q_ellipse;
			mindistance = dist;
		}
		q_ellipse = q_ellipse->next;
	}
	dist = distEllipse(mx, my, q_ellipse);
	if (dist < mindistance) {
		min = q_ellipse;
		mindistance = dist;
	}
	minDistance[ELLIPSE] = mindistance;

	return min;
}

int distText(int x, int y, TextT *text) {
	int x0, y0;

	x0 = (text->LT.x + text->RB.x) / 2;
	y0 = (text->LT.y + text->RB.y) / 2;
	return (x - x0)*(x - x0) + (y - y0)*(y - y0);          //�����ĵ��Զ��
}

TextT *SelectNearestT(int mx, int my) {     //ȷ�����������ͼ��
	Text *min;
	int dist, mindistance;
	q_text = head_text->next;
	min = q_text;

	if (q_text == NULL) return NULL;
	else
	{
		mindistance = distText(mx, my, q_text);
	}

	while (q_text->next) {

		dist = distText(mx, my, q_text);
		if (dist < mindistance) {
			min = q_text;
			mindistance = dist;
		}
		q_text = q_text->next;
	}
	dist = distText(mx, my, q_text);
	if (dist < mindistance) {
		min = q_text;
		mindistance = dist;
	}
	minDistance[4] = mindistance;

	return min;
}

int PickAll(int mx, int my) {  //�Ƚ�����ͼ�����ͣ�ȷ�������һ��ͼ��

	int i, minlist;

	curline = SelectNearestL(mx, my);
	currectangle = SelectNearestR(mx, my);
	curellipse = SelectNearestE(mx, my);
	curtext = SelectNearestT(mx, my);

	minlist = 1;
	for (i = 1; i <5; i++) {
		if (minDistance[i] < minDistance[minlist]) minlist = i;
	}

	return minlist;
}

void Move(const int x, const int y, const int button, const int event) {
	static int curList, select;
	static int ox, oy;  /*ǰһ�������*/
	int dx, dy, x1, y1, x2, y2;

	if (button == LEFT_BUTTON && event == BUTTON_DOWN && select == 0) {
		curList = PickAll(x, y); /*ѡ�����*/
		ox = x;
		oy = y;
		select = 1;
	}

	if (select == 1 && button == MOUSEMOVE && event == MOUSEMOVE) {

		dx = x - ox;
		dy = y - oy;
		switch (curList) {
		case LINE:
			curline->x1 += dx;
			curline->y1 += dy;
			curline->x2 += dx;
			curline->y2 += dy;
			break;
		case RECTANGLE:
			x1 = currectangle->x1 + dx;
			y1 = currectangle->y1 + dy;
			x2 = currectangle->x2 + dx;
			y2 = currectangle->y2 + dy;
			if (x1 < x2) {
				currectangle->x1 = x1;
				currectangle->x2 = x2;
			}
			else {
				currectangle->x1 = x2;
				currectangle->x2 = x1;
			}
			if (y1 < y2) {
				currectangle->y1 = y1;
				currectangle->y2 = y2;
			}
			else {
				currectangle->y1 = y2;
				currectangle->y2 = y1;
			}
			break;
		case ELLIPSE:
			x1 = curellipse->x1 + dx;
			y1 = curellipse->y1 + dy;
			x2 = curellipse->x2 + dx;
			y2 = curellipse->y2 + dy;
			if (x1 < x2) {
				curellipse->x1 = x1;
				curellipse->x2 = x2;
			}
			else {
				curellipse->x1 = x2;
				curellipse->x2 = x1;
			}
			if (y1 < y2) {
				curellipse->y1 = y1;
				curellipse->y2 = y2;
			}
			else {
				curellipse->y1 = y2;
				curellipse->y2 = y1;
			}
			break;
		case _TEXT:
			curtext->LT.x += dx;
			curtext->LT.y += dy;
			curtext->RB.x += dx;
			curtext->RB.y += dy;
			break;
		}

		beginPaint();
		clearDevice();
		endPaint();
		initInterface();
		button_move_end(&_move);
		DrawAll();
		ox = x;
		oy = y;
	}

	if (button == LEFT_BUTTON && event == BUTTON_UP) {
		select = 0;
	}

	return END_WITHOUT_ERROR;
}

void Change(const int x, const int y, const int button, const int event) {    //����ģ��
	static int curList, select;
	static int ox, oy;  /*ǰһ�������*/
	int dx, dy, x1, y1, x2, y2;
	float dvalue;

	if (button == LEFT_BUTTON && event == BUTTON_DOWN && select == 0) {
		curList = PickAll(x, y); /*ѡ�����*/
		ox = x;
		oy = y;
		select = 1;
	}

	if (select == 1 && button == MOUSEMOVE && event == MOUSEMOVE) {

		dx = x - ox;
		dy = y - oy;
		switch (curList) {
		case LINE:
			if (fabs(ox - curline->x1) + fabs(oy - curline->y1) <
				fabs(ox - curline->x2) + fabs(oy - curline->y2)) {
				curline->x1 += dx;
				curline->y1 += dy;
			}
			else {
				curline->x2 += dx;
				curline->y2 += dy;
			}
			break;
		case RECTANGLE:
			if (fabs(ox - currectangle->x1) < fabs(ox - currectangle->x2)) {
				currectangle->x1 += dx;
			}
			else {
				currectangle->x2 += dx;
			}
			if (fabs(oy - currectangle->y1) < fabs(oy - currectangle->y2)) {
				currectangle->y1 += dy;
			}
			else {
				currectangle->y2 += dy;
			}
			break;
		case ELLIPSE:
			if (fabs(ox - curellipse->x1) < fabs(ox - curellipse->x2)) {
				curellipse->x1 += dx;
			}
			else {
				curellipse->x2 += dx;
			}
			if (fabs(oy - curellipse->y1) < fabs(oy - curellipse->y2)) {
				curellipse->y1 += dy;
			}
			else {
				curellipse->y2 += dy;
			}
			break;
		}
		beginPaint();
		clearDevice();
		endPaint();
		initInterface();
		button_change_end(&_change);
		DrawAll();
		ox = x;
		oy = y;
	}

	if (button == LEFT_BUTTON && event == BUTTON_UP) {
		select = 0;
	}

	return END_WITHOUT_ERROR;
}

void ChangeCaretPos(const int x, const int y) {   //���Ĺ��λ��
	caretPos.x = x;
	caretPos.y = y;
}

void AddChar(char* c) {         //�����̽��յ������ַ���Ϣʱ���ѺϷ��ַ��洢��������
	Text* search = NULL;
	Text* temp = (Text*)malloc(sizeof(Text));
	temp->value = c;
	temp->next = NULL;
	if (p_text->text != NULL) {
		search = p_text->text;
		while (search->next != NULL) {
			search = search->next;
		}
		search->next = temp;
	}
	else {
		p_text->text = temp;
	}
	p_text->cnt++;
}     

void DeleteChar() {       //�����̽��յ�Back������ʱ��ɾ������ĩβ�ַ�
	Text *searchq, *searchp;
	if (p_text->text != NULL) {
		if (p_text->text->next == NULL) {
			p_text->text = NULL;
		}
		else {
			searchp = p_text->text;
			searchq = p_text->text;
			while (searchq->next != NULL) {
				searchp = searchq;
				searchq = searchq->next;
			}
			searchp->next = NULL;
			free(searchq);
		}
		p_text->cnt--;
	}
}
