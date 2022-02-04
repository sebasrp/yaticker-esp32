#include <Arduino.h> // In-built

#include <lilygo.h>

#define SCREEN_WIDTH EPD_WIDTH
#define SCREEN_HEIGHT EPD_HEIGHT

// program constant and variables
uint8_t *framebuffer;
LilyGo screen;

void setup()
{
  screen = LilyGo();
  screen.initialize();
  screen.display_message("Hellow World");
}

void loop()
{
  // nothing here
}