#include <math.h>
#include <SPI.h>
#include "src/arduinogl/ArduinoGL.h"
// #include "src/GU800/GU800_GFX.h"
#include "src/GU800/GU800_Canvas.h"
// #include "pikachu.h"

#define css 10
// #define css 53
#define cd 9
#define reset 8

GU800_Canvas display(css, cd, reset);

uint8_t state = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(css, OUTPUT);
  digitalWrite(css, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(5);
  digitalWrite(LED_BUILTIN, HIGH);

//  SPI.setSCK(14);
  delay(2500);
  display.begin();
  display.clearDisplay();

  // setup text
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
//  display.println("Fuck You!");

  printInit();

  display.display();
}

void initGL() {
  /* Pass the canvas to the OpenGL environment */
  glUseCanvas(&display);
  
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(4);
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // square
  // gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
  
  // cube
  gluPerspective(30.0, display.width()/display.height(), 0.1f, 9999.f);
    
  glMatrixMode(GL_MODELVIEW);
}

void printInit() {
  display.setCursor(26, 18);
  display.println("INITIALIZING");
  display.setCursor(38, 26);
  display.println("ARDUINOGL");
  display.setCursor(44, 34);
  display.print("ENGINE");
}

float _angle = 0.0f;

// static float scale = 3.0, scaleInc = 0.4;
// const float maxScale = 8.0, minScale = 2.0;

void prep3dShapeDraw(float angle, float scale) {
  glClear(GL_COLOR_BUFFER_BIT); 

  glLoadIdentity();
  gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
    
  glRotatef(angle, 0.f, 1.f, 0.f);
  glScalef(scale, scale, scale);
}

void runSquare(float angle, float scale) {
 // square 
  glLoadIdentity();
  glRotatef(angle, 0.f, 0.f, 1.f);
  glScalef(scale, scale, 0.f);
  glTranslatef(-0.5f, -0.5f, 0.f);

  // square
  glBegin(GL_POLYGON);
    glVertex3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);
    glVertex3f(1.f, 1.f, 0.f);
  glEnd();
}

void drawCube() {  
  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
  glEnd();
}

void drawPyramid() {
  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(0, 1, 0);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
  glEnd();
  
  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
  glEnd();
}

void runGL() {
  _angle += 5.0f;
  _angle = fmod(_angle, 360.0f);
  const float _scale = 2.5f;

  runSquare(_angle, _scale);
  //prep3dShapeDraw(_angle, _scale);
  //drawCube();
//  drawPyramid();
  // runPikachu(_angle);

  /* Ask the display to print our frame buffer */
  display.display();
}

uint8_t dotCount = 0;
uint8_t loadCounts = 0;

void printLoading() {
  display.clearDisplay();
  printInit();
  for (uint8_t i = 0; i < dotCount; i++) {
    display.print(".");
  }
  display.display();
  delay(75);
  dotCount++;
  if (dotCount >= 4) {
    dotCount = 0;
    loadCounts++;
  }
}

void loop()
{
   if (state == 0) {
     Serial.print(loadCounts);
     Serial.println(" load");
     printLoading();
     if (loadCounts > 4) {
       state++;
       Serial.println("END STATE 0");
     }
   }

   if (state == 1) {
     display.clearDisplay();
     display.setCursor(24, 26);
     display.println("LOAD COMPLETE!");
     display.display();
     delay(250);
     Serial.println("END STATE 1");
     state++;
   }

   if (state == 2) {
     display.clearDisplay();
     display.display();
     state++;
     Serial.println("cleared, running GL!");
   }

   if (state == 3) {
     runSquare(1, 2);
   }
  
}
