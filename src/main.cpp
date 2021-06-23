#include <Arduino.h>

#define DIAL0 A3
#define DIAL1 A2
#define DIAL2 A1
#define DIAL3 A0

#define BUTTON0 PD5
#define BUTTON1 PD4
#define BUTTON2 PD3
#define BUTTON3 PD2

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


void printDialValue(uint8_t pin, int dial) {
    int value = 1024 - analogRead(pin);
    Serial.print("v");
    Serial.print(dial);
    Serial.print("x");
    Serial.println(value/10);
}


int buttonLastValue[4] = {0, 0, 0, 0};

void printButtonValue(uint8_t pin, int dial) {
    int value = digitalRead(pin);
    if(buttonLastValue[dial] == value) {
        // no change
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
    printDialValue(DIAL0, 0);
    printDialValue(DIAL1, 1);
    printDialValue(DIAL2, 2);
    printDialValue(DIAL3, 3);

    printButtonValue(BUTTON0, 0);
    printButtonValue(BUTTON1, 1);
    printButtonValue(BUTTON2, 2);
    printButtonValue(BUTTON3, 3);

    sendPong();
    delay(100);
}
