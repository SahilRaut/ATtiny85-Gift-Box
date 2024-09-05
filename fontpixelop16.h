/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* font */
const uint8_t Tiny4kOLED_pixelop16 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x17, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x40, 0xf0, 
	0x40, 0x40, 0xf0, 0x40, 0x04, 0x1f, 0x04, 0x04, 0x1f, 0x04, 0xe0, 0x10, 0xfc, 0x10, 0x20, 0x08, 
	0x11, 0x7f, 0x11, 0x0e, 0x60, 0x90, 0x60, 0x00, 0x80, 0x40, 0x00, 0x00, 0x04, 0x02, 0x01, 0x0c, 
	0x12, 0x0c, 0xe0, 0x10, 0x10, 0x10, 0x20, 0x0e, 0x11, 0x11, 0x11, 0x1e, 0x70, 0x00, 0xc0, 0x20, 
	0x10, 0x07, 0x08, 0x10, 0x10, 0x20, 0xc0, 0x10, 0x08, 0x07, 0xa0, 0x40, 0xf0, 0x40, 0xa0, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0x01, 0x07, 0x01, 0x01, 0x00, 0x00, 
	0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x10, 0x00, 0x80, 0x70, 0x1c, 
	0x03, 0x00, 0xe0, 0x10, 0x10, 0x90, 0xe0, 0x0f, 0x12, 0x11, 0x10, 0x0f, 0x40, 0x20, 0xf0, 0x00, 
	0x00, 0x1f, 0x20, 0x10, 0x10, 0x90, 0x60, 0x1c, 0x12, 0x11, 0x10, 0x10, 0x20, 0x10, 0x10, 0x10, 
	0xe0, 0x08, 0x10, 0x11, 0x11, 0x0e, 0x00, 0x80, 0x40, 0x20, 0xf0, 0x03, 0x02, 0x02, 0x02, 0x1f, 
	0xf0, 0x90, 0x90, 0x90, 0x10, 0x08, 0x10, 0x10, 0x10, 0x0f, 0xe0, 0x10, 0x10, 0x10, 0x20, 0x0f, 
	0x11, 0x11, 0x11, 0x0e, 0x10, 0x10, 0x10, 0x90, 0x70, 0x1c, 0x02, 0x01, 0x00, 0x00, 0xe0, 0x10, 
	0x10, 0x10, 0xe0, 0x0e, 0x11, 0x11, 0x11, 0x0e, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x08, 0x11, 0x11, 
	0x11, 0x0f, 0x40, 0x10, 0x00, 0x40, 0x40, 0x30, 0x00, 0x80, 0x40, 0x01, 0x02, 0x04, 0x80, 0x80, 
	0x80, 0x80, 0x02, 0x02, 0x02, 0x02, 0x40, 0x80, 0x00, 0x04, 0x02, 0x01, 0x20, 0x10, 0x10, 0x90, 
	0x60, 0x00, 0x00, 0x17, 0x00, 0x00, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x10, 0xe0, 0x0f, 0x10, 0x13, 
	0x14, 0x17, 0x14, 0x03, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x1f, 0x02, 0x02, 0x02, 0x1f, 0xf0, 0x10, 
	0x10, 0x10, 0xe0, 0x1f, 0x11, 0x11, 0x11, 0x0e, 0xe0, 0x10, 0x10, 0x10, 0x20, 0x0f, 0x10, 0x10, 
	0x10, 0x08, 0xf0, 0x10, 0x10, 0x10, 0xe0, 0x1f, 0x10, 0x10, 0x10, 0x0f, 0xf0, 0x10, 0x10, 0x10, 
	0x10, 0x1f, 0x11, 0x11, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x01, 0x01, 0x00, 0x00, 
	0xe0, 0x10, 0x10, 0x10, 0x20, 0x0f, 0x10, 0x10, 0x11, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x1f, 
	0x01, 0x01, 0x01, 0x1f, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x08, 0x10, 0x10, 0x10, 0x0f, 
	0xf0, 0x00, 0x80, 0x40, 0x30, 0x1f, 0x01, 0x02, 0x04, 0x18, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0x10, 0x10, 0x10, 0x10, 0xf0, 0x40, 0x80, 0x00, 0x80, 0x40, 0xf0, 0x1f, 0x00, 0x00, 0x01, 0x00, 
	0x00, 0x1f, 0xf0, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x01, 0x02, 0x1f, 0xe0, 0x10, 0x10, 0x10, 
	0xe0, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0xf0, 0x10, 0x10, 0x10, 0xe0, 0x1f, 0x01, 0x01, 0x01, 0x00, 
	0xe0, 0x10, 0x10, 0x10, 0xe0, 0x0f, 0x10, 0x14, 0x08, 0x17, 0xf0, 0x10, 0x10, 0x10, 0xe0, 0x1f, 
	0x01, 0x03, 0x05, 0x18, 0xe0, 0x10, 0x10, 0x10, 0x20, 0x08, 0x11, 0x11, 0x11, 0x0e, 0x10, 0x10, 
	0xf0, 0x10, 0x10, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x10, 0x10, 
	0x10, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x07, 0x08, 0x10, 0x08, 0x07, 0xf0, 0x00, 0x00, 0xc0, 
	0x00, 0x00, 0xf0, 0x0f, 0x10, 0x10, 0x0f, 0x10, 0x10, 0x0f, 0x70, 0x80, 0x00, 0x80, 0x70, 0x1c, 
	0x02, 0x01, 0x02, 0x1c, 0x70, 0x80, 0x00, 0x80, 0x70, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x10, 0x10, 
	0x10, 0x90, 0x70, 0x1c, 0x12, 0x11, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x70, 0x80, 
	0x00, 0x00, 0x03, 0x1c, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x1f, 0x40, 0x20, 0x10, 0x20, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x10, 0x20, 
	0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x0c, 0x12, 0x12, 0x12, 0x1f, 0xf0, 0x40, 0x40, 0x40, 
	0x80, 0x1f, 0x10, 0x10, 0x10, 0x0f, 0x80, 0x40, 0x40, 0x40, 0x80, 0x0f, 0x10, 0x10, 0x10, 0x08, 
	0x80, 0x40, 0x40, 0x40, 0xf0, 0x0f, 0x10, 0x10, 0x10, 0x1f, 0x80, 0x40, 0x40, 0x40, 0x80, 0x0f, 
	0x12, 0x12, 0x12, 0x0b, 0x80, 0xe0, 0x90, 0x90, 0x00, 0x1f, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 
	0xc0, 0x27, 0x48, 0x48, 0x48, 0x3f, 0xf0, 0x40, 0x40, 0x40, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x1f, 
	0xd0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x20, 0x40, 0x40, 0x40, 0x3f, 0xf0, 0x00, 0x00, 0x80, 
	0x40, 0x1f, 0x02, 0x05, 0x08, 0x10, 0xf0, 0x00, 0x0f, 0x10, 0xc0, 0x40, 0x40, 0x80, 0x40, 0x40, 
	0x80, 0x1f, 0x00, 0x00, 0x07, 0x00, 0x00, 0x1f, 0xc0, 0x40, 0x40, 0x40, 0x80, 0x1f, 0x00, 0x00, 
	0x00, 0x1f, 0x80, 0x40, 0x40, 0x40, 0x80, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0xc0, 0x40, 0x40, 0x40, 
	0x80, 0x7f, 0x10, 0x10, 0x10, 0x0f, 0x80, 0x40, 0x40, 0x40, 0xc0, 0x0f, 0x10, 0x10, 0x10, 0x7f, 
	0xc0, 0x00, 0x80, 0x40, 0x40, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x09, 
	0x12, 0x12, 0x12, 0x0c, 0x40, 0xe0, 0x40, 0x40, 0x00, 0x0f, 0x10, 0x10, 0xc0, 0x00, 0x00, 0x00, 
	0xc0, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x07, 0x08, 0x10, 0x08, 0x07, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x10, 0x10, 0x0f, 0x10, 0x10, 0x0f, 0xc0, 0x00, 
	0x00, 0x00, 0xc0, 0x18, 0x05, 0x02, 0x05, 0x18, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x27, 0x48, 0x48, 
	0x48, 0x3f, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x18, 0x14, 0x12, 0x11, 0x10, 0x00, 0xe0, 0x10, 0x10, 
	0x01, 0x0e, 0x10, 0x10, 0xf0, 0x1f, 0x10, 0x10, 0xe0, 0x00, 0x10, 0x10, 0x0e, 0x01, 0x20, 0x10, 
	0x10, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


};

const uint8_t Tiny4kOLED_pixelop16_widths [] PROGMEM = {
3, 1, 3, 6, 5, 7, 5, 1, 3, 3, 5, 5, 2, 4, 1, 3,  
5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 3, 4, 3, 5,  
7, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 5, 5, 7, 5, 5,  
5, 5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 3, 3, 3, 5, 5,  
2, 5, 5, 5, 5, 5, 4, 5, 5, 1, 5, 5, 2, 7, 5, 5,  
5, 5, 5, 5, 4, 5, 5, 7, 5, 5, 5, 4, 1, 4, 6
};

const uint16_t Tiny4kOLED_pixelop16_widths_16s [] PROGMEM = {
3+ 1+ 3+ 6+ 5+ 7+ 5+ 1+ 3+ 3+ 5+ 5+ 2+ 4+ 1+ 3, 
5+ 3+ 5+ 5+ 5+ 5+ 5+ 5+ 5+ 5+ 1+ 2+ 3+ 4+ 3+ 5, 
7+ 5+ 5+ 5+ 5+ 5+ 5+ 5+ 5+ 1+ 5+ 5+ 5+ 7+ 5+ 5, 
5+ 5+ 5+ 5+ 5+ 5+ 5+ 7+ 5+ 5+ 5+ 3+ 3+ 3+ 5+ 5, 
2+ 5+ 5+ 5+ 5+ 5+ 4+ 5+ 5+ 1+ 5+ 5+ 2+ 7+ 5+ 5, 
5+ 5+ 5+ 5+ 4+ 5+ 5+ 7+ 5+ 5+ 5+ 4+ 1+ 4+ 6
};

const DCfont Tiny4kOLEDpixelop16 = {
  (uint8_t *)Tiny4kOLED_pixelop16,
  0, // character width in pixels
  2, // character height in pages (16 pixels)
  32,126, // ASCII extents
 // 0x20,0x30, // ASCII extents
  (uint16_t *)Tiny4kOLED_pixelop16_widths_16s,
  (uint8_t *)Tiny4kOLED_pixelop16_widths,
  1 // spacing
};

// for backwards compatibility
#define FONTPIXELOP16 (&Tiny4kOLEDpixelop16)