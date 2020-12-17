#include "ssd1306.hpp"

i2c_t *__SSD1306_HI2C__;

const uint8_t font_bitmat[][6] = 
{//0x00~0x1Fはutf8では未使用なので省略 (文字-32)の配列を呼び出す
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // sp
    {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00}, // !
    {0x00, 0x00, 0x07, 0x00, 0x07, 0x00}, // "
    {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
    {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
    {0x00, 0x23, 0x13, 0x08, 0x64, 0x62}, // %
    {0x00, 0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00}, // (
    {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00}, // )
    {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00}, // ,
    {0x00, 0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x00, 0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x00, 0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x00, 0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x00, 0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x00, 0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x00, 0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x00, 0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E}, // @
    {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C}, // A
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x00, 0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
    {0x00, 0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x00, 0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x00, 0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00}, // [
    {0x00, 0x02, 0x04, 0x08, 0x10, 0x20}, // back_slash
    {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
    {0x00, 0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x00, 0x40, 0x40, 0x40, 0x40, 0x40}, // _
    {0x00, 0x00, 0x01, 0x02, 0x04, 0x00}, // '
    {0x00, 0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38}, // b
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F}, // d
    {0x00, 0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02}, // f
    {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C}, // g
    {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00}, // j
    {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78}, // m
    {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18}, // p
    {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC}, // q
    {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08}, // r
    {0x00, 0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20}, // t
    {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // y
    {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x00, 0x08, 0x77, 0x00, 0x00}, // {
    {0x00, 0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x00, 0x00, 0x77, 0x08, 0x00, 0x00}, // }
    {0x00, 0x10, 0x08, 0x10, 0x08, 0x00}, // ~
    {0x14, 0x14, 0x14, 0x14, 0x14, 0x14} // horiz lines-> DEL
};

void oled_init(i2c_t *handler)
{
    __SSD1306_HI2C__ = handler;
    uint8_t cmd_on[] = {ctrlbyte_mono,0xAF};
    uint8_t cmd_contrast[] = {ctrlbyte_multi,0x81,0xFF};
    uint8_t cmd_clk[] = {ctrlbyte_multi,0x81,0x80};
    uint8_t cmd_pump[] = {ctrlbyte_multi,0x8D,0x14};
    uint8_t cmd_adressing[] = {ctrlbyte_multi,0x20,0x00};
    uint8_t cmd_inv[] = {ctrlbyte_multi,0xA1,0xC8};

    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_contrast,3,true,0xFF);
    delay(1);
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_clk,3,true,0xFF);
    delay(1);
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_adressing,3,true,0xFF);
    delay(1);    
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_inv,5,true,0xFF);
    delay(1);
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_pump,3,true,0xFF);
    delay(1);
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_on,2,true,0xFF);
    delay(1);
}
void oled_printf(const char *format,...)
{
    char strbuf[43] = {0};
    uint8_t txbuf[257] = {databyte_multi};
    va_list val;
    va_start(val,format);
    vsnprintf(strbuf,42,format,val);
    va_end(val);

    uint8_t i = 1 ,j ,datalen = 1;
    char *pstr = strbuf;
    while(*pstr)
    {
        for(j = 0;j < 6;j++)
        {
            txbuf[i+j] = font_bitmat[(uint8_t)(*pstr)-32][j];
            datalen++;
        }
        i+=6;
        pstr++;
    }
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,txbuf,datalen,true,0xFF);
}
void oled_clear(void)
{
    uint8_t cmd_clm[] = {ctrlbyte_mono,0x00};
    uint8_t cmd_setpos[] = {ctrlbyte_multi,0xB0,0x00,0x10,0xD3,0x00};
    uint8_t data_sp[129] = {databyte_multi};
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_clm,2,true,0xFF);
    delay(1);
    for(uint8_t i = 0;i < 8;i++)
    {
        i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,data_sp,129,true,0xFF);
    }
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_setpos,5,true,0xFF);
}
void oled_origin(void)
{
    uint8_t cmd_reset[] = {ctrlbyte_multi,0x00,0xB0};
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_reset,3,true,0xFF);
}
void oled_move(uint8_t x, uint8_t y)
{
    uint8_t cmd_area[] = {ctrlbyte_multi,(uint8_t)(0x00|x>>4),(uint8_t)(0x10|(x&0b00001111)),0xD3,(uint8_t)(0x00|(0b00111111&(-y*8)))};
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_area,5,true,0xFF);
}
void oled_usingarea(uint8_t x0, uint8_t y0, uint8_t x1,uint8_t y1)
{
    uint8_t cmd_area[] = {ctrlbyte_multi,0x21,x0,x1,0x22,y0,y1};
    i2cWrite(__SSD1306_HI2C__,SSD1306_ADDRESS,cmd_area,7,true,0xFF);
}