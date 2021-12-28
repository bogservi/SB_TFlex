#include <windows.h>
#include <iostream>
#include "Figures.cpp"
#include <cmath>

using namespace std;
//Холст, отвечающий за отрисовку
class Canvas : public  Figure
{
private:
    const char* BORDER = "=";
    const char* POINT = "*";
    const char* EMPT = " ";
    COORD _startCanva;
    HANDLE _gout;
    DWORD dw = 0u;

public:
    Canvas() {};
    ~Canvas() {};

    Canvas(HANDLE &gout )
    {
        _gout = gout;
    }
    
    //Очистка холста
    void Clear() 
    {
        char tc;
        for (short y = _startCanva.Y; y <= _startCanva.Y+ MAX_HEIGHT; y++)
        {
            WriteConsoleOutputCharacterA(_gout, BORDER, strlen(BORDER), { _startCanva.X, y }, &dw);
            if (y == _startCanva.Y || y == _startCanva.Y + MAX_HEIGHT)
            {
                tc = BORDER[0];
            }
            else
            {
                tc = EMPT[0];
            }
            WriteConsoleOutputCharacterA(_gout, string(MAX_WIDTH - 1, tc).c_str(), MAX_WIDTH - 1, { _startCanva.X + (short)1, y }, &dw);
            WriteConsoleOutputCharacterA(_gout, BORDER, strlen(BORDER), { _startCanva.X + MAX_WIDTH, y }, &dw);
        }
    }
    
    void SetStartPoint(COORD startPoint) override
    {
        _startCanva = startPoint;
    };

    //Отрисовка фигур
    void PrintFigure(Figure &item)
    {
        //принудительная очистка+отрисовка границы
        Clear();

        //проход для заполнения холста
        for (short y = _startCanva.Y+1; y < _startCanva.Y + MAX_HEIGHT; y++)
        {
            for (short x = _startCanva.X+1; x < _startCanva.X + MAX_WIDTH; x++)
            {
                if (item.CheckPoint(x,y))
                {
                    WriteConsoleOutputCharacterA(_gout, POINT, strlen(POINT), { x, y }, &dw);
                }
                else
                {
                    WriteConsoleOutputCharacterA(_gout, EMPT, strlen(EMPT), { x, y }, &dw);
                }
            }
        }
    }
};


//прямоугольник
 class Rectan : public Figure
{
public:
    Rectan(COORD startPoint, short widht, short height)
    {
        SetDefaultParam(startPoint, widht, height);
    };

     bool CheckPoint(short& x, short& y)
    {
        return 
            x>= _startPoint.X && x<= _startPoint.X + _widht &&
            y>= _startPoint.Y && y <= _startPoint.Y+ _height;
    }


};

 //эллипс
 class Disc : public Figure
 {
 public:
     Disc(COORD startPoint, short radius)
     {
         SetStartPoint(startPoint);
         _radius = radius;
     };

     bool CheckPoint(short& x, short& y)
     {
         return
             pow(x - _startPoint.X, 2) + pow(y - _startPoint.Y, 2) <= pow(_radius, 2);
     }


 private:
     short _radius;
 };

 //Прямоугольный треугольник
 class Triangl : public Figure
 {
 public:
     Triangl(COORD startPoint, short widht, short height)
     {
         SetDefaultParam(startPoint, widht, height);
     };

     bool CheckPoint(short& x, short& y)
     {
         return

             /* / */round((x - _startPoint.X) / (0.5 * _widht)) -
             round((y - _startPoint.Y) / (-_height)) >= 0
             &&
             /* _ */ x <= _startPoint.X+_widht+1
             &&
             /* _ */ y <= _startPoint.Y
             ;
     }

 };




