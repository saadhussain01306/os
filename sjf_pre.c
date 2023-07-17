#include<stdio.h>
#include<stdlib.h>

typedef struct process {
    int Id, AT, BT, CT, TAT, WT; 
} pro;

pro p[15];

void main() {
    int n, tempBT[15], total_WT=0, total_TAT=0;
    float avg_WT=0, avg_TAT=0;
    int minIndex, minBT, completed=0, curTime = 0;
    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);
    printf("\nEnter the arrival time and burst time of the process:\n");
    printf("AT BT\n");
    for(int i=0; i<n; i++) {
        p[i].Id = (i+1);
        scanf("%d%d", &p[i].AT, &p[i].BT);
        tempBT[i] = p[i].BT;
    }

    printf("\nGantt Chart:\n");
    while(completed != n) {
        minIndex = -1;
        minBT = 9999;
        for(int i=0; i<n; i++) {
            if(p[i].AT <= curTime && p[i].BT>0) {
                if(p[i].BT < minBT || (p[i].BT == minBT && p[i].AT < p[minIndex].AT)) {
                    minBT = p[i].BT;
                    minIndex = i;
                }
            }
        }

        curTime++;

        if (minIndex != -1)
        {
            p[minIndex].BT--;
            printf("| P%d(1) %d", p[minIndex].Id, curTime);
            if (p[minIndex].BT == 0)
            {
                p[minIndex].CT = curTime;
                p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
                p[minIndex].WT = p[minIndex].TAT - tempBT[minIndex];
                total_TAT += p[minIndex].TAT;
                total_WT += p[minIndex].WT;
                completed++;
            }
        }
    }
    printf("|\n");
    avg_TAT = (float)total_TAT/n;
    avg_WT = (float)total_WT/n;

    //Printing the table of processes with details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT);
    }
    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);
}
/*
Enter the number of processes:
4

Enter the arrival time and burst time of the process:
AT BT
0 6
1 4
2 2
3 3

Gantt Chart:
| P1(1) 1| P2(1) 2| P3(1) 3| P3(1) 4| P2(1) 5| P2(1) 6| P2(1) 7| P4(1) 8| P4(1) 9| P4(1) 10| P1(1) 11| P1(1) 12| P1(1) 13| P1(1) 14| P1(1) 15|

PID	AT	BT	CT	TAT	WT
1	0	6	15	15	9
2	1	4	7	6	2
3	2	2	4	2	0
4	3	3	10	7	4

Average TAT = 7.50
Average WT = 3.75
*/
