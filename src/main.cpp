#include <Arduino.h>

#define DIAL0 A3
#define DIAL1 A2
#define DIAL2 A1
#define DIAL3 A0

#define BUTTON0 PD5
#define BUTTON1 PD4
#define BUTTON2 PD3
#define BUTTON3 PD2

// the range of the dial seems to go from [14, 1023]
#define MIN_DIAL_VALUE 14.0
#define MAX_DIAL_VALUE 1023.0

int dialLastValue[4] = {0, 0, 0, 0};
int buttonLastValue[4] = {0, 0, 0, 0};

void setup() {
    Serial.begin(9600);
    pinMode(DIAL0, INPUT_PULLUP);
    pinMode(DIAL1, INPUT_PULLUP);
    pinMode(DIAL2, INPUT_PULLUP);
    pinMode(DIAL3, INPUT_PULLUP);

    pinMode(BUTTON0, INPUT_PULLUP);
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
}

int scaleDialValue(int value) {
    // scale from 1-100
    auto v = (double) value;
    return (int) ((1.0 - (v - MIN_DIAL_VALUE) / (MAX_DIAL_VALUE-MIN_DIAL_VALUE)) * 100);
}

void sendDialValue(uint8_t pin, int dial) {
    int value = analogRead(pin);
    if(dialLastValue[dial] == value) {
        return;
    }
    dialLastValue[dial] = value;

    Serial.print("v");
    Serial.print(dial);
    Serial.print("x");
    Serial.println(scaleDialValue(value));
}

void sendButtonValue(uint8_t pin, int dial) {
    int value = digitalRead(pin);
    if(buttonLastValue[dial] == value) {
        return;
    }
    buttonLastValue[dial] = value;

    Serial.print("b");
    Serial.print(dial);
    Serial.print(" ");
    Serial.println(value);
}

int count = 0;
void sendPong() {
    if(++count % 15 == 0) {
        // send "pong" every ~1.5s
        Serial.println("pong");
    }
}

void loop() {
    sendDialValue(DIAL0, 0);
    sendDialValue(DIAL1, 1);
    sendDialValue(DIAL2, 2);
    sendDialValue(DIAL3, 3);

    sendButtonValue(BUTTON0, 0);
    sendButtonValue(BUTTON1, 1);
    sendButtonValue(BUTTON2, 2);
    sendButtonValue(BUTTON3, 3);

    sendPong();
    delay(100);
}
