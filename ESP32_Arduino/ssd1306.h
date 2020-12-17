#include <Arduino.h>
#include <stdio.h>
#include <stdarg.h>

#define SSD1306_ADDRESS 0x3C
#define WIDTH 128
#define HEIGHT 64

extern const uint8_t font_bitmat[][6];
extern i2c_t *__HI2C__;

static const uint8_t ctrlbyte_mono = 0b10000000;
static const uint8_t ctrlbyte_multi = 0;
static const uint8_t databyte_mono = 0b11000000;
static const uint8_t databyte_multi = 0b01000000;

void oled_init(i2c_t *handler);
void oled_printf(const char *format,...);
void oled_clear(void);
void oled_move(uint8_t x,uint8_t y);
void oled_usingarea(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1);