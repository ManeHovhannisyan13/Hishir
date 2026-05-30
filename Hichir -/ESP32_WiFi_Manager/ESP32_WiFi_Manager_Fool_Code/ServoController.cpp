// ServoController.cpp
#include "ServoController.h"

ServoController::ServoController() {
    servoTargetAngle = SERVO_REST_ANGLE;
    servoCurrentAngle = SERVO_REST_ANGLE;
    servoNextStepMs = 0;
}

int ServoController::clampAngle(int angle) {
    if (angle < 0) return 0;
    if (angle > 180) return 180;
    return angle;
}

void ServoController::applyImmediate(int angle) {
    angle = clampAngle(angle);

    servoCurrentAngle = angle;
    servoTargetAngle = angle;

    servo.write(angle);
}

void ServoController::begin() {
    servo.attach(servoPin, 500, 2400);
    applyImmediate(SERVO_REST_ANGLE);
}

void ServoController::tick() {
    unsigned long now = millis();

    if (servoCurrentAngle == servoTargetAngle) return;
    if (now < servoNextStepMs) return;

    int delta =
        (servoTargetAngle > servoCurrentAngle)
        ? SERVO_MOVE_STEP_DEG
        : -SERVO_MOVE_STEP_DEG;

    int next = servoCurrentAngle + delta;

    if ((delta > 0 && next > servoTargetAngle) ||
        (delta < 0 && next < servoTargetAngle)) {
        next = servoTargetAngle;
    }

    servoCurrentAngle = next;

    servo.write(servoCurrentAngle);

    servoNextStepMs = now + SERVO_MOVE_STEP_MS;
}

void ServoController::requestAngle(int target) {
    servoTargetAngle = clampAngle(target);
    servoNextStepMs = 0;
}

void ServoController::rest() {
    requestAngle(SERVO_REST_ANGLE);
    Serial.println("servwww");
}

void ServoController::alarm() {
    requestAngle(SERVO_ALARM_ANGLE);
}

void ServoController::fillBox(int box) {
    if (box < 1) box = 1;
    if (box > MAX_MEDS) box = MAX_MEDS;

    int angle = boxAngles[box - 1];

    Serial.printf("FILL BOX=%d -> ANGLE=%d\n", box, angle);

    requestAngle(angle);
}
