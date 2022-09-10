#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define encoder_phase_A 18
#define encoder_phase_B 19

volatile int count = 0 ; 
int direction = 0 ;


static void IRAM_ATTR gpio_isr_handler(void* arg) {
    if(1) {
        if(gpio_get_level(encoder_phase_A))
            direction = gpio_get_level(encoder_phase_B);
        if(direction) {
            count++;
            printf("%d %d" , count , direction ) ;
        } else {
            count--;
            printf("%d %d" , count , direction ) ;
        }
    }
}

void app_main ()
{
    gpio_config_t conf;
    conf.intr_type = GPIO_INTR_ANYEDGE;
    conf.mode = GPIO_MODE_INPUT;
    conf.pin_bit_mask = (1 << encoder_phase_A ) | (1 << encoder_phase_B);
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&conf);

    gpio_isr_handler_add(encoder_phase_A, gpio_isr_handler, (void*)encoder_phase_A);
    gpio_isr_handler_add(encoder_phase_B, gpio_isr_handler, (void*)encoder_phase_B);

    gpio_isr_handler_remove(encoder_phase_A);
    gpio_isr_handler_remove(encoder_phase_B);
}
