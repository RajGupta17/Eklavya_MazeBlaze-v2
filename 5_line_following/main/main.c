#include "mazeblaze2.h"
/*This method involves tuning kp , ki ,kd physically*/
#define GOOD_DUTY_CYCLE 68
#define MIN_DUTY_CYCLE 55
#define MAX_DUTY_CYCLE 85
#define NO_OF_NODES 150

/*variables which help to decide which turns to take*/
bool left_possible ;
bool right_possible = 0 ; 
bool straight_possible = 0 ;

int Turn ;
float error=0, prev_error=0, difference, cumulative_error, correction; 
float left_duty_cycle = 0, right_duty_cycle = 0;
int prev_Turn ;
int prev_lsa0_value = 0 ;  //left most sensor
int prev_lsa2_value = 0 ; //middle sensor
//we dont need a right sensor prev reading since we are using left follow
bool is_end = false ;
int total_angle = 0;

int dry_run[NO_OF_NODES] = {0} ;; //To be filled during dry run
/* Dry_run will hold only 4 types of values , i.e. 1 for West , 3 for North , 5 for East , 7 for South */
int final_run[NO_OF_NODES] = {3 , 0}; //after removing redundant values from dry run and the first value is hardcoded as 3 since it north as start always
int degree[NO_OF_NODES] = {0} ; //This contains angles taken at node . hardcoding the first degree as 0 , since it is always going to be in line 
int degree_index = 1 ; //This contains index for degree array
int turn_index = 0 ;   //This contains index for turns taken
int angle ;
int final_run_index = 1 ; //final_run[0] is already 3 which stands for north 
int prev_in_final_run;

void circular_defn(int change_in_dir) ;
float bound(float val, float min, float max) ;
void calculate_correction() ;
void calculate_error() ;


void line_follow_task(void *arg)
{

    while (1)
    {
        get_raw_lsa();

        calculate_error();
        calculate_correction();

        left_duty_cycle = bound((GOOD_DUTY_CYCLE - correction), MIN_DUTY_CYCLE, MAX_DUTY_CYCLE);
        right_duty_cycle = bound((GOOD_DUTY_CYCLE + correction), MIN_DUTY_CYCLE, MAX_DUTY_CYCLE);
   
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);    /*goes forward in this case*/
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
// end of task

void app_main()
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());

    xTaskCreate(&line_follow_task, "line_follow_task", 4096, NULL, 1, NULL); // creating a task to start line following
}
// end of main

void calculate_error()
{
    /*
    possible cases of errors :-
    1) All the front sensor read black - this means the bot is entirely out of path
    2) if lsa_reading [1] != lsa_reading [2] != lsa_reading [3] != 1 - this means bot is slightly out of path

    error to right of line is +ve while left of line is -ve
    */
    if (lsa_reading[0] == 0 && lsa_reading[1] == 0 && lsa_reading[2] == 0 && lsa_reading[3] == 0 && lsa_reading[4] == 0)
    {
        /*All sensore read black*/
        if (prev_error > 0) // we use prev_error to extract the sign to give to error
        {
            error = 2.5; // arbitrary value
        }
        else
        {
            error = -2.5; // arbitrary value
        }
    }
    else if (lsa_reading[1] == 0 && lsa_reading[3] == 1000)
    {
        /* turn right to nullify */
        error = 1; // arbitrary value
    }
    else if (lsa_reading[1] == 1000 && lsa_reading[3] == 0)
    {
        /* turn left to nullify */
        error = -1; // arbitrary value
    }
    else if (lsa_reading[1] == 1000 && lsa_reading[2] == 1000 && lsa_reading[3] == 1000)
    {
        /* no error since the bot is on line */
        error = 0; // arbitrary value
    }
    else
    {
        error = 0; // this case is for safety
    }
}
// end of function

void calculate_correction()
{
    error = error * 10;              // we need the error correction in range 0-100 so that we can send it directly as duty cycle paramete
    difference = error - prev_error; // used for calcuating kd
    cumulative_error += error;       // used for calculating ki

    cumulative_error = bound(cumulative_error, -30, 30); // bounding cumulative_error to avoid the issue of cumulative_error being very large

    float kp , ki , kd ;
    kp = 3.5 ;
    kd = 1.25 ;
    ki = 0 ; 

    correction = kp* error + ki * cumulative_error + kd * difference; // defined in http_server.c

    prev_error = error; // update error
}
// end of function

float bound(float val, float min, float max) //To bound a certain value in range MAX to MIN 
{
    if (val > max)
        val = max;
    else if (val < min)
        val = min;
    return val;
}
//end of function

void circular_defn(int change_in_dir)
{
    /*The use of this function is have a circular defination from 1 to 8 
    1 - W , 2 - NW , 3 - N , 4 - NE , 5 - E , 6 - SE , 7 - S , 8 - SW 
    The difference of 4 stands for u turn i.e. dead end . this will help us to delete that path from char array 
    subtracting 4 from 1 will give 5 according tio this function */
    int temp = Turn ;
    Turn = prev_Turn + change_in_dir ; //for LFR , change_in_dir = -2 means left
    prev_Turn = temp ; 

    if (Turn <= 0)
    {
        Turn = Turn + 8 ;
        /*fpr eg . if you were moving in west i.e. 1 and then you were to take left . As per LFR , your new direction is 1 - 2 = -1 ;
        now -1 + 8 is 7 which is 7 . Now using LFR you are facing lsouth which is also 7*/
    }
    if (Turn <= 0)
    {
        Turn = Turn - 8 ;
        /*fpr eg . if you were moving in south i.e. 7 and then you were to take right . As per LFR , your new direction is 7 + 2 = 9 ;
        now 9 - 8 is 1 which is 1 . Now using LFR you are facing west which is also 1*/
    }
}
//end of function