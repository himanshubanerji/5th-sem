#include <stdio.h>
#include <stdlib.h>

#define RESOURCE_NUM 3
#define PROCESS_NUM 5

int alloc[PROCESS_NUM][RESOURCE_NUM];
int max[PROCESS_NUM][RESOURCE_NUM];
int total[RESOURCE_NUM] = {10, 5, 3};
int avail[RESOURCE_NUM] = {3, 3, 2};
int previous[RESOURCE_NUM] = {3, 3, 2};
int need[PROCESS_NUM][RESOURCE_NUM];
int finish[PROCESS_NUM];

void getNeedMatrix(){
    printf("Need Matrix:\n");
    for (int i =0 ;i<PROCESS_NUM; i++){
        for (int j =0; j<RESOURCE_NUM; j++){
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }
}

int checkSafety(){
    int i =0;
    for (; i<PROCESS_NUM; i++){
        if (finish[i]) continue;

        int process_fail = 0;
        for (int j=0 ; j<RESOURCE_NUM; j++){
            if (avail[j] < need[i][j]){
                process_fail = 1;
                break;
            }
        }

        if (process_fail == 1) {
            continue;
        }
        else {
            printf("Process %d finished: ", i);
            finish[i] = 1;
            for (int j=0 ; j<RESOURCE_NUM; j++){
                avail[j] += alloc[i][j];
                printf("%d ", avail[j]);
            }
            printf("\n");
            if (i == PROCESS_NUM-1) i =-1;
        }
    }
}

void printUpdatedVals(){
    printf("Allocated Matrix:\n");
    for (int i =0 ;i<PROCESS_NUM; i++){
        for (int j =0; j<RESOURCE_NUM; j++){
            printf("%d  ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("Need Matrix:\n");
    for (int i =0 ;i<PROCESS_NUM; i++){
        for (int j =0; j<RESOURCE_NUM; j++){
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }

    printf("Avail Matrix:\n");
    for (int i =0 ;i<RESOURCE_NUM; i++){
        printf("%d  ", avail[i]);
    }
    printf("\n");
}

void requestProcess(int pno, int request[RESOURCE_NUM]){
    for (int i =0 ;i<PROCESS_NUM; i++){
        finish[i] = 0;
    }
    // avail[0] = 3;
    // avail[1] = 3;
    // avail[2] = 2;
    for (int i =0 ;i<RESOURCE_NUM; i++){
        avail[i] = previous[i];
    }

    for (int i=0 ; i<RESOURCE_NUM; i++){
        if (request[i] > need[pno][i] || request[i]>avail[i]){
            printf("Request Not Possible.\n");
            return;
        }
    }

    for (int i=0 ; i<RESOURCE_NUM; i++){
        avail[i] = avail[i] - request[i];
        previous[i] = avail[i];
        alloc [pno][i] = alloc[pno][i] + request[i];
        need [pno][i] = need[pno][i] - request[i];
    }

    printUpdatedVals();

    checkSafety();
    for (int i=0; i<RESOURCE_NUM; i++){
        if (!finish [i]) {
            printf("System not safe\n\n");
            for (int j=0; j<RESOURCE_NUM; j++){
                avail[j] = avail[j] + request[j];
                alloc [pno][j] = alloc[pno][j] - request[j];
                need [pno][j] = need[pno][j] + request[j];
            }
            return;
        }
    }
    printf("System is safe\n\n");
}

int main(){
    int request[RESOURCE_NUM];
    int pno;

    printf("Enter allocation matrix values: ");
    for (int i =0 ;i<PROCESS_NUM; i++){
        for (int j =0; j<RESOURCE_NUM; j++){
            scanf ("%d", &alloc[i][j]);
        }
    }

    printf("Enter max matrix values: ");
    for (int i =0 ;i<PROCESS_NUM; i++){
        for (int j =0; j<RESOURCE_NUM; j++){
            scanf ("%d", &max[i][j]);
        }
    }

    for (int i =0 ;i<PROCESS_NUM; i++){
        finish[i] = 0;
    }

    getNeedMatrix();

    checkSafety();
    for (int i=0; i<RESOURCE_NUM; i++){
        if (!finish [i]) {
            printf("System not safe\n");
            return 1;
        }
    }
    printf("System is safe\n\n");

    printf("Enter process request number: ");
    scanf("%d", &pno);
    printf("Enter process request values: ");
    for (int i =0; i<RESOURCE_NUM; i++){
        scanf("%d", &request[i]);
    }
    requestProcess(pno, request);

    printf("Enter process request number: ");
    scanf("%d", &pno);
    printf("Enter process request values: ");
    for (int i =0; i<RESOURCE_NUM; i++){
        scanf("%d", &request[i]);
    }
    requestProcess(pno, request);

    printf("Enter process request number: ");
    scanf("%d", &pno);
    printf("Enter process request values: ");
    for (int i =0; i<RESOURCE_NUM; i++){
        scanf("%d", &request[i]);
    }
    requestProcess(pno, request);

    return 0;
}