#include"acllib.h"
#include"CAD.h"
#include<stdio.h>

char _bufstr[3];
char *bufstr;
char *bufc;
int cnt = 0;

MouseEventCallback MouseEvent(int x, int y, int button, int event);
CharEventCallback CharEvent(char c);
KeyboardEventCallback KeyboardEvent(int key, int event);

int Setup() {
	initWindow("CAD", DEFAULT, DEFAULT, SCREEN_LENGTH, SCREEN_HEIGHT);
	//initConsole();
	reset_screen();                   //初始化窗口界面
	registerMouseEvent(MouseEvent);
	registerKeyboardEvent(KeyboardEvent);
	registerCharEvent(CharEvent);

	return 0;
}

MouseEventCallback MouseEvent(int x, int y, int button, int event) {   //鼠标回调函数
	mouse_position.mouse_x = x;                       //用全局变量接收当前鼠标的坐标
	mouse_position.mouse_y = y;
	//printf("button=%d   event=%d\n", button, event);
	if (button == LEFT_BUTTON && event == BUTTON_UP) {
		if (check_position(&mouse_position, &_line) == IS_IN) {     //如果点击左键发生在直线按钮处
			initInterface();
			button_line_end(&_line);                               //将按钮换色
			button_model = LINE;
			return END_WITHOUT_ERROR;
		}

		else if (check_position(&mouse_position, &_rectangle) == IS_IN) {    //如果点击左键发生在矩形按钮处，则进入绘制矩形的状态
			initInterface();
			button_rectangle_end(&_rectangle);
			button_model = RECTANGLE;
			return END_WITHOUT_ERROR;
		}
		else if (check_position(&mouse_position, &_ellipse) == IS_IN) {      //如果点击左键发生在椭圆按钮处，则进入绘制椭圆的状态
			initInterface();
			button_ellipse_end(&_ellipse);
			button_model = ELLIPSE;
			return END_WITHOUT_ERROR;
		}

		else if (check_position(&mouse_position, &_text) == IS_IN) {          //如果点击左键发生在文字按钮处，则进入绘制文字的状态
			initInterface();
			button_text_end(&_text);
			button_model = _TEXT;
			return END_WITHOUT_ERROR;
		}

		else if (check_position(&mouse_position, &_move) == IS_IN) {          //如果点击左键发生在移动按钮处，则进入绘制文字的状态
			initInterface();
			button_move_end(&_move);
			button_model = MOVE;
			return END_WITHOUT_ERROR;
		}
		else if (check_position(&mouse_position, &_change) == IS_IN) {          //如果点击左键发生在缩放按钮处，则进入绘制文字的状态
			initInterface();
			button_change_end(&_change);
			button_model = CHANGE;
			return END_WITHOUT_ERROR;
		}

		else if (check_position(&mouse_position, &_clearscreen) == IS_IN) reset_screen();      //如果点击左键发生在清屏按钮处，则重置

		else if (check_position(&mouse_position, &color_1) == IS_IN) {      //如果左键发生在调色板按钮处，改变图形绘制的颜色
			check_color = COLOR_DECIDED;
			R = 255;
			G = 128;
			B = 128;
		}
		else if (check_position(&mouse_position, &color_2) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 255;
			G = 0;
			B = 0;
		}
		else if (check_position(&mouse_position, &color_3) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 255;
			G = 255;
			B = 0;
		}
		else if (check_position(&mouse_position, &color_4) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 0;
			G = 0;
			B = 0;
		}
		else if (check_position(&mouse_position, &color_5) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 128;
			G = 255;
			B = 0;
		}
		else if (check_position(&mouse_position, &color_6) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 0;
			G = 0;
			B = 255;
		}
		else if (check_position(&mouse_position, &color_7) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 128;
			G = 0;
			B = 255;
		}
		else if (check_position(&mouse_position, &color_8) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 255;
			G = 128;
			B = 255;
		}
		else if (check_position(&mouse_position, &color_9) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 192;
			G = 192;
			B = 192;
		}
		else if (check_position(&mouse_position, &color_10) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 0;
			G = 64;
			B = 128;
		}
		else if (check_position(&mouse_position, &color_11) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 207;
			G = 16;
			B = 248;
		}
		else if (check_position(&mouse_position, &color_12) == IS_IN) {
			check_color = COLOR_DECIDED;
			R = 11;
			G = 249;
			B = 242;
		}
	}
	else;


	//根据按钮的状态以及paint结构的成员变量，进入不同图形的绘制状态
	if (button_model == LINE) {
		Paint_line(x, y, button, event);
	}
	else if (button_model == RECTANGLE) {
		Paint_rectangle(x, y, button, event);
	}
	else if (button_model == ELLIPSE) {
		Paint_ellipse(x, y, button, event);
	}
	else if (button_model == _TEXT) {
		Paint_text(x, y, button, event);
	}
	else if (button_model == MOVE) {
		Move(x, y, button, event);
	}
	else if (button_model == CHANGE) {
		Change(x, y, button, event);
	}
	else;

	return END_WITHOUT_ERROR;
}

CharEventCallback CharEvent(char c) {     //字符回调函数
	printf("%c", c);
	if (isInput == IS_INPUT) {
		beginPaint();
		setTextBkColor(EMPTY);
		setTextSize(p_text->size);
		setTextColor(RGB(p_text->color.R, p_text->color.G, p_text->color.B));
		if (c >= ' '&&c <= '~') {
			bufc = (char*)malloc(sizeof(char) * 2);
			bufc[0] = c;
			bufc[1] = '\0';
			AddChar(bufc);  //把当前字符添加到文本链表中
			paintText(caretPos.x, caretPos.y, bufc);
			caretPos.x += p_text->size;
			if (caretPos.x > textEnd.x) {
				textEnd.x = caretPos.x;
			}
			if (caretPos.y > textEnd.y) {
				textEnd.y = caretPos.y;
			}
			setCaretPos(caretPos.x, caretPos.y);
		}
		else if(!(c>=0&&c<=127)){
			_bufstr[cnt] = c;
			cnt++;
			if (cnt == 2) {
				_bufstr[cnt] = '\0';
				cnt = 0;
				bufstr = (char*)malloc(sizeof(char) * 3);
				bufstr[0] = _bufstr[0];
				bufstr[1] = _bufstr[1];
				bufstr[2] = _bufstr[2];
				AddChar(bufstr);  //把当前字符添加到文本链表中
				paintText(caretPos.x, caretPos.y, bufstr);
				caretPos.x += p_text->size;
				if (caretPos.x > textEnd.x) {
					textEnd.x = caretPos.x;
				}
				if (caretPos.y > textEnd.y) {
					textEnd.y = caretPos.y;
				}
				setCaretPos(caretPos.x, caretPos.y);
			}
		}
		endPaint();
	}
	return END_WITHOUT_ERROR;
}

KeyboardEventCallback KeyboardEvent(int key, int event) {  //键盘回调函数
	if (isInput == IS_INPUT&&event == KEY_DOWN) {
		switch (key) {
		case VK_RETURN:
			caretPos.x = p_text->LT.x;
			caretPos.y += p_text->size;
			bufc = (char*)malloc(sizeof(char) * 2);
			bufc[0] = '\n';
			bufc[1] = '\0';
			AddChar(bufc);
			beginPaint();
			setCaretPos(caretPos.x, caretPos.y);
			endPaint();
			break;
		case VK_BACK:
			if (caretPos.x >= p_text->LT.x) {
				caretPos.x -= p_text->size;
				beginPaint();
				setCaretPos(caretPos.x, caretPos.y);
				endPaint();
				DeleteChar();  //把当前文本链表中的最后一个字符删除
			}
			beginPaint();
			clearDevice();
			endPaint();
			initInterface();
			button_text_end(&_text);
			DrawAll();
			break;
		}
	}
	return END_WITHOUT_ERROR;
}

