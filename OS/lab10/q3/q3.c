#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure
struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
    int processed; // Flag to track if the request has been processed
};

// Function to sort the requests based on their arrival time
void sortRequests(struct DSA requests[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (requests[j].arrival_time_stamp > requests[j + 1].arrival_time_stamp) {
                // Swap the requests
                struct DSA temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to calculate the absolute difference between two cylinder numbers
int calculateSeekTimeDifference(int current_cylinder, int target_cylinder) {
    return abs(current_cylinder - target_cylinder);
}

// Function to find the request with the shortest seek time from the current cylinder
int findShortestSeekTimeRequest(struct DSA requests[], int n, int current_cylinder) {
    int shortest_seek_time = INT_MAX;
    int shortest_seek_time_index = -1;

    for (int i = 0; i < n; i++) {
        if (!requests[i].processed) {
            int seek_time = calculateSeekTimeDifference(current_cylinder, requests[i].cylinder);
            if (seek_time < shortest_seek_time) {
                shortest_seek_time = seek_time;
                shortest_seek_time_index = i;
            }
        }
    }

    return shortest_seek_time_index;
}

// Function to simulate FCFS disk scheduling
void FCFS(struct DSA requests[], int n, int initial_cylinder) {
    int total_movement = 0;
    int current_cylinder = initial_cylinder;

    printf("\nFCFS Disk Scheduling Algorithm\n");
    printf("==============================\n");

    printf("Order of processing requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request ID: %d, Process ID: %d, Cylinder: %d\n",
         requests[i].request_id, requests[i].process_id, requests[i].cylinder);

        // Calculate the movement for the current request
        total_movement += abs(requests[i].cylinder - current_cylinder);
        current_cylinder = requests[i].cylinder;
    }

    printf("Total head movement: %d cylinders\n", total_movement);
}

// Function to simulate SSTF disk scheduling
void SSTF(struct DSA requests[], int n, int initial_cylinder) {
    int total_movement = 0;
    int current_cylinder = initial_cylinder;

    printf("\nSSTF Disk Scheduling Algorithm\n");
    printf("==============================\n");

    printf("Order of processing requests:\n");
    for (int i = 0; i < n; i++) {
        int next_request_index = findShortestSeekTimeRequest(requests, n, current_cylinder);
        if (next_request_index != -1) {
            printf("Request ID: %d, Process ID: %d, Cylinder: %d\n",
             requests[next_request_index].request_id, requests[next_request_index].process_id, requests[next_request_index].cylinder);

            // Update the total movement
            total_movement += calculateSeekTimeDifference(current_cylinder, requests[next_request_index].cylinder);

            // Mark the request as processed
            requests[next_request_index].processed = 1;

            // Update the current cylinder
            current_cylinder = requests[next_request_index].cylinder;
        }
    }

    printf("Total head movement: %d cylinders\n", total_movement);
}

int main() {
    int n;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    struct DSA requests[n];

    // Input the requests
    for (int i = 0; i < n; i++) {
        requests[i].request_id = i + 1;
        printf("Enter arrival time for request %d: ", i + 1);
        scanf("%d", &requests[i].arrival_time_stamp);
        printf("Enter cylinder number for request %d: ", i + 1);
        scanf("%d", &requests[i].cylinder);
        printf("Enter process ID for request %d: ", i + 1);
        scanf("%d", &requests[i].process_id);
    }

    int initial_cylinder;
    printf("Enter the initial head position (current cylinder): ");
    scanf("%d", &initial_cylinder);

    sortRequests(requests, n);

    FCFS(requests, n, initial_cylinder);

    SSTF(requests, n, initial_cylinder);

    // Sort the requests based on arrival time

    // Simulate the selected disk scheduling algorithm

    return 0;
}
