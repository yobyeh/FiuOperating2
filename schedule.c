//This code is designed to emulate the running of FCFS and SJF schedules then output information on them.
//John Patrick
//6356296

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
    //Close the file after reading
    fclose(file);

    //Identifying scedule selection or exit
    int userSelect = 0;
    if(strcmp(argv[2], "FCFS") == 0){
        userSelect = 1;
    }else if (strcmp(argv[2], "SJF") == 0){
        userSelect = 2;
    }else{
        printf("Selected schedule not recognized\n Options are FCFS and SJF");
        free(arrival);
        free(burst);
        exit(1);
    }

    //Tracking process labels
    int processLables[numProcess];
    for(int i = 0; i < numProcess; i++){
        processLables[i] = i + 1;
    }

    //Sorting arrays by arrival time
    for(int i = 0; i < numProcess; i++){
        int oldArrival = arrival[i];
        int oldBurst = burst[i];
        int oldLable = processLables[i];
        for(int j = i + 1; j < numProcess; j++){
            int newArrival = arrival[j];
            int newBurst = burst[j];
            int newLable = processLables[j];
            if(oldArrival > newArrival){
                arrival[i] = newArrival;
                arrival[j] = oldArrival;
                burst[i] = newBurst;
                burst[j] = oldBurst;
                processLables[i] = newLable;
                processLables[j] = oldLable;
            }
        }
    }

    //Tracking start and end time of process
    int startTime[numProcess];
    int endTime[numProcess];
    for(int i = 0; i < numProcess; i++) {
    startTime[i] = -1;
    endTime[i] = -1;
    }

    //Run desired schedule
    switch (userSelect)
    {
        //FCFS
        case 1:{
            
            //Print process order
            printf("Process order\n");
            for (int i = 0; i < numProcess; i++){
                printf(" %d ", processLables[i]);
            }
            printf("\n");

            //Running FCFS
            int currentTime = 0;
            int currentProcess = 0;
            int completedProcess = 0;
            while(completedProcess < numProcess){
                if(arrival[currentProcess] <= currentTime){
                    startTime[currentProcess] = currentTime;
                    currentTime += burst[currentProcess];
                    endTime[currentProcess] = currentTime;
                    completedProcess++;
                    currentProcess++;
                }else{
                    currentTime++;
                }
            }
            
            //Average wait
            int totalWait = 0;
            for (int i = 0; i < numProcess; i++){
                int waitTime = startTime[i] - arrival[i];
                totalWait += waitTime;
            }
            double averageWait = (double)(totalWait) / numProcess;
            printf("average wait time is: %f\n", averageWait);

            //Average turnaround
            int totalTurn = 0;
            for (int i = 0; i < numProcess; i++){
                int turn = endTime[i] - arrival[i];
                totalTurn += turn;
            }
            double averageTurn = (double)(totalTurn) / numProcess;
            printf("Average turnaround time is: %f\n", averageTurn);
            break;
        }
        //SJF
        case 2:{
            int completedProcess = 0;
            int currentTime = 0;
            int visited[numProcess];
            int orderCompleted[numProcess];
            for(int i = 0; i < numProcess; i++){
                visited[i] = 0;
            }

            //Running SJF
            while(completedProcess < numProcess){
                int shortBurstLocation = 0;
                int shortBurst = INT_MAX;
                for(int i = 0; i < numProcess; i++){
                    if (arrival[i] <= currentTime && !visited[i] && burst[i] < shortBurst){
                    shortBurst = burst[i];
                    shortBurstLocation = i;
                    }
                }
                if(startTime[shortBurstLocation] == -1){
                    startTime[shortBurstLocation] = currentTime;
                }
                currentTime += shortBurst; // Process completes
                endTime[shortBurstLocation] = currentTime;
                visited[shortBurstLocation] = 1;
                orderCompleted[completedProcess] = processLables[shortBurstLocation];
                completedProcess++;
            }

            //Print order
            printf("Process order\n");
            for(int i = 0; i < numProcess; i++){
                printf(" %d ", orderCompleted[i]);
            }


            //Average wait
            int totalWait = 0;
            for (int i = 0; i < numProcess; i++){
                int waitTime = startTime[i] - arrival[i];
                totalWait += waitTime;
            }
            double averageWait = (double)(totalWait) / numProcess;
            printf("average wait time is: %f\n", averageWait);

            //Average turnaround
            int totalTurn = 0;
            for (int i = 0; i < numProcess; i++){
                int turn = endTime[i] - arrival[i];
                totalTurn += turn;
            }
            double averageTurn = (double)(totalTurn) / numProcess;
            printf("Average turnaround time is: %f\n", averageTurn);
            break;
        }
        default:
            break;
    }
    
    //Release the dynamically allocated memory
    free(arrival);
    free(burst);

    return 0;
}
