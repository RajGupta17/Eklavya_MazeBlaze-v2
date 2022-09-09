#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"    //for GPIO pins
#include "esp_attr.h"      //For IRAM - Instant ram where interupts are stored

#define encoder_phase_A 18
#define encoder_phase_B 19  //for directly these macros instead of remembering numbers 

int count = 0 ;

void IRAM_ATTR isr() {
    if(gpio_get_level(encoder_phase_B) == 1) //This symbolizes that B is high when A is RISING
    {
        count ++; //clockwise
        printf("%d\n" , count ) ;
    }

    else if(gpio_get_level(encoder_phase_B) == 0) //This symbolizes that B is low when A is RISING
    {
        count --;  //anticlockwise
        printf("%d\n" , count ) ;
    }
}

void setup() {
	Serial.begin(115200);
	pinMode(encoder_phase_A, INPUT_PULLUP);
	attachInterrupt(encoder_phase_A, isr, RISING );
}

void app main ()
{
    setup() ;
    gpio_isr_handler_add(encoder_phase_A, isr, (void*)encoder_phase_B);
}