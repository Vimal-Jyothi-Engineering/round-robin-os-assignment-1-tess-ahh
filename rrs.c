#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int first_response;   // -1 if not yet started
} Process;

// Circular queue for ready queue
int queue[MAX_PROCESSES * 100];
int front = 0, rear = 0;

int is_empty() { return front == rear; }
void enqueue(int pid) { queue[rear++] = pid; }
int dequeue() { return queue[front++]; }

// Check if process is already in the ready queue
int in_queue(int pid) {
    for (int i = front; i < rear; i++)
        if (queue[i] == pid) return 1;
    return 0;
}

void print_gantt(int gantt_pid[], int gantt_time[], int gantt_len) {
    printf("\nGantt Chart:\n");

    // Top border
    printf(" ");
    for (int i = 0; i < gantt_len; i++) {
        printf("------");
    }
    printf("\n|");

    // Process names
    for (int i = 0; i < gantt_len; i++) {
        if (gantt_pid[i] == -1)
            printf(" IDLE |");
        else
            printf("  P%-2d |", gantt_pid[i]);
    }

    // Bottom border
    printf("\n ");
    for (int i = 0; i < gantt_len; i++) {
        printf("------");
    }

    // Time markers
    printf("\n");
    printf("%-2d", gantt_time[0]);
    for (int i = 0; i < gantt_len; i++) {
        printf("     %-2d", gantt_time[i + 1]);
    }
    printf("\n");
}

void round_robin(Process proc[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;

    // Gantt chart storage
    int gantt_pid[1000];
    int gantt_time[1001];
    int gantt_len = 0;

    // Initialise remaining times and first response
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].first_response = -1;
    }

    // Enqueue all processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time == 0)
            enqueue(i);
    }

    while (completed < n) {
        if (is_empty()) {
            // CPU is idle — advance to next arrival
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (proc[i].remaining_time > 0) {
                    if (next_arrival == -1 || proc[i].arrival_time < next_arrival)
                        next_arrival = proc[i].arrival_time;
                }
            }
            gantt_pid[gantt_len]    = -1;           // idle slot
            gantt_time[gantt_len]   = current_time;
            gantt_len++;
            current_time = next_arrival;
            gantt_time[gantt_len] = current_time;

            // Enqueue processes that have now arrived
            for (int i = 0; i < n; i++) {
                if (proc[i].arrival_time <= current_time &&
                    proc[i].remaining_time > 0 && !in_queue(i))
                    enqueue(i);
            }
            continue;
        }

        int idx = dequeue();

        // Record first response time
        if (proc[idx].first_response == -1)
            proc[idx].first_response = current_time;

        // Determine how long this process runs
        int run_time = (proc[idx].remaining_time < quantum)
                       ? proc[idx].remaining_time
                       : quantum;

        gantt_pid[gantt_len]  = proc[idx].pid;
        gantt_time[gantt_len] = current_time;
        gantt_len++;

        current_time          += run_time;
        proc[idx].remaining_time -= run_time;

        gantt_time[gantt_len] = current_time;

        // Enqueue newly arrived processes before re-adding current one
        for (int i = 0; i < n; i++) {
            if (i != idx &&
                proc[i].arrival_time <= current_time &&
                proc[i].remaining_time > 0 && !in_queue(i))
                enqueue(i);
        }

        if (proc[idx].remaining_time == 0) {
            // Process finished
            proc[idx].completion_time  = current_time;
            proc[idx].turnaround_time  = current_time - proc[idx].arrival_time;
            proc[idx].waiting_time     = proc[idx].turnaround_time - proc[idx].burst_time;
            completed++;
        } else {
            // Re-add to back of queue
            enqueue(idx);
        }
    }

    // ── Print Gantt chart ──────────────────────────────────────────────────
    print_gantt(gantt_pid, gantt_time, gantt_len);

    // ── Print results table ───────────────────────────────────────────────
    printf("\n%-6s %-10s %-10s %-12s %-12s %-12s\n",
           "PID", "Arrival", "Burst", "Completion", "Turnaround", "Waiting");
    printf("%-6s %-10s %-10s %-12s %-12s %-12s\n",
           "---", "-------", "-----", "----------", "----------", "-------");

    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%-6d %-10d %-10d %-12d %-12d %-12d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].turnaround_time,
               proc[i].waiting_time);
        total_tat += proc[i].turnaround_time;
        total_wt  += proc[i].waiting_time;
    }

    printf("\nAverage Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Waiting Time    : %.2f\n",   total_wt  / n);
}

int compare_arrival(const void *a, const void *b) {
    return ((Process *)a)->arrival_time - ((Process *)b)->arrival_time;
}

int main() {
    int n, quantum;
    Process proc[MAX_PROCESSES];

    printf("=== Round Robin CPU Scheduling ===\n\n");
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("  P%d — Arrival Time: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("  P%d — Burst Time  : ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    // Sort by arrival time so we enqueue in order
    // (use a simple insertion sort to keep pid labels intact)
    for (int i = 1; i < n; i++) {
        Process key = proc[i];
        int j = i - 1;
        while (j >= 0 && proc[j].arrival_time > key.arrival_time) {
            proc[j + 1] = proc[j];
            j--;
        }
        proc[j + 1] = key;
    }

    round_robin(proc, n, quantum);
    return 0;
}
