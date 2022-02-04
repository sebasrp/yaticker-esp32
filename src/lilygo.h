#ifndef LILYGO_H
#define LILYGO_H
#include <Arduino.h>
#include <epd_driver.h>
#include <yfapi.h>

class LilyGo
{
private:
    int width;
    int height;
    GFXfont font;
    uint8_t *framebuffer;
    YahooFinanceAPI yfapi;
    void initialize_screen();
    uint8_t wifi_start();
    void wifi_stop();

public:
    LilyGo();
    void initialize();

    // Displays the stock data, the stock last price (at the desired coin/fiat)
    // 'ticker': symbol of the stock to display
    // 'period': time period to display
    // 'interval': granularity of the data
    void display_ticker(String ticker = "amzn", String period = "5d", String interval = "1h");
    void display_message(String message);
    void display_settings();
};

#endif