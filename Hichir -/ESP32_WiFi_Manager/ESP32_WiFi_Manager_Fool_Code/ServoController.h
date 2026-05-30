// ServoController.h
#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <ESP32Servo.h>

using ServoImpl = Servo;

class ServoController {
public:
    static const int MAX_MEDS = 6;

    ServoController();

    void begin();
    void tick();

    void rest();
    void alarm();
    void fillBox(int box);

    int clampAngle(int angle);
    void applyImmediate(int angle);
    void requestAngle(int target);

private:
    static const int servoPin = 15;

    static const int SERVO_ALARM_ANGLE = 90;
    static const int SERVO_REST_ANGLE = 0;
    static const int SERVO_FILL_STEP_ANGLE = 45;

    static const int SERVO_MOVE_STEP_DEG = 2;
    static const unsigned long SERVO_MOVE_STEP_MS = 15;

    const int boxAngles[MAX_MEDS] = {30, 60, 90, 120, 150, 180};

    ServoImpl servo;

    int servoTargetAngle;
    int servoCurrentAngle;
    unsigned long servoNextStepMs;

};

#endif
