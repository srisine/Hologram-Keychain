#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Common addresses: 0x3C or 0x3D

// Default I2C pins on most ESP32-C3 boards
#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* messages[] = {
  "ESP32-C3 Ready!",
  "Rotating Text",
  "I2C OLED 128x64",
  "Hello World!"
};
const int numMessages = sizeof(messages) / sizeof(messages[0]);

int currentIndex = 0;
unsigned long lastSwitchTime = 0;
const unsigned long switchInterval = 2000; // Change text every 2 seconds

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.display();
}

void loop() {
  unsigned long now = millis();
  if (now - lastSwitchTime >= switchInterval) {
    lastSwitchTime = now;
    currentIndex = (currentIndex + 1) % numMessages;
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextWrap(false);

  // Center the text horizontally and vertically
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(messages[currentIndex], 0, 0, &x1, &y1, &w, &h);

  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;
  if (x < 0) x = 0;

  display.setCursor(x, y);
  display.print(messages[currentIndex]);
  display.display();

  delay(30);
}
