#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
volatile int btn_red_flag = 0;
volatile int btn_green_flag = 0;
volatile int i = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events = GPIO_IRQ_EDGE_FALL_RED){
    i = 1;
  }
  btn_red_flag = 1;

  if (events = GPIO_IRQ_EDGE_FALL_GREEN){
    i = 2;
  }
  btn_green_flag = 1;
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (btn_red_flag){
      btn_red_flag = 0;
      if (i == 1){
        printf("fall red");
      }
    }

    if (btn_green_flag){
      btn_green_flag = 0;
      if(i == 2){
        printf("fall green");
      }
    }
  }
}
