#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
// #define PCNT_HIGH_LIMIT 600
// #define PCNT_LOW_LIMIT  -600

#define encoder_phase_A 18
#define encoder_phase_B 19

volatile int count = 0;
volatile bool direction = 0;

// pcnt_unit_config_t unit_config = {
//     .high_limit = PCNT_HIGH_LIMIT,
//     .low_limit = PCNT_LOW_LIMIT,
// };
// pcnt_unit_handle_t pcnt_unit = NULL;
// ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));


static void IRAM_ATTR gpio_isr_handler(void *gpio)
{
    if (gpio == encoder_phase_A && gpio_get_level(encoder_phase_A))
        direction = gpio_get_level(encoder_phase_B);
    if (direction)
    {
        count++;
    }
    else
    {
        count--;
    }
}
void app_main()
{
    gpio_install_isr_service(0);

    gpio_config_t conf;

    conf.intr_type = GPIO_INTR_ANYEDGE;
    conf.mode = GPIO_MODE_INPUT;
    conf.pin_bit_mask = (1ULL << encoder_phase_A) | (1ULL << encoder_phase_B);
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&conf); 
    while (1)
    {
        gpio_isr_handler_add(encoder_phase_A, gpio_isr_handler, (void *)encoder_phase_A);
        gpio_isr_handler_add(encoder_phase_B, gpio_isr_handler, (void *)encoder_phase_B);
        
        printf("%d \n", count);
        vTaskDelay(10 / portTICK_RATE_MS);

        
    }
}