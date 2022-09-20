/*
 * Copyright (c) 2019 David Antliff
 *
 * This program provides an example using the esp32-rotary-encoder component.
 * Events are received via an event queue and displayed on the serial console.
 * The task also polls the device position every second to show that the latest
 * event always matches the current position.
 *
 * esp32-rotary-encoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * esp32-rotary-encoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with esp32-rotary-encoder.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"

#include "rotary_encoder.h"

#define TAG "app"

#define ROT_ENC_L1_GPIO 4
#define ROT_ENC_L2_GPIO 16
#define ROT_ENC_R1_GPIO 17
#define ROT_ENC_R2_GPIO 5

#define ENABLE_HALF_STEPS false  // Set to true to enable tracking of rotary encoder at half step resolution
#define RESET_AT          0      // Set to a positive non-zero number to reset the position if this value is exceeded
#define FLIP_DIRECTION    false  // Set to true to reverse the clockwise/counterclockwise sense
double dist;

void app_main()
{
    // esp32-rotary-encoder requires that the GPIO ISR service is installed before calling rotary_encoder_register()
    ESP_ERROR_CHECK(gpio_install_isr_service(0));


    // Initialise the rotary encoder device with the GPIOs for A and B signals
    rotary_encoder_info_t info = { 0 };

    ESP_ERROR_CHECK(rotary_encoder_init(&info, ROT_ENC_L1_GPIO, ROT_ENC_L2_GPIO, ROT_ENC_R1_GPIO, ROT_ENC_R2_GPIO));
    
    ESP_ERROR_CHECK(rotary_encoder_enable_half_steps(&info, ENABLE_HALF_STEPS));

#ifdef FLIP_DIRECTION
    ESP_ERROR_CHECK(rotary_encoder_flip_direction(&info));
#endif

    // Create a queue for events from the rotary encoder driver.
    // Tasks can read from this queue to receive up to date position information.
    QueueHandle_t event_queue = rotary_encoder_create_queue();
    ESP_ERROR_CHECK(rotary_encoder_set_queue(&info, event_queue));


    while(1)
        {
        // Wait for incoming events on the event queue.
        rotary_encoder_event_t event = { 0 };

        if (xQueueReceive(event_queue, &event, 100 / portTICK_PERIOD_MS) == pdTRUE)
        {
            ESP_LOGI(TAG, "Event: position %lf, direction %s", (event.state.position)*0.055,
                     event.state.direction ? (event.state.direction == ROTARY_ENCODER_DIRECTION_CLOCKWISE ? "CW" : "CCW") : "NOT_SET");

        }


        else
        {
            //Poll current position and direction
            rotary_encoder_state_t state = { 0 };

            
            ESP_ERROR_CHECK(rotary_encoder_get_state(&info, &state));
            ESP_LOGI(TAG, "Distance_R: %lf, direction %s", (state.position)*0.055,
                     (state.direction == ROTARY_ENCODER_DIRECTION_CLOCKWISE ? "CW" : "CCW"));


            // Reset the device
            if (RESET_AT && (state.position >= RESET_AT || state.position <= -RESET_AT))
            {
                ESP_LOGI(TAG, "Reset");
                ESP_ERROR_CHECK(rotary_encoder_reset(&info));
            }

        }
    
        
    }
    ESP_LOGE(TAG, "queue receive failed");

    ESP_ERROR_CHECK(rotary_encoder_uninit(&info));

}

