// simple Pitch and Roll indicator project using DFRobot Serial 6-Axis Accelerometer and 2x ESP32-S3-LCD-1.28 from Waveshare

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/GosqWcScwC0
// SOURCE files: https://github.com/upiir/pitch_roll_indicator

// Links from the video:
// Do you like this video? You can buy me a coffee ☕: https://www.buymeacoffee.com/upir
// Display with enclosure: https://s.click.aliexpress.com/e/_DkQiwQf
// Display without enclosure: https://s.click.aliexpress.com/e/_DEe0YJv
// Display documentation: https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28
// DFRobot Serial 6-Axis Accelerometer: https://www.dfrobot.com/product-2200.html
// DFRobot Accelerometer Documentation: https://wiki.dfrobot.com/Serial_6_Axis_Accelerometer_SKU_SEN0386
// DFRobot_WT61PC Library: https://github.com/DFRobot/DFRobot_WT61PC
// Adapter board (1.27mm to 2.54mm Pitch): https://s.click.aliexpress.com/e/_Dc74hqb
// USB-C adapter: https://s.click.aliexpress.com/e/_DD2cHkT
// USB-C multiple cable: https://s.click.aliexpress.com/e/_DE8b0UP
// Screw Terminals: https://s.click.aliexpress.com/e/_DnB938b
// Image2cpp (convert array to image): https://javl.github.io/image2cpp/
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/
// ESP32 Partition calculator: https://esp32.jgarrettcorbin.com/
// KiCad: https://www.kicad.org/
// PCB online viewer: https://www.pcbway.com/project/OnlineGerberViewer.html
// Classic Ford Broncos: https://classicfordbroncos.com/truck/signature-series-coyote/

// Related videos:
// CHEAP DIY BOOST GAUGE: https://youtu.be/cZTx7T9uwA4	
// Boost pressure Arduino + OLED: https://youtu.be/JXmw1xOlBdk
// Pitch Roll Indicator: https://youtu.be/S_ppdbb0poQ
// Custom Shifter Knob with Display: https://www.youtube.com/playlist?list=PLjQRaMdk7pBb6r6xglZb92DGyWJTgBVaV


#include <TFT_eSPI.h>       // Include the graphics library
TFT_eSPI tft = TFT_eSPI();  // Create object "tft"

#include "roll_images.h" // 81 fullscreen (240x240) images are stored in this header file

void setup()
{
  
  Serial.begin(115200); // Use Serial as debugging serial port 
  Serial2.begin(115200, SERIAL_8N1, /*rx =*/16, /*tx =*/17); // Use Serial2 to connect it second display

  tft.init(); // initialize the display
  tft.setRotation(1); // set the display rotation
  tft.setRotation(4); // set the display rotation
  tft.fillScreen(TFT_DARKGREY); // fill the display with a dark grey color
  tft.setTextFont(4); // set the font, font number 4 is quite big
  tft.setSwapBytes(true); // Swap the colour byte order when rendering  

  // debug only - draw label "secondary"
  tft.setCursor(30, 60);
  tft.print("SECONDARY");
}


int roll_value_img = 0; // image to be displayed, going from 0 - 80
int received_int = 0; // integer value received from the Serial2 port (from main display)


void loop()
{

  if (Serial2.available() > 0) { // if there is any data in the Serial2 buffer..
    received_int = Serial2.parseInt(); // try to parse the incoming integer value
    if (received_int >= 0 && received_int <= 80) { // if the value is within range 0-80, set the roll value image
      roll_value_img = received_int;
    }

    // debug only
    // print the roll_value_img value to the display
    /*tft.setCursor(30,100);
    tft.print("Roll Img: ");
    tft.print(roll_value_img);
    tft.print("       ");*/

    tft.pushImage(0, 0, 240, 240, epd_bitmap_allArray[roll_value_img]); // draw the fullscreen image sized 240x240px on position 0,0px
  }  
}


