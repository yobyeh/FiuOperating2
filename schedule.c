//This code is designed to emulate the running of FCFS and SJF schedules then output information on them.
//John Patrick
//6356296

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    FILE *file;
    int numProcess;
    int *arrival;
    int *burst;

    // Open the file
    file = fopen(argv[1], "r");
    // Read the first line - number of processes, note the '&' operator before num_process
    fscanf(file, "%d", &numProcess);
    
    // Allocate the arrays to store the arrival time and burst time, one element for each process
    arrival = (int *)malloc(numProcess * sizeof(int));
    burst = (int *)malloc(numProcess * sizeof(int));

    // Read each line of the file for arrival time and burst time, note that no '&' operator used here
    for (int i = 0; i < numProcess; i++){
        fscanf(file, "%d", arrival + i);
        fscanf(file, "%d", burst + i);
    }
    // You should close the file after reading, even though it's usually ok to forget
    fclose(file);
    
    // In this example I only print the values, in your assignment you have to compute the execution sequence
    // as well as the average waiting time and average turnaround time
    printf("There are %d processes\n", numProcess);
    for (int i = 0; i < numProcess; i++){
        printf("Process %d arrives at %d with burst time %d\n", i + 1, arrival[i], burst[i]);
    }

    //identifying scedule selection or exit
    int userSelect = 0;
    if(strcmp(argv[2], "FCFS") == 0){
        userSelect = 1;
    }else if (strcmp(argv[2], "SJF") == 0){
        userSelect = 2;
    }else{
        printf("Selected schedule not recognized\n Options are FCFS and SJF");
        exit(1);
    }
    
    //run desired schedule
    //output order Average wait and average turnaround

    switch (userSelect)
    {
    //FCFS
    case 1:
        int currentArrival = arrival[0];
        int arrivals[sizeof(arrival)];
        for (int i = 0; i < sizeof(arrival); i++){
            for (int j = 0; j < sizeof(arrival); j++){
                //if(currentArrival > )
            }
        }

        break;
    //SJF
    case 2:
        /* code */
        break;
    default:
        break;
    }
    
    // And remember to release the dynamically allocated memory after using
    free(arrival);
    free(burst);

    return 0;
}