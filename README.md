# CodeBuddy

CodeBuddy is a small ESP32-powered device that uses AI to explain code snippets directly on an OLED display. Without constatnly having to visit LLM to understand code.


---
## Features

* Explain code snippets
* Explain functions and programming keywords
* One-button operation
* Powered by ESP32 and GROQ AI

## How It Works

1. The ESP32 sends an HTTP request to a Python Flask server running on your PC.
2. The Python server reads the current clipboard content.
3. The server sends the content to an LLM (GROQ API).
4. The LLM generates a short explanation.
5. The response is sent back to the ESP32.
6. The explanation is displayed on the OLED screen.

---

## How to Use

- Copy any programming-related line, function, or keyword.
- Press the button on the device.
- Wait for the explanation to appear on the OLED display.

---

## Hardware

### Components

- ESP32 DevKit V1
- breadboard
- SSD1306 OLED Display (128×64)
- Push button
- Jumper wires

## Wiring

### OLED Display (SSD1306 I2C)

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO21    |
| SCL      | GPIO22    |

### Push Button

| Button Pin | ESP32 Pin |
|------------|-----------|
| One side   | GPIO4     |
| Other side | GND       |

> Note: Button is configured with INPUT_PULLUP in ESP32, so no external resistor is required.


---

## Software Setup
### 1. Install Python dependencies
```bash
pip install -r requirements.txt
```
### 2. Create .env file
```GROQ_API_KEY
GROQ_API_KEY=your_api_key_here
```
### 3. Run python server
```bash
python server.py
```
### 4. Configure main.ino
```bash
const char* ssid = "<YOUR_WIFI_NAME>";
const char* pass = "<YOUR_WIFI_PASSWORD>";
const char* serverIP = "<YOUR_PC_IP>";
```
Now upload code to ESP32 via USB cable

## Note

This project is still under development. There may be bugs or unexpected behavior. Improvements and new features will be added over time.
