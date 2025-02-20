#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_PIN_R = 4;
const int LED_PIN_G = 6;
volatile int btn_red_flag = 0;
volatile int btn_green_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_PIN_R && events == GPIO_IRQ_EDGE_FALL) {
      btn_red_flag = 1;
  } else if (gpio == BTN_PIN_G && events == GPIO_IRQ_EDGE_RISE) {
      btn_green_flag = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);
  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);
  
  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

      int i = 0; 
      int j = 0;   
      while (true) {
          if (btn_red_flag) {
              btn_red_flag = 0;
              i = !i;
              if (i) {
                  gpio_put(LED_PIN_R, 1);
              } else {
                  gpio_put(LED_PIN_R, 0);
              }
          }

          if (btn_green_flag){
            btn_green_flag = 0;
            j = !j;
            if (j){
              gpio_put(LED_PIN_G,1);
            } else {
              gpio_put(LED_PIN_G,0);
            }
          }
      }
}
