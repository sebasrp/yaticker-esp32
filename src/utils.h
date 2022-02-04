#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>    // In-built
#include "epd_driver.h" // In-built

#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson#include <string>
#include "firasans.h"    // font

enum alignment
{
    LEFT,
    RIGHT,
    CENTER
};

void draw_text(uint8_t *framebuffer, String text, int x_offset, int y_offset, alignment align = LEFT, GFXfont font = FiraSans)
{
    char *data = const_cast<char *>(text.c_str());
    int x1, y1; //the bounds of x,y and w and h of the variable 'text' in pixels.
    int w, h;
    int xx = x_offset, yy = y_offset;
    get_text_bounds(&font, data, &xx, &yy, &x1, &y1, &w, &h, NULL);
    if (align == RIGHT)
        x_offset = EPD_WIDTH - w;
    if (align == CENTER)
        x_offset = (EPD_WIDTH - w) / 2;
    int cursor_y = y_offset + h;
    Serial.println(String(__FILE__) + "\n Drawing string: " + text + ". x: " + x_offset + " y: " + cursor_y);
    write_string(&font, data, &x_offset, &cursor_y, framebuffer);
}

#endif