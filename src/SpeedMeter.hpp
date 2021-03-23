//
// Created by William Kamp on 5/30/21.
//

#pragma once

class SpeedMeter {

private:
    /*
     2 second sample for 1 knot resolution
     |----|----|
     0    1    2
     */
    const static int sampleSeconds = 2;
    const static int len = sampleSeconds * 4; //250ms segments
    int arr[len] = {};
    int pos = 0;
    bool ready = false;
public:

    /**
     * Call every 250ms (4Hz)
     * @return knots
     */
    int tick() {
        auto rotations = 0;
        for (const auto &item : arr) {
            rotations += item;
        }
        if (++pos >= len) {
            pos = 0;
            ready = true;
        }
        arr[pos] = 0;

        if (ready) {
            // 1 MPH == 1600 rph
            // 9 MPH == 14400 rph
            // 9 MPH == 240 rpm
            // 9 MPH == 4 rps
            // 2.25 MPH == 1 rps
            // 2 KT == 1 rps
            return (2 * rotations) / sampleSeconds;
        } else {
            return 0;
        }
    }

    /**
     * Call every rotation
     */
    void rotation() {
        arr[pos] += 1;
    }
};
