#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BG_LED_1 32
int led_on, led_off;


uint64_t bit_mask = (1ULL << BG_LED_1);

esp_err_t enable_LED()
{
    esp_err_t error;
    gpio_config_t io_config;
    io_config.pin_bit_mask = bit_mask;
    io_config.mode = GPIO_MODE_OUTPUT;
    io_config.pull_up_en = 0;
    io_config.pull_down_en = 1;
    error = gpio_config(&io_config);
    return error;

}

esp_err_t set_led_on()
{
    esp_err_t error;
    error = gpio_set_level(BG_LED_1, 1);
    return error;

}

esp_err_t set_led_off()
{
    esp_err_t error;
    error = gpio_set_level(BG_LED_1, 0);
    return error;

}

void app_main()
{
    enable_LED();
    uint8_t var = 0xFF; //for now, I have not added all LED pins so 0xFF wont work

    while(1)
    {
        set_led_on();  
        vTaskDelay(1000/portTICK_RATE_MS);
		set_led_off();
	    vTaskDelay(1000/portTICK_RATE_MS);


    } 

}
