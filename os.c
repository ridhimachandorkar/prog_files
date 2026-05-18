// Simple modular implementation with only the requested scheduling functions.

#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

void fcfs(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[j] < at[i] || (at[j] == at[i] && pid[j] < pid[i])) {
                int tmp;
                tmp = at[i]; at[i] = at[j]; at[j] = tmp;
                tmp = bt[i]; bt[i] = bt[j]; bt[j] = tmp;
                tmp = pid[i]; pid[i] = pid[j]; pid[j] = tmp;
            }
        }
    }

    int currentTime = 0;
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) {
            currentTime = at[i];
        }
        wt[i] = currentTime - at[i];
        currentTime += bt[i];
        tat[i] = wt[i] + bt[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

void npsjf(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], completed[MAX_PROCESSES] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    int currentTime = 0;
    int finished = 0;
    printf("\nPID\tAT\tBT\tWT\tTAT\n");

    while (finished < n) {
        int index = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && bt[i] < minBurst) {
                minBurst = bt[i];
                index = i;
            }
        }
        if (index == -1) {
            currentTime++;
            continue;
        }
        wt[index] = currentTime - at[index];
        currentTime += bt[index];
        tat[index] = wt[index] + bt[index];
        completed[index] = 1;
        finished++;
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[index], at[index], bt[index], wt[index], tat[index]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

void sjf(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], rt[MAX_PROCESSES], completed[MAX_PROCESSES] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int currentTime = 0;
    int finished = 0;

    while (finished < n) {
        int index = -1;
        int minRemaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && rt[i] < minRemaining && rt[i] > 0) {
                minRemaining = rt[i];
                index = i;
            }
        }
        if (index == -1) {
            currentTime++;
            continue;
        }
        rt[index]--;
        currentTime++;
        if (rt[index] == 0) {
            completed[index] = 1;
            finished++;
            tat[index] = currentTime - at[index];
            wt[index] = tat[index] - bt[index];
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

void rr(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], rt[MAX_PROCESSES];
    int queue[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    int tq;
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    if (tq <= 0) {
        printf("Time quantum must be positive.\n");
        return;
    }

    int currentTime = 0;
    int front = 0, rear = 0;
    int completed = 0;
    int inQueue[MAX_PROCESSES] = {0};

    for (int i = 0; i < n; i++) {
        if (at[i] < at[currentTime]) {
            currentTime = at[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (at[i] == currentTime) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && rt[i] > 0 && at[i] <= currentTime) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (front == MAX_PROCESSES) front = 0;

        int slice = rt[idx] < tq ? rt[idx] : tq;
        rt[idx] -= slice;
        currentTime += slice;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && rt[i] > 0 && at[i] <= currentTime) {
                queue[rear++] = i;
                if (rear == MAX_PROCESSES) rear = 0;
                inQueue[i] = 1;
            }
        }

        if (rt[idx] == 0) {
            completed++;
            tat[idx] = currentTime - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        } else {
            queue[rear++] = idx;
            if (rear == MAX_PROCESSES) rear = 0;
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

void npp(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES], pr[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], completed[MAX_PROCESSES] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("Process %d priority: ", pid[i]);
        scanf("%d", &pr[i]);
    }

    int currentTime = 0;
    int finished = 0;
    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");

    while (finished < n) {
        int index = -1;
        int bestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && pr[i] < bestPriority) {
                bestPriority = pr[i];
                index = i;
            }
        }
        if (index == -1) {
            currentTime++;
            continue;
        }
        wt[index] = currentTime - at[index];
        currentTime += bt[index];
        tat[index] = wt[index] + bt[index];
        completed[index] = 1;
        finished++;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[index], at[index], bt[index], pr[index], wt[index], tat[index]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

void p(void) {
    int n;
    int pid[MAX_PROCESSES], at[MAX_PROCESSES], bt[MAX_PROCESSES], pr[MAX_PROCESSES];
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], rt[MAX_PROCESSES], completed[MAX_PROCESSES] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d arrival time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d burst time: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("Process %d priority: ", pid[i]);
        scanf("%d", &pr[i]);
        rt[i] = bt[i];
    }

    int currentTime = 0;
    int finished = 0;
    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");

    while (finished < n) {
        int index = -1;
        int bestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && rt[i] > 0 && pr[i] < bestPriority) {
                bestPriority = pr[i];
                index = i;
            }
        }
        if (index == -1) {
            currentTime++;
            continue;
        }
        rt[index]--;
        currentTime++;
        if (rt[index] == 0) {
            completed[index] = 1;
            finished++;
            tat[index] = currentTime - at[index];
            wt[index] = tat[index] - bt[index];
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[index], at[index], bt[index], pr[index], wt[index], tat[index]);
        }
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

int main(void) {
    int choice;

    do {
        printf("\nSelect scheduling algorithm:\n");
        printf("  1. FCFS\n");
        printf("  2. SJF Preemptive\n");
        printf("  3. SJF Non-preemptive\n");
        printf("  4. RR\n");
        printf("  5. P\n");
        printf("  6. NPP\n");
        printf("  7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs();
                break;
            case 2:
                sjf();
                break;
            case 3:
                npsjf();
                break;
            case 4:
                rr();
                break;
            case 5:
                p();
                break;
            case 6:
                npp();
                break;
            case 7:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
