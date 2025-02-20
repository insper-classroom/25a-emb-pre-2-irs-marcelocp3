#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
volatile int btn_red_flag = 0;
volatile int btn_green_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (gpio == BTN_PIN_R && events == GPIO_IRQ_EDGE_FALL) {
        btn_red_flag = 1;
    } else if (gpio == BTN_PIN_G && events == GPIO_IRQ_EDGE_FALL) {
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

    // Configurar interrupções corretamente para ambos os botões
    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    while (true) {
        if (btn_red_flag) {
            btn_red_flag = 0;
            printf("fall red\n");
        }

        if (btn_green_flag) {
            btn_green_flag = 0;
            printf("fall green\n");
        }
    }
}
