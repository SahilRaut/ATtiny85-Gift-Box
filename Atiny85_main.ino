#include <TinyWireM.h> // To use the Adafruit's TinyWireM library:
#include <Tiny4kOLED.h> // we are using the Tiny4kOLED library to draw on the display

#define BUTTON_DOWN_PIN PB3 // pin for DOWN button

#include "fontpixelop16.h" // font pixel operator regular
#include "bg.h" // 128x64px fullscreen background image


const unsigned char scrollbar_empty [] PROGMEM =  { B00000000, B01010101, B00000000  }; // image for scrollbar background 3x8px
const unsigned char scrollbar_filled [] PROGMEM = { B11111110, B11111111, B11111110  }; // image for scrollbar handle 3x8px

const int NUM_ITEMS = 10; // number of items in the list 
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name

char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // array with item names
  { "For all the" }, 
  { "help and guidance"}, 
  { "you provided me" }, 
  { "with, sometimes" }, 
  { "even in the most" }, 
  { "inconvenient" },   
  { "scenarios. I am" }, 
  { "sure this would" },
  { "contribute a lot" }, 
  { "towards my future!"}
};

int item_selected = 0; // which item in the menu is selected
int item_selected_displayed = -1; // currently displayed menu item on the OLED display, so we don´t need to redraw the screen all the time

void setup() {
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button, set to INPUT_PULLUP = when not pressed, pin is HIGH

  oled.begin(128, 64, sizeof(tiny4koled_init_128x64), tiny4koled_init_128x64); // display initialization
  oled.enableChargePump(); // The default is off, but most boards need this.
  oled.setRotation(1);     // The default orientation is not the most commonly used.
  oled.clear();  // clear the screen
  
  oled.bitmap(0, 0, 128, 8, epd_bitmap_bg_no_labels); // draw 128x64px background image
  
  oled.on(); // turn on the display
}

void clearTextArea() {
  for (int i = 1; i <= 6; i++) {
    oled.setCursor(0, i);
    oled.fillLength(0, 128); // clear each line of menu area
  }
}

void displayMenu() {
  clearTextArea(); // Clear the text area before drawing new text

  oled.setFont(FONTPIXELOP16); // regular font
  
  int top_index = item_selected;
  int middle_index = (item_selected + 1) % NUM_ITEMS;
  
  // Draw the menu items
  oled.setCursor(3, 2); // set cursor for the top item
  oled.print(menu_items[top_index]); // draw top menu item label
  
  oled.setCursor(3, 4); // set cursor for the middle item
  oled.print(menu_items[middle_index]); // draw middle menu item label

  // draw scrollbar
  for (byte i = 0; i < 8; i++) { // for all 8 pages
    if (i == item_selected % 8) {
      // draw scrollbar handle = scrollbar_filled
      oled.bitmap(125, i, 125 + 3, i + 1, scrollbar_filled);
    } else {
      // draw scrollbar background = scrollbar_empty
      oled.bitmap(125, i, 125 + 3, i + 1, scrollbar_empty);
    }
  }
}

void loop() { // main loop
  if (item_selected_displayed != item_selected) { // only redraw the screen if the selected item is different from the last time
    displayMenu();
    item_selected_displayed = item_selected; // update which item is currently rendered on the display
  }

  if (digitalRead(BUTTON_DOWN_PIN) == LOW) { // button DOWN is pressed
    item_selected = (item_selected + 1) % NUM_ITEMS; // switch to the next item
    delay(200); // debounce delay
  }
}
