//
// Created by William Kamp on 5/30/21.
//

#pragma once

class SpeedMeter {

private:
    /*
     4 second sample for .5 knot resolution
     |----|----|----|----|
     0    1    2    3    4  rotations
     0.0  0.5  1.0  1.5  2.0 kts
     */
    const static int sampleSeconds = 4;
    const static int len = sampleSeconds * 4; //250ms segments
    int ring[len] = {};
    int pos = 0;

    // we will wait (4 seconds) for the ring buffer to populate before sending results
    bool ready = false;
public:

    /**
     * Call every 250ms (4Hz)
     * @return knots (x 10)
     */
    int tick() {
        auto rotations = 0;
        for (const auto &item : ring) {
            rotations += item;
        }
        if (++pos >= len) {
            pos = 0;
            ready = true;
        }
        ring[pos] = 0;

        if (ready) {
            // 1 MPH == 1600 rph
            // 9 MPH == 14400 rph
            // 9 MPH == 240 rpm
            // 9 MPH == 4 rps
            // 2.25 MPH == 1 rps
            // 2 KT == 1 rps

            // |  0  |  1  |  2  |  3  |  4  |  5   | rotations in 4 seconds
            // |  0  | 0.5 | 1.0 | 1.5 | 2.0 | 2.5  | knots
            return (2 * rotations * 10) / sampleSeconds;
        } else {
            return 0;
        }
    }

    /**
     * Call every rotation
     */
    void rotation() {
        ring[pos] += 1;
    }
};
