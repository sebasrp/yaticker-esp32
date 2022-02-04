#ifndef LILYGO_H
#define LILYGO_H
#include <Arduino.h>
#include "epd_driver.h"

class LilyGo
{
private:
    int width;
    int height;
    GFXfont font;
    uint8_t *framebuffer;
    void initialize_screen();
    uint8_t wifi_start();
    void wifi_stop();

public:
    LilyGo();
    void initialize();
    void display_message(String message);
};

#endif