#include <stdio.h>

#define MAX 100

int main() {
    int n, q;
    int pid[MAX], at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, time = 0;
    int done[MAX];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
        rt[i] = bt[i];
        done[i] = 0;
    }

    scanf("%d", &q);

    while (completed < n) {
        int progress = 0;

        for (int i = 0; i < n; i++) {
            if (done[i] == 0 && at[i] <= time && rt[i] > 0) {
                progress = 1;

                if (rt[i] > q) {
                    time += q;
                    rt[i] -= q;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    done[i] = 1;
                    completed++;
                }
            }
        }

        if (!progress) {
            time++;
        }
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt  += wt[i];
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", pid[i], wt[i]);
    }

    printf("\nTurnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", pid[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
