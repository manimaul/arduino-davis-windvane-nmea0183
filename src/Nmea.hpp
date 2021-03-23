//
// Created by William Kamp on 3/22/21.
//

#pragma once

#include <Arduino.h>

class Nmea {

public:
    static const size_t BUFFER_LEN = 40;

    /*
     * MWV - Wind Speed and Angle
     * $--MWV,x.x,a,x.x,a,A*hh<CR><LF>
     *         |  |  |  | |__ Status, A = Data Valid, V = Data invalid
     *         |  |  |  |____ Wind speed units, K = kph, M = mps, N = knots
     *         |  |  |_______ Wind speed
     *         |  |__________ Reference, R = Relative, T = True
     *         |_____________ Wind Angle, 0 to 359 degrees
     */
    void writeMwv(long direction, int kts) {
        sprintf(bodyBuffer, "WIMWV,%li.0,R,%i.0,N,A", direction, kts);
        checksum();
        Serial.print(sentenceBuffer);
    }

private:
    char bodyBuffer[BUFFER_LEN];
    char sentenceBuffer[BUFFER_LEN];

    void checksum() {
        uint8_t sum = 0;
        for (char n : bodyBuffer) {
            if (n == '\0') {
                break;
            }
            sum ^= (uint8_t) n;
        }
        sprintf(sentenceBuffer, "$%s*%02X\r\n", bodyBuffer, sum);
    }

};
