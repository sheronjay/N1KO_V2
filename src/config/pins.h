#pragma once

#include <Arduino.h>

#define I2C_second_bus_SDA 6
#define I2C_second_bus_SCL 7

#define LED_PIN 4 // Change this to our actual LED pin
#define BUZZER_PIN 3

// ===== XSHUT pins =====
#define XSHUT_FRONT 14   // front
#define XSHUT_RIGHT90 15 // right90 (shares LOS with LEFT90)
#define XSHUT_RIGHT45 16 // right45
#define XSHUT_LEFT45 17  // left45
#define XSHUT_LEFT90 18  // left90 (shares LOS with RIGHT90)

// ===== Logical indices =====
#define IDX_FRONT 0
#define IDX_RIGHT90 1
#define IDX_RIGHT45 2
#define IDX_LEFT45 3
#define IDX_LEFT90 4

#define NUM_TOF 5

// right motor
#define PWM_B 35
#define IN1_B 37 // 37
#define IN2_B 36 // 36
// left motor
#define PWM_A 1
#define IN1_A 2  // 38
#define IN2_A 38 // 2

// == == = DIP switch pins == == =
#define DIPSWITCH_PIN_0 40
#define DIPSWITCH_PIN_1 41
#define DIPSWITCH_PIN_2 42