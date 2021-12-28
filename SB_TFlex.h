// SB_TFlex.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include "Canvas.cpp"
//#include "Figures.cpp"

#define  FOCUS_COLOR  10u   // цвет текста при фокусе комманды меню
#define  STATE_COLOR  14u   // цвет не выделенных комманд меню
#define  MENU_POS_X   14    // начальная позиция меню по-X
#define  MENU_POS_Y   2     // начальная позиция меню по-Y

CONSOLE_SCREEN_BUFFER_INFO    ginfo;
HANDLE   gout;
Canvas canva;
DWORD dw;