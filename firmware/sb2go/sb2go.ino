#define IS_SIM

#include "words.h"
#include <Adafruit_NeoPixel.h>
#ifdef IS_SIM
    #include <Adafruit_GFX.h>
    #include "Adafruit_ILI9341.h"
#else
    #include <Arduino_GFX_Library.h>
#endif

// hardware mappings
// ----------------------------------
// neopixels       <--   2
// button numbers  <--   button pins
//  7 6                   11 19
// 5 4 1           <--   20 15 3
//  3 2                   16 4
// screen sda      <--   5
// screen scl      <--   6
// screen rst      <--   7
// screen dc       <--   8

// sim mappings
// ----------------------------------
// neopixels       <--   2
// button numbers  <--   button pins
//  7 6                   11 19
// 5 4 1           <--   20 15 3
//  3 2                   16 4
// screen sda      <--   5
// screen scl      <--   6
// screen rst      <--   7
// screen dc       <--   8

#define NUM_NEOPIXELS 8
#define NUM_BTNS 7
#ifdef IS_SIM
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 64

    #define PIN_NEOPIXELS D9
    #define PIN_BTN_1 D2
    #define PIN_BTN_2 D3
    #define PIN_BTN_3 D6
    #define PIN_BTN_4 D4
    #define PIN_BTN_5 D5
    #define PIN_BTN_6 D1
    #define PIN_BTN_7 D0
    #define PIN_LCD_DC D7

    Adafruit_ILI9341 screen = Adafruit_ILI9341(-1, D7);
#else
    #define SCREEN_WIDTH 320
    #define SCREEN_HEIGHT 240

    #define PIN_NEOPIXELS 2
    #define PIN_BTN_1 3
    #define PIN_BTN_2 4
    #define PIN_BTN_3 16
    #define PIN_BTN_4 15
    #define PIN_BTN_5 20
    #define PIN_BTN_6 19
    #define PIN_BTN_7 11
    #define PIN_LCD_SDA 5
    #define PIN_LCD_SCL 6
    #define PIN_LCD_RST 7
    #define PIN_LCD_DC 8

    Arduino_DataBus *bus = new Arduino_HWSPI(PIN_LCD_DC /* DC */, GFX_NOT_DEFINED /* CS */);
    Arduino_GFX *gfx = new Arduino_ST7789(bus, PIN_LCD_RST /* RST */, 0 /* rotation */);
#endif

Adafruit_NeoPixel NeoPixel(NUM_NEOPIXELS, PIN_NEOPIXELS, NEO_GRB + NEO_KHZ800);
const u_int8_t BTN_PINS[7] = { 
    PIN_BTN_1, PIN_BTN_2, PIN_BTN_3, 
    PIN_BTN_4, PIN_BTN_5, PIN_BTN_6, 
    PIN_BTN_7 
};
bool btnLast[7] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW };

void handleBtnPress(int btnId) {

}

void setup() {
    #ifdef IS_SIM
        screen.begin();

        screen.setCursor(10, 10);
        screen.setTextColor(ILI9341_RED);
        screen.setTextSize(3);
        screen.println("Hello, screen!");
    #else
        gfx->begin();

        gfx->fillScreen(RGB565_BLACK);
        gfx->setCursor(10, 10);
        gfx->setTextColor(RGB565_RED);
        gfx->println("Hello, screen!");
    #endif

    NeoPixel.begin();

    // test neopixels by turning green
    NeoPixel.clear();
    for (int pixel = 0; pixel < 8; pixel++) {           
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));  
        NeoPixel.show();                                           
    }

    for (u_int8_t i = 0; i < NUM_BTNS; i++) {
        pinMode(BTN_PINS[i], INPUT_PULLUP);
    }
}

void loop() {
    for (u_int8_t i = 0; i < NUM_BTNS; i++) {
        bool btnStatus = digitalRead(BTN_PINS[i]);
        if (btnStatus == HIGH && btnLast[i] == LOW) {
            handleBtnPress(i);
        }
        btnLast[i] = btnStatus;
    }
}