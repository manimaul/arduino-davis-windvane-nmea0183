//
// Created by William Kamp on 3/22/21.
//
#pragma once

#include <Arduino.h>

class Timer {

protected:
    unsigned long time = millis();

public:
    /**
     * See if a specified window of time has elapsed.
     *
     * @param checkWindow time window to check in milliseconds
     * @return true if specified window of time has elapsed false otherwise.
     * When we return true we also record the start of a new time window.
     */
    bool tick(unsigned long checkWindow) {
        auto t = millis();
        auto dt = t - time;
        if (dt >= checkWindow) {
            time = t;
            return true;
        } else {
            return false;
        }
    }

};
