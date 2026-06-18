#include <WiFi.h>
#include <HTTPClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_W 128
#define SCREEN_H 64

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

const char* ssid = "<YOUR_WIFI_NAME>";
const char* pass = "<YOUR_WIFI_PASSWORD>";

// Open cmd, type ipconfig, look for "IPv4 Address"
const char* serverIP = "<YOUR_PC_IP>";

bool previousState = HIGH;

#define buttonPin 4

void showWrappedText(String text) {
  display.clearDisplay();
  display.setCursor(0, 0);

  int maxLen = 21;
  String line = "";
  String word = "";

  text += " "; 

  for (int i = 0; i < text.length(); i++)
  {
    char c = text[i];

    if (c == ' ')
    {
      if (line.length() + word.length() > maxLen)
      {
        display.println(line);
        line = word + " ";
      }
      else
      {
        line += word + " ";
      }
      word = "";
    }
    else
    {
      word += c;
    }
  }

  if (line.length() > 0)
    display.println(line);

  display.display();
}

void analyzeCode() {
  display.clearDisplay();
  display.setCursor(10,10);
  display.println("Contacting PC...");
  display.display();

  HTTPClient http;

  String url = String("http://") + serverIP + ":5000/analyze";

  http.begin(url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    String text = http.getString();

    Serial.println(text);
    showWrappedText(text);
  } else {
    showWrappedText("Request failed please try again.");
  }
  http.end();
}


void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAILED.");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(WHITE);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Connecting WiFi...");
    display.display();
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("WiFi connected to: ");
  display.setCursor(0, 20);
  display.print(WiFi.SSID());
  display.display();

  delay(5000);

  display.clearDisplay();
  display.display();
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  if (currentState == LOW && previousState == HIGH) {
    analyzeCode();
  }

  previousState = currentState;

  delay(50);
}

