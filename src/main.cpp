#include <Arduino.h>

/*
 * MWV - Wind Speed and Angle
 * $--MWV,x.x,a,x.x,a,A*hh<CR><LF>
 *         |  |  |  | |__ Status, A = Data Valid, V = Data invalid
 *         |  |  |  |____ Wind speed units, K = kph, M = mps, N = knots
 *         |  |  |_______ Wind speed
 *         |  |__________ Reference, R = Relative, T = True
 *         |_____________ Wind Angle, 0 to 359 degrees
 */

char buffer1[40];
char buffer2[40];
unsigned long time;

uint8_t nmeaChecksum(const char *sentence) {
    const char *n = sentence + 1;
    uint8_t chk = 0;

    while ('*' != *n && '\n' != *n && '\0' != *n) {
        chk ^= (uint8_t) *n;
        n++;
    }

    return chk;
}

void setup() {
    Serial.begin(4800);
}

void loop() {
    auto t = millis();
    auto dt = t - time;
    if (dt >= 250L) {
        time = t;
        auto direction = map(analogRead(A4), 0, 1023, 0, 360);
        sprintf(buffer1, "WIMWV,%li.0,R,0.0,N,A", direction);
        auto sum = nmeaChecksum(buffer1);
        sprintf(buffer2, "$%s*%02X\r\n", buffer1, sum);
        Serial.print(buffer2);
    }
}

