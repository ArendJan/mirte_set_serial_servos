#include "HiwonderServo.hpp"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define servo_num 3

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

  // set id
  while (true) {
    sleep_ms(1000);

    HiwonderServo servo(&bus, servo_num);
    servo.initialize();
    sleep_ms(100);
    if (servo.id_verify() != servo_num) {
      printf("Failed to verify id, got %i\n", servo.id_verify());
      continue;
    }
    auto pos = servo.pos_read();
    printf("pos: %i\n", pos);
    // read voltage
    auto voltage = servo.vin();
    printf("voltage: %i\n", voltage);
    servo.readLimits();
    printf("limits: %i - %i\n", servo.getMinCentDegrees(),
           servo.getMaxCentDegrees());

    uint32_t lower = 0;
    uint32_t upper = 0;
    servo.getVoltageLimits(lower, upper);
    printf("voltage limits: %i - %i\n", lower, upper);

    // if serial data is available, read it and set position to that value
    if (stdio_getchar_timeout_us(0) != PICO_ERROR_TIMEOUT && false) {
      getchar_timeout_us(0); // consume the character
      int newPos = 11450;
      printf("Setting position to %i\n", newPos);
      servo.move_time(newPos, 1000);
    }
  }
}
