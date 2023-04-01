#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_GFX.h>

#define TFT_CS   -10
#define TFT_RST  9
#define TFT_DC   8

Adafruit_MPU6050 mpu;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Wire.begin();
  mpu.begin();
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 10);
  tft.println("MPU6050 Arrow");
}

void loop() {
  sensors_event_t accel;
  mpu.getAccelerometerSensor()->getEvent(&accel);

  float x = accel.acceleration.x;
  float y = accel.acceleration.y;
  float z = accel.acceleration.z;

  float roll = atan2(-y, z) * 180 / PI;
  float pitch = atan2(x, sqrt(y * y + z * z)) * 180 / PI;

  int x1 = 120 + cos(roll * PI / 180) * 50;
  int y1 = 120 + sin(roll * PI / 180) * 50;
  int x2 = 120 + cos((roll + 150) * PI / 180) * 50;
  int y2 = 120 + sin((roll + 150) * PI / 180) * 50;
  int x3 = 120 + cos((roll + 210) * PI / 180) * 50;
  int y3 = 120 + sin((roll + 210) * PI / 180) * 50;
  int x4 = 120 + cos((roll + 180) * PI / 180) * 70;
  int y4 = 120 + sin((roll + 180) * PI / 180) * 70;

  tft.fillScreen(ST77XX_BLACK);
  tft.drawLine(x1, y1, x2, y2, ST77XX_WHITE);
  tft.drawLine(x2, y2, x3, y3, ST77XX_WHITE);
  tft.drawLine(x3, y3, x1, y1, ST77XX_WHITE);
  tft.drawLine(x1, y1, x4, y4, ST77XX_WHITE);

  delay(50);
}
              
