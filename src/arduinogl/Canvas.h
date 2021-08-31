#ifndef Canvas_h
#define Canvas_h

class Canvas {
    
public:
    Canvas() {}
    virtual void clear();
    virtual void setPixel(int x, int y, bool on);
    
    virtual void drawLine(int startX, int startY, int endX, int endY);
    virtual void drawCircle(int centreX, int centreY, int radius);
    virtual void drawSquare(int startX, int startY, int endX, int endY);
    virtual void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

    virtual int width();
    virtual int height();
};

#endif

