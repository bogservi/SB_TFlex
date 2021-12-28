#include <windows.h>
class Figure {

public:
    virtual ~Figure() {}
    virtual void SetStartPoint(COORD startPoint) 
    {
        _startPoint = startPoint;
    };
    virtual bool CheckPoint(short& x, short& y)
    {
        return false;
    };
    
    virtual void SetDefaultParam(COORD startPoint, short widht, short height)
    {
        SetStartPoint(startPoint);
        _widht = widht;
        _height = height;
    };

protected:
    const short MAX_WIDTH = 40;
    const short MAX_HEIGHT = 20;
    COORD _startPoint;
    short _widht;
    short _height;
};


