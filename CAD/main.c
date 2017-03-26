/*
*    main.c
*    C Project
*	 Team production.
*	 Team member: Jiang Wen, Huang Nianmei, Li Jianing.
*    This file was created by Wen Jiang on 3/14/2017.
*    Copyright (c) 2017 Wen Jiang. All rights reserved.
*/
#include"main.h"
//typedef struct MSGQUEUE {
//	int32_t size;
//	int32_t style;
//	struct MSGQUEUE *pNext;
//}MsgQueue;

int32_t m_lMode = 0;
int32_t m_Text_Postion_x = 0;
int32_t m_Text_Postion_y = 0;
ACL_Color m_CurrentColor = BLACK;
MsgQueue* p_MsgHead = NULL;
MsgQueue CAD_Msg;
int32_t IO_Init();
int32_t DrawRectangle(int x0, int y0, int size, int style);
int32_t Erase(int x0, int y0, int size, int style);
int32_t Craming(int x0, int y0, int size, int style);
int32_t Words(int x0, int y0, int size, int style);
//bellows are newly added function
int32_t	Regular_Triangle(int x0, int y0, int size, int style) { ; }
int32_t Right_Triangle(int x0, int y0, int size, int style) { ; }
int32_t Five_Star(int x0, int y0, int size, int style) { ; }
int32_t Up_Arrow(int x0, int y0, int size, int style) { ; }
int32_t DrawSquare(int x0, int y0, int size, int style) { ; }
int32_t DrawCurve(int x0, int y0, int size, int style) { ; }
int32_t DrawCircle(int x0, int y0, int size, int style) { ; }
int32_t Arc_Rectangle(int x0, int y0, int size, int style) { ; }
int32_t DrawPentagon(int x0, int y0, int size, int style) { ; }
int32_t DownArrow(int x0, int y0, int size, int style) { ; }
int32_t Hexagon(int x0, int y0, int size, int style) { ; }
int32_t Rhombus(int x0, int y0, int size, int style) { ; }
int32_t Six_Star(int x0, int y0, int size, int style) { ; }
int32_t ForeStar(int x0, int y0, int size, int style) { ; }
//barcket the latetst comment
MsgQueue* NewMsgQueue();
MsgQueue* Push_Back_Msg(const MsgQueue* p_CurrentMsg);
MsgQueue Pop_Msg();
TimerEventCallback TimerEvent(int timerID);
CharEventCallback CharEvent(char c);
KeyboardEventCallback KeyboardEvent(int key, int event);
MouseEventCallback MouseEvent(int x, int y, int button, int event);

int Setup() {
	initWindow("CAD", DEFAULT, DEFAULT, 1024, 768);
	initConsole();
	IO_Init();
	registerTimerEvent(&TimerEvent);
	registerKeyboardEvent(&KeyboardEvent);
	registerCharEvent(&CharEvent);
	registerMouseEvent(&MouseEvent);
	return 0;
}
TimerEventCallback TimerEvent(int timerID) { ; }
CharEventCallback CharEvent(char c) {
	//static String Words = NULL;
	//Hidden dangreous
	static String Words_string;
	static int32_t String_Index = 0;
	if (m_lMode != WORDS_MODE) {
		static int32_t flag_input = 0;
		static int32_t num = 0;
		static MsgQueue Msg;
		int32_t length = 0;
		int32_t length_Temp = num;
		while (length_Temp != 0) {
			length++;
			length_Temp = length_Temp / 10;
		}
		if (0 == flag_input) flag_input = 1;
		if (CHAR_ENTER == c) {
			flag_input++;
			num = 0;
		}
		beginPaint();
		paintText(0, 0, CLEAN_LINE);
		switch (flag_input)
		{
		case 0:break;
		case 1:
			//New feature caretpos.
			SetCaretPos(CARET_POSITON_X_SIZE + length*SIZE_PER_CARET, CARET_POSITON_Y);
			showCaret();
			if (isdigit(c)) {
				num = num * 10 + c - '0';
			}
			String Dynamic_Size;
			sprintf(Dynamic_Size, "size = %d pixels", num);
			paintText(0, 0, Dynamic_Size);
			CAD_Msg.Size = num;
			break;
		case 2:
			SetCaretPos(CARET_POSITON_X_STYLE + length*SIZE_PER_CARET, CARET_POSITON_Y);
			if (isdigit(c)) {
				num = num * 10 + c - '0';
			}
			sprintf(Dynamic_Size, "style = %d", num);
			paintText(0, 0, Dynamic_Size);
			CAD_Msg.Style = num;
			break;
		case 3:
			flag_input = 0;
			hideCaret();
			break;
		default:
			break;
		}
		endPaint();
	}
	else {
		int32_t strlength = strlen(Words);
		String Words_Temp;
		sprintf(Words_Temp, "%c", c);
		strcat(Words_string, Words_Temp);
		SetCaretPos(m_Text_Postion_x+ strlength*SIZE_PER_CARET, m_Text_Postion_y);
		
		showCaret();
		//paintText(0, 0, Dynamic_Size);
		//CAD_Msg.Size = num;
	}
}
KeyboardEventCallback KeyboardEvent(int key, int event) {
	printf("Key = %d,event = %d\n", key, event);
	if (key == CHAR_ENTER) {
		MsgQueue Msg_Enter;
		Msg_Enter.Style = -1;
		Msg_Enter.Size = -1;
		Push_Back_Msg(&Msg_Enter);
	}
}
MouseEventCallback MouseEvent(int x, int y, int button, int event) {
	//static int32_t  Click_Times = 0;
	static int32_t PressDown = 0;
	static MsgQueue Current_Msg;
	switch (event)
	{
	case 0: PressDown = 1; break;
	case 1: PressDown = 2; break;
	case 2: PressDown = 0; break;
	}
	//Use Static variable to check whether the user's Mouse is pressing & moving.
	//Also it can be easy to write the pen function and erase.
	static int i = 0;
	if (i == 0) {
		DrawRectangle(100, 100, 5, 1);
		i = 1;
	}
	printf("x=%d, y=%d, butoton =%d, event = %d\n", x, y, button, event);
	if (x > RECTANGLE_X_LEFT && x < RECTANGLE_X_RIGHT && y > RECTANGLE_Y_UP && y < RECTANGLE_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 8;
	}
	else if (x > PEN_BUTTON_X_LEFT && x < PEN_BUTTON_X_RIGHT && y > PEN_BUTTON_Y_UP && y < PEN_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 1;
	}
	else if (x > ERASE_X_LEFT && x < ERASE_X_RIGHT && y > ERASE_Y_UP && y < ERASE_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 3;
	}
	else if (x > CURVE_BUTTON_X_LEFT && x<CURVE_BUTTON_X_RIGHT && y>CURVE_BUTTON_Y_UP && y < CURVE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 4;
	}
	else if (x > CRAMING_BUTTON_X_LEFT && x<CRAMING_BUTTON_X_RIGHT && y>CRAMING_BUTTON_Y_UP && y < CRAMING_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 5;
	}
	else if (x > LINE_BUTTON_X_LEFT && x< LINE_BUTTON_X_RIGHT && y > LINE_BUTTON_Y_UP && y < LINE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 2;
	}

	else if (x > WORDS_BUTTON_X_LEFT && x< WORDS_BUTTON_X_RIGHT && y> WORDS_BUTTON_Y_UP && y < WORDS_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 7;
	}
	else if (x > CIRCLE_BUTTON_X_LEFT && x< CIRCLE_BUTTON_X_RIGHT && y> CIRCLE_BUTTON_Y_UP && y < CIRCLE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 6;
	}
	else if (x >REGULAR_TRIANGLE_BUTTON_X_LEFT && x< REGULAR_TRIANGLE_BUTTON_X_RIGHT && y> REGULAR_TRIANGLE_BUTTON_Y_UP && y < REGULAR_TRIANGLE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 9;
	}
	else if (x >ARC_RECTANGLE_BUTTON_X_LEFT && x< ARC_RECTANGLE_BUTTON_X_RIGHT && y> ARC_RECTANGLE_BUTTON_Y_UP && y < ARC_RECTANGLE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 10;
	}
	else if (x >RIGHT_TRIANGLE_BUTTON_X_LEFT && x< RIGHT_TRIANGLE_BUTTON_X_RIGHT && y>RIGHT_TRIANGLE_BUTTON_Y_UP && y < RIGHT_TRIANGLE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 11;
	}
	else if (x >FREE_SHAPE_BUTTON_X_LEFT && x< FREE_SHAPE_BUTTON_X_RIGHT && y>FREE_SHAPE_BUTTON_Y_UP && y <FREE_SHAPE_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 11;//12 in contribution
	}
	else if (x >FORE_STAR_BUTTON_X_LEFT && x< FORE_STAR_BUTTON_X_RIGHT && y>FORE_STAR_BUTTON_Y_UP && y < FORE_STAR_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 16;
	}
	else if (x >PENTAGON_BUTTON_X_LEFT && x< PENTAGON_BUTTON_X_RIGHT && y>PENTAGON_BUTTON_Y_UP && y < PENTAGON_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 14;
	}
	else if (x >HEXAGON_BUTTON_X_LEFT && x< HEXAGON_BUTTON_X_RIGHT && y>HEXAGON_BUTTON_Y_UP && y < HEXAGON_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 15;
	}
	else if (x >RHOMBUS_BUTTON_X_LEFT && x< RHOMBUS_BUTTON_X_RIGHT && y>RHOMBUS_BUTTON_Y_UP && y < RHOMBUS_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 13;
	}
	else if (x >FIVE_STAR_BUTTON_X_LEFT && x<FIVE_STAR_BUTTON_X_RIGHT && y>FIVE_STAR_BUTTON_Y_UP && y < FIVE_STAR_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 17;
	}
	else if (x >SIX_STAR_BUTTON_X_LEFT && x<SIX_STAR_BUTTON_X_RIGHT && y>SIX_STAR_BUTTON_Y_UP && y < SIX_STAR_BUTTON_Y_DOWN && button == 1 && event == 0) {
		beginPaint();
		setPenColor(BLACK);
		paintText(0, 0, CLEAN_LINE);
		paintText(0, 0, "Please input Size(pixels) and Style. Seperated by enter");
		setPenColor(m_CurrentColor);
		endPaint();
		m_lMode = 18;
	}
	/*int32_t	Rgular_Triangle(int x0, int y0, int size, int style) { ; }
int32_t Right_Triangle(int x0, int y0, int size, int style) { ; }
int32_t Five_Star(int x0, int y0, int size, int style) { ; }
int32_t Up_Arrow(int x0, int y0, int size, int style) { ; }
int32_t DrawSquare(int x0, int y0, int size, int style) { ; }
int32_t DrawCurve(int x0, int y0, int size, int style) { ; }
int32_t DrawCircle(int x0, int y0, int size, int style) { ; }
int32_t Arc_Rectangle(int x0, int y0, int size, int style) { ; }
int32_t DrawPentagon(int x0, int y0, int size, int style) { ; }
int32_t DownArrow(int x0, int y0, int size, int style) { ; }
int32_t Hexagon(int x0, int y0, int size, int style) { ; }*/
	if (0 != m_lMode && PressDown == 1)
		//Beacuse we have varible PressDown we don't care the event and button.
	{
		switch (m_lMode) {
		case 1:
			Pen(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 8:
			DrawRectangle(x, y, 1, 1);
			break;
			//Rectangle tool
		case 3:
			printf("In call erase\n");
			Erase(x, y, CAD_Msg.Size, CAD_Msg.Style);
			//Erase mode.
			break;
		case 5:
			Craming(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 2:
			StraightLine(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 7:
			Words(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 9:
			Regular_Triangle(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 10:
			Arc_Rectangle(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 11:
			Right_Triangle(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 13:
			Rhombus(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 14:
			DrawPentagon(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 15:
			Hexagon(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 16:
			ForeStar(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 17:
			Five_Star(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		case 18:
			Six_Star(x, y, CAD_Msg.Size, CAD_Msg.Style);
			break;
		}
	}
}
int32_t IO_Init() {
	p_MsgHead = NewMsgQueue();
	CAD_Msg.Size = 10;
	CAD_Msg.Style = 1;
	beginPaint();
	ACL_Image Pallet, DashBoard;
	loadImage(".//pallet.bmp", &Pallet);
	putImage(&Pallet, PALLETX, PALLETY);
	loadImage(".//DashBoard.bmp", &DashBoard);
	putImage(&Pallet, PALLETX, PALLETY);
	putImage(&DashBoard, DASHBOARDX, DASHBOARDY);
	endPaint();
}
int32_t DrawRectangle(int x0, int y0, int size, int style) {
	switch (style) {
	case 1:
		printf("In darw\n");
		beginPaint();
		setPenColor(RED);
		rectangle(x0, y0, x0 + size * 30, y0 + size * 20);
		endPaint();
	}
}
int32_t Erase(int x0, int y0, int size, int style) {
	static int32_t Alert_Flag = 1;
	if (x0 > PANEL_BUNDARY_LEFT && x0 < PANEL_BUNDARY_RIGHT && y0 < PANEL_BUNDARY_DOWN) {
		//Encapulse the conditon to a bool lean function in the future.
		//If-statement to avoid paint the panel.
		switch (style)//0 by default
		{
		case 1:
			beginPaint();
			setBrushColor(WHITE);
			setPenColor(WHITE);
			rectangle(x0, y0, x0 + size, y0 + size);
			setBrushColor(m_CurrentColor);
			setPenColor(m_CurrentColor);
			endPaint();
			break;
		case 2:
			beginPaint();
			setBrushColor(WHITE);
			setPenColor(WHITE);
			ellipse(x0, y0, x0 + size, y0 + size);
			setBrushColor(m_CurrentColor);
			setPenColor(m_CurrentColor);
			endPaint();
			break;
		default:
			printf("In msgBox\n");
			msgBox("Style out of range", "Please input style range from 1 to 2", Alert_Flag);
			Alert_Flag = -1;
			break;
		}
	}
	return 0;
}
int32_t Craming(int x0, int y0, int size, int style) {
	static int32_t Alert_Flag = 1;
	if (x0 > PANEL_BUNDARY_LEFT && x0 < PANEL_BUNDARY_RIGHT && y0 < PANEL_BUNDARY_DOWN) {
		//Encapulse the conditon to a bool lean function in the future.
		//If-statement to avoid paint the panel.
		switch (style)//0 by default
		{
		case 1:
			beginPaint();
			rectangle(x0, y0, x0 + size, y0 + size);
			endPaint();
			break;
		case 2:
			beginPaint();
			ellipse(x0, y0, x0 + size, y0 + size);
			endPaint();
			break;
		default:
			printf("In msgBox\n");
			msgBox("Style out of range", "Please input style range from 1 to 2", Alert_Flag);
			Alert_Flag = -1;
			break;
		}
	}
}
MsgQueue* NewMsgQueue() {
	MsgQueue *p_Temp = (MsgQueue*)malloc(sizeof(MsgQueue));
	p_Temp->pNext = NULL;
}//Encapusule to avoid dangling pointer.
MsgQueue* Push_Back_Msg(const MsgQueue* p_CurrentMsg) {
	MsgQueue *p_Iterator = NULL;
	if (NULL == p_MsgHead->pNext) {
		p_Iterator = p_MsgHead;
		p_MsgHead->pNext = NewMsgQueue();
	}
	else {
		for (p_Iterator = p_MsgHead; p_Iterator->pNext != NULL; p_Iterator = p_Iterator->pNext);
		p_Iterator->pNext = NewMsgQueue();
	}
	p_Iterator->Size = p_CurrentMsg->Size;
	p_Iterator->Style = p_CurrentMsg->Style;
	return p_Iterator;
}
MsgQueue Pop_Msg() {
	MsgQueue p_Return = *p_MsgHead;
	MsgQueue *p_FreeTemp = p_MsgHead;
	if (NULL == p_MsgHead->pNext) {
		p_MsgHead = NewMsgQueue();
	}
	else {
		p_MsgHead = p_MsgHead->pNext;
	}
	free(p_FreeTemp);
	return p_Return;
}
int32_t StraightLine(int x0, int y0, int size, int style) {
	static int32_t Pen_Times = 0;
	static int32_t Alert_Flag = 1;
	static int32_t Pre_x = 0, Pre_y = 0;
	if (Pen_Times == 0) {
		Pen_Times = 1;
		beginPaint();
		setPenColor(WHITE);
		endPaint();
	}
	if (x0 > PANEL_BUNDARY_LEFT && x0 < PANEL_BUNDARY_RIGHT && y0 < PANEL_BUNDARY_DOWN) {
		//Encapulse the conditon to a bool lean function in the future.
		//If-statement to avoid paint the panel.
		switch (style)//0 by default
		{
		case 1:
			beginPaint();
			line(Pre_x, Pre_y, x0, y0);
			endPaint();
			break;
		case 2:
			beginPaint();
			line(Pre_x, Pre_y, x0, y0);
			endPaint();
			break;
		default:
			printf("In msgBox\n");
			msgBox("Style out of range", "Please input style range from 1 to 2", Alert_Flag);
			Alert_Flag = -1;
			break;
		}
	}
	if (Pen_Times == 1) {
		beginPaint();
		setPenColor(m_CurrentColor);
		Pen_Times = -1;
		endPaint();
	}
	Pre_x = x0;
	Pre_y = y0;
}
int32_t Words(int x0, int y0, int size, int style) {
	beginPaint();
	hideCaret();
	endPaint();
	m_Text_Postion_x = x0;
	m_Text_Postion_y = y0;
}
/* The two functions below and Pen_Bottom added */
int32_t Pen(int x0, int y0, int size, int style) {
	static int32_t Pen_Times = 0;
	static int32_t Alert_Flag = 1;
	static int32_t Pre_x = 0, Pre_y = 0;
	printf("0\n");
	/*if (Pen_Times == 0) {
	Pen_Times = 1;
	printf("1\n");
	return;
	}
	if (Pen_Times == 1) {
	Pre_x = x0;
	Pre_y = y0;
	Pen_Times = 2;
	printf("2\n");
	}

	if (Pen_Times == 2 && abs(getX() - Pre_x) > 20 || abs(getY() - Pre_y) > 20) {
	Pen_Times = 0;
	}
	setPenColor(BLACK);
	*/
	if (x0 > PANEL_BUNDARY_LEFT && x0 < PANEL_BUNDARY_RIGHT && y0 < PANEL_BUNDARY_DOWN && abs(x0 - Pre_x) < 20 || abs(y0 - Pre_y) < 20) {
		//Encapulse the conditon to a bool lean function in the future.
		//If-statement to avoid paint the panel.
		switch (style)//0 by default
		{
		case 1:
			beginPaint();
			setPenWidth(size);
			printf("3\n");
			line(Pre_x, Pre_y, x0, y0);
			endPaint();
			break;
		case 2:
			beginPaint();
			setPenWidth(size);
			line(Pre_x, Pre_y, x0, y0);
			endPaint();
			break;
		default:
			printf("In msgBox\n");
			msgBox("Style out of range", "Please input style range from 1 to 2", Alert_Flag);
			Alert_Flag = -1;
			break;
		}
	}
	if (Pen_Times == 1) {
		beginPaint();
		setPenColor(m_CurrentColor);
		Pen_Times = -1;
		endPaint();
	}
	Pre_x = x0;
	Pre_y = y0;
}
int32_t DrawCurve(int x0, int y0, int size, int style) {
	static int32_t Alert_Flag = 1;
	static int32_t Pre_x = 0, Pre_y = 0;


	if (x0 > PANEL_BUNDARY_LEFT && x0 < PANEL_BUNDARY_RIGHT && y0 < PANEL_BUNDARY_DOWN) {
		//Encapulse the conditon to a bool lean function in the future.
		//If-statement to avoid paint the panel.
		switch (style)//0 by default
		{
		case 1:
			beginPaint();
			arc(Pre_x, Pre_y, x0, y0, Pre_x - 30, Pre_y, x0, y0);
			endPaint();
			break;
		case 2:
			beginPaint();
			line(Pre_x, Pre_y, x0, y0);
			endPaint();
			break;
		default:
			printf("In msgBox\n");
			msgBox("Style out of range", "Please input style range from 1 to 2", Alert_Flag);
			Alert_Flag = -1;
			break;
		}
	}

	Pre_x = x0;
	Pre_y = y0;
}
