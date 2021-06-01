#include <Arduino.h>
#include "Nmea.hpp"
#include "Timer.hpp"
#include "SpeedMeter.hpp"


Nmea nmea = Nmea{};
Timer timer = Timer{};
SpeedMeter speedMeter = SpeedMeter{};

void rotation() {
    speedMeter.rotation();
}

/**
 * Davis wires
 * Yellow 5v
 * Red Negative
 * Green Wind Direction
 * Black Wind Speed
 */
void setup() {
    Serial.begin(4800);
    pinMode(7, INPUT_PULLUP); // use built in pull-up resistor
    auto iu = digitalPinToInterrupt(7);
    attachInterrupt(iu, rotation, FALLING);
    sei();
}

void loop() {
    if (timer.tick(250)) {
        auto ktsX10 = speedMeter.tick();
        auto direction = map(analogRead(A4), 0, 1023, 0, 360);
        nmea.writeMwv(direction, ktsX10);
    }
}
