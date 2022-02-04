#include <Arduino.h>    // In-built
#include "epd_driver.h" // In-built

#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <HTTPClient.h>

#include <SPI.h>  // In-built
#include <time.h> // In-built
#include <vector>
#include <string>

#include "firasans.h" // font

#include <utils.h>
#include <config.h>

#define SCREEN_WIDTH EPD_WIDTH
#define SCREEN_HEIGHT EPD_HEIGHT

// program constant and variables
GFXfont currentFont;
uint8_t *framebuffer;

// should be moved to header file
void edp_update();

uint8_t wifi_start()
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

void wifi_stop()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  Serial.println("WiFi switched Off");
}

void initialize_screen()
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

void setup()
{
  initialize_screen();
  wifi_start();

  draw_text(framebuffer, "Hello World", 0, 0, CENTER);
  edp_update();
  epd_poweroff_all(); // Switch off all power to EPD
}

void loop()
{
  // nothing here
}

void edp_update()
{
  epd_draw_grayscale_image(epd_full_screen(), framebuffer); // Update the screen
}