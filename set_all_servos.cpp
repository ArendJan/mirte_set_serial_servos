#include "HiwonderServo.hpp"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

// #define servo_num 2

typedef struct {
  uint8_t id;
  int16_t min;
  int16_t max;
  int16_t home;

} servo_settings_t;

float voltage_limit_min = 10.0f;
float voltage_limit_max = 14.0f;

servo_settings_t servos_settings_all[] = {
    // #if servo_num ==2
    {
        .id = 2, .min = 3400, .max = 21000, .home = 12000
        // #endif
    },
    {.id = 3, .min = 2832, .max = 20000, .home = 11450},
    {.id = 4, .min = 120, .max = 21000, .home = 11750},
    {.id = 5, .min = 1128, .max = 21000, .home = 12200},
    {.id = 6, .min = 6168, .max = 14224, .home = 10524}};

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart0
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
  stdio_init_all();
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  HiwonderBus bus;
  bus.begin(UART_ID, UART_RX_PIN, UART_TX_PIN);

  sleep_ms(10000);

  // set id
  while (true) {
    for (auto &servos_settings : servos_settings_all) {
      HiwonderServo servo(&bus, servos_settings.id);
      servo.initialize();
      sleep_ms(100);
      if (servo.id_verify() != servos_settings.id) {
        printf("Failed to verify id, got %i\n", servo.id_verify());
        continue;
      }
      printf("Servo %i initialized\n", servos_settings.id);
      printf("current pos: %i\n", servo.pos_read());
      servo.setVoltageLimits(voltage_limit_min * 1000,
                             voltage_limit_max * 1000);
      servo.setLimitsTicks(servos_settings.min / 24, servos_settings.max / 24);
      servo.angle_offset_adjust(0);
      printf("Servo %i calibrated with home %i, min %i, max %i\n",
             servos_settings.id, servos_settings.home, servos_settings.min,
             servos_settings.max);
      sleep_ms(1000);
      servo.move_time(servos_settings.home, 1000);
      printf("Servo %i moved to home position %i\n", servos_settings.id,
             servo.pos_read());
      printf("limits set to min %i, max %i\n", servo.getMinCentDegrees(),
             servo.getMaxCentDegrees());
      sleep_ms(1000);
    }
    sleep_ms(10000);
  }
}
