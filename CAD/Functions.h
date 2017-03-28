/*
*    Functions.h
*    C Project
*	 Team production.
*	 Team member: Jiang Wen, Huang Nianmei, Li Jianing.
*    This file was created by Wen Jiang on 3/28 2017.
*    Copyright (c) 2017 Wen Jiang,Huang Nianmei, Li Jianing. All rights reserved.
*/
#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include"main.h"

//ToolsModes
#define END_WITHOUT_ERROR 0
#define M_PEN 1
#define M_LINE 2
#define  M_ERASE 3
#define M_CURVE 4
#define M_CRAMING 5
#define M_CIRCLE 6
#define M_WORDS 7
#define M_RECTANGLE 8
#define M_REGULAR_TRI 9
#define M_ARC_RECTANGLE 10
#define M_RIGHT_TRIANGLE 11
#define  M_FREE_SHAPE 12
#define  M_RHOMBUS 13
#define M_PENTAGON 14
#define M_HEXAGON 15
#define M_FIVE_STAR 17
#define M_FOUR_STAR 16
#define M_SIX_STAR 18
//Status
#define TRUE 1
#define FALSE 0
#define OFF -1
#define MOUSE_LEFT 1
#define CLICK 0
//Constants
#define PALLETX 960
#define PALLETY 20
#define DASHBOARDX 0
#define DASHBOARDY 20
#define RECTANGLE_X_LEFT 45
#define RECTANGLE_X_RIGHT 75
#define RECTANGLE_Y_UP 125
#define RECTANGLE_Y_DOWN 145
#define ERASE_X_LEFT 0
#define ERASE_X_RIGHT 30
#define ERASE_Y_UP 55
#define ERASE_Y_DOWN 85
#define PANEL_BUNDARY_LEFT 75
#define PANEL_BUNDARY_RIGHT 960
#define PANEL_BUNDARY_DOWN 740
#define CHAR_ENTER 13
#define CARET_POSITON_Y 5
#define CARET_POSITON_X_SIZE 50
#define CARET_POSITON_X_STYLE 55
#define SIZE_PER_CARET 7
#define MAX_STYLE 2
#define MIN_STYLE 1
#define TEXT_SIZE 30
#define WORDS_MODE 7
#define CLEAN_LINE "                                                                                                                                                                                        "

#define COLORS_X_LEFT 955
#define COLORS_X_RIGHT 1024
#define COLORS_Y_UP 25
#define COLORS_Y_DOWN 415
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_BACKSPACE 8
#define PIXEL_INTESITY 3
#define DEXMINAL 10
#define STRING_LENGTH 16
//Panels position's Marco definaton.
#define PEN_BUTTON_X_LEFT 0
#define PEN_BUTTON_X_RIGHT 35
#define PEN_BUTTON_Y_UP 25
#define PEN_BUTTON_Y_DOWN 55
#define ERASER_BUTTON_X_LEFT 0
#define ERASER_BUTTON_X_RIGHT
#define ERASER_BUTTON_Y_UP 55
#define ERASER_BUTTON_Y_DOWN 85
#define CRAMING_BUTTON_X_LEFT 0
#define CRAMING_BUTTON_X_RIGHT 35
#define CRAMING_BUTTON_Y_UP 85
#define CRAMING_BUTTON_Y_DOWN 120
#define WORDS_BUTTON_X_LEFT 0
#define WORDS_BUTTON_X_RIGHT 35
#define WORDS_BUTTON_Y_UP 120
#define WORDS_BUTTON_Y_DOWN 155
#define REGULAR_TRIANGLE_BUTTON_X_LEFT 0
#define REGULAR_TRIANGLE_BUTTON_X_RIGHT 35
#define REGULAR_TRIANGLE_BUTTON_Y_UP 155
#define REGULAR_TRIANGLE_BUTTON_Y_DOWN 185
#define RIGHT_TRIANGLE_BUTTON_X_LEFT 0
#define RIGHT_TRIANGLE_BUTTON_X_RIGHT 35
#define RIGHT_TRIANGLE_BUTTON_Y_UP 185
#define RIGHT_TRIANGLE_BUTTON_Y_DOWN 215
#define RHOMBUS_BUTTON_X_LEFT 0
#define RHOMBUS_BUTTON_X_RIGHT 35
#define RHOMBUS_BUTTON_Y_UP 215
#define RHOMBUS_BUTTON_Y_DOWN 250
#define HEXAGON_BUTTON_X_LEFT 0
#define HEXAGON_BUTTON_X_RIGHT 35
#define HEXAGON_BUTTON_Y_UP 250
#define HEXAGON_BUTTON_Y_DOWN 285
#define FIVE_STAR_BUTTON_X_LEFT 0
#define FIVE_STAR_BUTTON_X_RIGHT 35
#define FIVE_STAR_BUTTON_Y_UP 285
#define FIVE_STAR_BUTTON_Y_DOWN 315
#define RIGHT_ARROW_BUTTON_X_LEFT 0
#define RIGHT_ARROW_BUTTON_X_RIGHT 35
#define RIGHT_ARROW_BUTTON_Y_UP 315
#define RIGHT_ARROW_BUTTON_Y_DOWN 350
#define UP_ARROW_BUTTON_X_LEFT 0
#define UP_ARROW_BUTTON_X_RIGHT 35
#define UP_ARROW_BUTTON_Y_UP 350
#define UP_ARROW_BUTTON_Y_DOWN 385
#define SQUARE_DIALOG_BUTTON_X_LEFT 0
#define SQUARE_DIALOG_BUTTON_X_RIGHT 35
#define SQUARE_DIALOG_BUTTON_Y_UP 385
#define SQUARE_DIALOG_BUTTON_Y_DOWN 410
#define LINE_BUTTON_X_LEFT 35
#define LINE_BUTTON_X_RIGHT 70
#define LINE_BUTTON_Y_UP 25
#define LINE_BUTTON_Y_DOWN 55
#define CURVE_BUTTON_X_LEFT 35
#define CURVE_BUTTON_X_RIGHT 70
#define CURVE_BUTTON_Y_UP 55
#define CURVE_BUTTON_Y_DOWN 85
#define CIRCLE_BUTTON_X_LEFT 35
#define CIRCLE_BUTTON_X_RIGHT 70
#define CIRCLE_BUTTON_Y_UP 85
#define CIRCLE_BUTTON_Y_DOWN 120
#define RECTANGLE_BUTTON_X_LEFT 35
#define RECTANGLE_BUTTON_X_RIGHT 70
#define RECTANGLE_BUTTON_Y_UP 120 
#define RECTANGLE_BUTTON_Y_DOWN 155
#define ARC_RECTANGLE_BUTTON_X_LEFT 35
#define ARC_RECTANGLE_BUTTON_X_RIGHT 70
#define ARC_RECTANGLE_BUTTON_Y_UP 155
#define ARC_RECTANGLE_BUTTON_Y_DOWN 185
#define FREE_SHAPE_BUTTON_X_LEFT 35
#define FREE_SHAPE_BUTTON_X_RIGHT 70
#define FREE_SHAPE_BUTTON_Y_UP 185
#define FREE_SHAPE_BUTTON_Y_DOWN 215
#define PENTAGON_BUTTON_X_LEFT 35
#define PENTAGON_BUTTON_X_RIGHT 70
#define PENTAGON_BUTTON_Y_UP 215
#define PENTAGON_BUTTON_Y_DOWN 250
#define FORE_STAR_BUTTON_X_LEFT 35
#define FORE_STAR_BUTTON_X_RIGHT 70
#define FORE_STAR_BUTTON_Y_UP 250
#define FORE_STAR_BUTTON_Y_DOWN 285
#define SIX_STAR_BUTTON_X_LEFT 35
#define SIX_STAR_BUTTON_X_RIGHT 70
#define SIX_STAR_BUTTON_Y_UP 285
#define SIX_STAR_BUTTON_Y_DOWN 315
#define LEFT_ARROW_BUTTON_X_LEFT 35
#define LEFT_ARROW_BUTTON_X_RIGHT 70
#define LEFT_ARROW_BUTTON_Y_UP 315
#define LEFT_ARROW_BUTTON_Y_DOWN 350
#define DOWN_ARROW_BUTTON_X_LEFT 35
#define DOWN_ARROW_BUTTON_X_RIGHT 70
#define DOWN_ARROW_BUTTON_Y_UP 350
#define DOWN_ARROW_BUTTON_Y_DOWN 385
#define CIRCLE_DIALOG_BUTTON_X_LEFT 35
#define CIRCLE_DIALOG_BUTTON_X_RIGHT 70
#define CIRCLE_DIALOG_BUTTON_Y_UP 385
#define CIRCLE_DIALOG_BTTON_Y_DOWN 410
#define CANCLE_BUTTON_X_LEFT 0
#define CANCLE_BUTTON_X_RIGHT 35
#define CANCLE_BUTTON_Y_UP 385
#define CANCLE_BTTON_Y_DOWN 410
#define M_CANCLE 19
#endif // !BUTTON_H