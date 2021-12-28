// SB_TFlex.cpp: определяет точку входа для приложения.
//

#include "SB_TFlex.h"


using namespace std;

char* conv_cp(const char* str, char* buf);
void  additem(const char* str, WORD color, short &top);
void  set_cursor(char ch, WORD color, WORD focus, short cursor);
void  run_command(short cursor, Canvas &canva);
void  navigate(short& cursor, short size, short num);


int main()
{

	 char buf[255];
     CONSOLE_CURSOR_INFO  icur;
     short  posY   = MENU_POS_Y;
     short  cursor = MENU_POS_Y;
 
     gout = GetStdHandle(STD_OUTPUT_HANDLE);
 
     ZeroMemory(&ginfo, sizeof(CONSOLE_SCREEN_BUFFER_INFO));
     GetConsoleScreenBufferInfo(gout, &ginfo);
 
     icur.bVisible = FALSE;
     icur.dwSize   = 1u;
     SetConsoleCursorInfo(gout, &icur);  // убрать курсор из консоля
     
     // строим список комманд меню
     additem(conv_cp("Эллипс", buf), STATE_COLOR, posY);
     additem(conv_cp("Треугольник", buf), STATE_COLOR, posY);
     additem(conv_cp("Прямоугольник", buf), STATE_COLOR, posY);
     additem(conv_cp("Очистить", buf), STATE_COLOR, posY);
     additem(conv_cp("Закрыть консоль", buf), STATE_COLOR, posY);
 
     conv_cp("Навигация по меню клавиши вверх и вниз, enter.", buf);
     WriteConsoleA(gout, buf, strlen(buf), &icur.dwSize, NULL);
 
     set_cursor('>', 12u, FOCUS_COLOR, cursor);


     Canvas canva = Canvas(gout);
     canva.SetStartPoint({ 40u, 7u });
     
     while (1) {
         if (GetAsyncKeyState(VK_DOWN))   // переместиться вниз
             navigate(cursor, posY, 1);

         if (GetAsyncKeyState(VK_UP))  // переместиться вверх
             navigate(cursor, posY, -1);
         if (GetAsyncKeyState(VK_RETURN))  // на клавишу Enter исполняются комманды
             run_command(cursor, canva);
     }

     return 0;
}



// конвертирование в родную консольную кодировку OEM
char* conv_cp(const char* str, char* buf) {
    CharToOemA(str, buf);
    return buf;
};

// добавить комманду в меню
void  additem(const char* str, WORD color, short &top) {
    
    COORD pos = { MENU_POS_X, top };

    WriteConsoleOutputCharacterA(gout, str, strlen(str), pos, &dw);
    for (; *str; *str++, pos.X++)
        WriteConsoleOutputAttribute(gout, &color, 1, pos, &dw);
    top++;
}

// ролловеры - эфекты 
void  set_cursor(char ch, WORD color, WORD focus, short cursor) {
   
    COORD pos = { MENU_POS_X - 1, cursor };
    FillConsoleOutputCharacterA(gout, ch, 1u, pos, &dw);
    FillConsoleOutputAttribute(gout, color, 1u, pos, &dw);
    pos.X++;
    FillConsoleOutputAttribute(gout, focus, 64u, pos, &dw);
}

// список комманд - меню
void  run_command(short cursor, Canvas &canva) {
    
    
    
    switch (cursor - MENU_POS_Y) {
    case 0:
    {
        Disc di = Disc({ (short)(60u + rand() % 10), (short)(15u + rand() % 3) },
            (rand() % 6) + 5 // радиус от 5-10
            ); 

        canva.PrintFigure(di);
    }
    break;
    case 1:
    {
        Triangl tr = Triangl({ (short)(42u + rand() % 3), (short)(22u + rand() % 3) },
            (rand() % 3) + 16 // ширина от 1-30
            , (rand() % 3) + 2); // высота от 1-15

        canva.PrintFigure(tr);
    }
        break;
    case 2:
    {
        Rectan rec = Rectan({ (short)(42u + rand() % 10), (short)(8u + rand() % 3) },
            (rand() % 30) + 1 // ширина от 1-30
            , (rand() % 10) + 1); // высота от 1-10

        canva.PrintFigure(rec);
    }
        break;
    case 3:
        canva.Clear();
        return;
    case 4:
        TerminateProcess(GetCurrentProcess(), 0u);
        break;

        
    }
    Sleep(400u);
}

// навигация по списку меню
void  navigate(short& cursor, short size, short num) {
    if (cursor <= MENU_POS_Y && num < 0 || cursor >= size - 1 && num > 0)
        return;
    set_cursor(' ', 12u, STATE_COLOR, cursor);
    cursor += num;
    set_cursor('>', 12u, FOCUS_COLOR, cursor);
    Sleep(400u);
}