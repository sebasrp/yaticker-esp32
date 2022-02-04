#include <SPI.h>
#include <WiFi.h>

#include <lilygo.h>
#include <utils.h>
#include <config.h>
#include "firasans.h" // font

LilyGo::LilyGo()
{
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
    font = FiraSans;
}

void LilyGo::initialize()
{
    initialize_screen();
    wifi_start();
}

void LilyGo::initialize_screen()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println(String(__FILE__) + "\nStarting...");
    epd_init();

    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer)
    {
        Serial.println("Memory alloc failed!");
        while (1)
            ;
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_poweron(); // Switch on EPD display
    epd_clear();   // Clear the screen
}

uint8_t LilyGo::wifi_start()
{
    Serial.println("\r\nConnecting to: " + String(ssid));
    WiFi.disconnect();
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("STA: Failed!\n");
        WiFi.disconnect(false);
        delay(500);
        WiFi.begin(ssid, password);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected at: " + WiFi.SSID() + " with IP: " + WiFi.localIP().toString());
    }
    else
        Serial.println("WiFi connection *** FAILED ***");
    return WiFi.status();
}

void LilyGo::wifi_stop()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi switched Off");
}

void LilyGo::display_message(String message)
{
    draw_text(framebuffer, message, 0, 0, LEFT);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); // Update the screen
    epd_poweroff_all();                                       // Switch off all power to EPD
}