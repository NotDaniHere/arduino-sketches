/*
 * Interfacing Arduino with ST7789 TFT display (240x240 pixel).
 * Graphics test example.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>



Adafruit_MPU6050 mpu;

// ST7789 TFT module connections
#define TFT_CS    10  // define chip select pin
#define TFT_DC     9  // define data/command pin
#define TFT_RST    8  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;

void setup(void) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.begin(9600);

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.println("");
  delay(100);
  Serial.print(F("Hello! ST77xx TFT Test"));

  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(2);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);

}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  tft.setCursor(1 , 1);
  tft.print("Accelerometer X: ");a
  tft.println(a.acceleration.x);
  tft.print("Accelerometer Y: ");
  tft.println(a.acceleration.y);
  tft.print("Accelerometer Z: ");
  tft.println(a.acceleration.z);
  tft.print("Temperature: ");
  tft.println(temp.temperature);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
  Serial.print("Acc: ");
  Serial.print(a.acceleration.x);
  Serial.print(a.acceleration.y);
  Serial.println(a.acceleration.z);
  
}

