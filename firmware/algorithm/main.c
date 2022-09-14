#include <stdio.h>
#include <stdbool.h>

struct node // defining a struct for all nodes
{
    int coordinates[1][1];
    int possible_arr[8]; // 8 types of directions
    int explored_arr[8];
    int dir;
    char neighbours[8] ;
    int nodal_distance[8] ;
};

// function prototyping
void NodalAnalysis(bool result, int no_of_nodes, struct node *node[100], int obtained_coordinates[1][1], int lsa_sensors[9], bool IsEndComplete , int dir );
bool IsNewNode(int obtained_coordinates[1][1], struct node node[100], int no_of_nodes);
void TypeDetector(int lsa_sensors[8], int no_of_nodes, int possible_arr[8] , int explored_arr[8] , int dir) ;

//main starts here
int main()
{
    int no_of_nodes, obtained_coordinates[1][1], lsa_sensors[9];
    bool IsEndComplete;
    struct node node[100];

    //----------------------This is hardcoded for the start node--------------------------
    node[0].possible_arr = node[0].explored_arr = {0} ; 
    node[0].dir = 3 ; // North 
    node[0].TypeDetector() ;

}
//end of main 


void NodalAnalysis(bool result, int no_of_nodes, struct node *node[100], int obtained_coordinates[1][1], int lsa_sensors[9], bool IsEndComplete , int dir)
{
    if (result == 1)
    {
        node[no_of_nodes]->coordinates == obtained_coordinates;
        TypeDetector(lsa_sensors, no_of_nodes, node[no_of_nodes]->possible_arr , node[no_of_nodes]->explored_arr , dir  );
        no_of_nodes++;
    }
    else
    {
        if (IsEndComplete == 1)
        {
        }
    }
}
//end of function

bool IsNewNode(int obtained_coordinates[1][1], struct node node[100], int no_of_nodes)
{
    for (int i = 0; i < no_of_nodes; i++)
    {
        if (obtained_coordinates[0][0] == node[i].coordinates[0][0]) // comparing with all available coordinates of previous unique nodes
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
//end of function

void TypeDetector(int lsa_sensors[8], int no_of_nodes, int possible_arr[8] , int explored_arr[8] , int dir )
{
//This function will detect the type of node and on basis of  present direction , it will fill the array 
}
//end of function

