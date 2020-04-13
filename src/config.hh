#ifndef CONFIG_HH
#define CONFIG_HH

struct Config {
    static const bool DEBUG = false;

    /*******************************************************************************
     * PIN LAYOUT
     ******************************************************************************/
    // General outputs
    static const int MOVE_BELT_OUT_PIN = 7;
    static const int MAIN_PUSHER_OUT_PIN = 0;
    static const int WHITE_PUSHER_OUT_PIN = 2;
    static const int BLACK_PUSHER_OUT_PIN = 3;

    // General inputs
    static const int MAIN_PRESENCE_IN_PIN = 1;
    static const int MAIN_PUSHER_ENDSTOP_IN_PIN = 6;
    static const int WHITE_SENSOR_IN_PIN = 26;
    static const int BLACK_SENSOR_IN_PIN = 27;

    // Pins which encode information via combinations
    static const int STATUS_2_OUT_PIN = 21;
    static const int STATUS_1_OUT_PIN = 22;
    static const int STATUS_0_OUT_PIN = 23;

    static const int COLOR_SENSOR_0_IN_PIN = 4;
    static const int COLOR_SENSOR_1_IN_PIN = 5;
};
#endif //CONFIG_HH
