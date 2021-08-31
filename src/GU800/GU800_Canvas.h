#include "GU800_GFX.h"
#include "../arduinogl/Canvas.h"

class GU800_Canvas : public GU800, public Canvas {
public:
  GU800_Canvas(int csPin, int dcPin, int resetPin) : GU800(csPin, dcPin, resetPin) {};

  void clear() override {
    clearDisplay();
  }

  void setPixel(int x, int y, bool on) override {
    drawPixel(x, y, on);
  }

  void drawLine(int startX, int startY, int endX, int endY) override {
    int diffX = (endX - startX);
    int diffY = (endY - startY);
      
    if (abs(diffX) > abs(diffY)) {
      float dy = diffY/(float)diffX;
      if(endX > startX) {
        for(int x = startX; x <= endX; x++) {
          this->setPixel(x, floor(startY + dy*(x - startX)), true);
        }
      } else {
        for(int x = startX; x >= endX; x--) {  
          this->setPixel(x, floor(startY + dy*(x - startX)), true);
        }
      }
    } else {
      float dx = diffX/(float)diffY;   
      if(endY > startY) {
        for(int y = startY; y <= endY; y++) {
          this->setPixel(floor(startX + dx*(y - startY)), y, true);
        }
      } else {
        for(int y = startY; y >= endY; y--) {
          this->setPixel(floor(startX + dx*(y - startY)), y, true);
        }
      }
    }
  }

  void drawCircle(int centreX, int centreY, int radius) override {
    radius = abs(radius);
    for(float angle = 0; angle < 2*M_PI; angle+=(M_PI/(4*radius))) {
      this->setPixel(centreX + cos(angle)*radius, centreY + sin(angle)*radius, true);
    }
  }

  void drawSquare(int startX, int startY, int endX, int endY) override {
    this->drawLine(startX, startY, startX, endY);
    this->drawLine(startX, endY, endX, endY);
    this->drawLine(endX, endY, endX, startY);
    this->drawLine(endX, startY, startX, startY);
  }

  void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) override {
    this->drawLine(x1, y1, x2, y2);
    this->drawLine(x2, y2, x3, y3);
    this->drawLine(x3, y3, x1, y1);
  }

  int width() override {
    return 128;
  }
  int height() override {
    return 64;
  }
};
