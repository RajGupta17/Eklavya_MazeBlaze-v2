#include <stdio.h>
#include <math.h>

#define NO_OF_NODES 9

int dry_run[NO_OF_NODES] = { 1 , 3 , 7 , 5 , 1 , 4 , 4 , 8 , 3} ; //To be filled during dry run
/* Dry_run will hold only 4 types of values , i.e. 1 for West , 3 for North , 5 for East , 7 for South */
int final_run[50] = {0}; //after removing redundant values from dry run
int degree[50] ; //This contains angles taken at node 
int degree_index = 0 ; //This contains index for degree array
int turn_index = 0 ;   //This contains index for turns taken
float angle ;


int main ()
{
    int prev_index = 0;
    int prev_value = dry_run[prev_index];
  

    for (int i = 0; i < NO_OF_NODES ; i++)
        if ( i == 0 )   //there is no value to compare yet
        {
            printf("1lol\n") ;
            continue ;
        }
        else if (dry_run[i] == 0)	// 0 refers to the unfilled cells or the cells with redundancy removed 
        {
            printf("2lol\n") ;
            continue;
        }
        /*path is redundant or not depends upon whether there is a dead end or not i.e. the difference between two consecutive values in dry_run have difference of 4 , but also if the angle accounts to 180 degree */
        else if (fabs(prev_value - dry_run[i]) == 4)
        {
            printf("3lol\n") ;
            dry_run[i] = 0;
            dry_run[prev_index--] = 0;	//we shift our previous index one behind after making the element as 0
            prev_value = dry_run[prev_index];	//we get the previous value as per the previous index since it is already shifted
        }
        else			//This condition means no redundant path was discovered hence we increment the prev_index
        {
            printf("4lol\n") ;
            prev_value = dry_run[i];
            prev_index++;
        }

    int length_of_path = 0 ; // j is the index counter for final run
    for (int i = 0 ; i < NO_OF_NODES ; i++)
    {
        if (dry_run[i] == 0 )   //all 0's are redundant and hence are not included in node
        {
            continue;
        }
        else 
        {
            final_run[length_of_path] = dry_run[i] ;
            length_of_path++ ;
        }
    }

    for (int i = 0 ; i < length_of_path ; i++ )
    {
        printf("%d\n" , final_run[i]) ;
    }

}
