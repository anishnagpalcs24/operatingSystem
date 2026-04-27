#include <stdio.h>

#define MAX_TASKS 10
#define SIMULATION_TIME 20

typedef struct {
    int id;
    int execution_time;
    int remaining_time;
    int period;
    int deadline;
    int next_arrival;
    int weight;
} Task;

Task tasks[MAX_TASKS];
int n;

void reset_tasks(Task original[]) {
    for (int i = 0; i < n; i++) {
        tasks[i] = original[i];
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_arrival = 0;
    }
}

void print_gantt(int timeline[]) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < SIMULATION_TIME; i++) {
        if (timeline[i] == -1)
            printf(" Idle |");
        else
            printf(" T%d |", timeline[i]);
    }

    printf("\n0");
    for (int i = 1; i <= SIMULATION_TIME; i++)
        printf("    %d", i);
    printf("\n");
}

void rate_monotonic(Task original[]) {
    printf("\nRate Monotonic Scheduling\n");
    reset_tasks(original);

    int timeline[SIMULATION_TIME];

    for (int t = 0; t < SIMULATION_TIME; t++) {
        int selected = -1;
        int min_period = 1000000;

        for (int i = 0; i < n; i++) {
            if (t >= tasks[i].next_arrival && tasks[i].remaining_time > 0) {
                if (tasks[i].period < min_period) {
                    min_period = tasks[i].period;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            timeline[t] = tasks[selected].id;
            tasks[selected].remaining_time--;

            if (tasks[selected].remaining_time == 0) {
                tasks[selected].remaining_time = tasks[selected].execution_time;
                tasks[selected].next_arrival += tasks[selected].period;
            }
        } else {
            timeline[t] = -1;
        }
    }

    print_gantt(timeline);
}

void earliest_deadline_first(Task original[]) {
    printf("\nEarliest Deadline First Scheduling\n");
    reset_tasks(original);

    int timeline[SIMULATION_TIME];

    for (int t = 0; t < SIMULATION_TIME; t++) {
        int selected = -1;
        int earliest_deadline = 1000000;

        for (int i = 0; i < n; i++) {
            if (t >= tasks[i].next_arrival && tasks[i].remaining_time > 0) {
                int abs_deadline = tasks[i].next_arrival + tasks[i].deadline;
                if (abs_deadline < earliest_deadline) {
                    earliest_deadline = abs_deadline;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            timeline[t] = tasks[selected].id;
            tasks[selected].remaining_time--;

            if (tasks[selected].remaining_time == 0) {
                tasks[selected].remaining_time = tasks[selected].execution_time;
                tasks[selected].next_arrival += tasks[selected].period;
            }
        } else {
            timeline[t] = -1;
        }
    }

    print_gantt(timeline);
}

void proportional_scheduling(Task original[]) {
    printf("\nProportional Scheduling\n");
    reset_tasks(original);

    int timeline[SIMULATION_TIME];
    int executed[MAX_TASKS] = {0};

    int total_weight = 0;
    for (int i = 0; i < n; i++)
        total_weight += tasks[i].weight;

    for (int t = 0; t < SIMULATION_TIME; t++) {
        int selected = -1;
        double min_ratio = 1e9;

        for (int i = 0; i < n; i++) {
            double expected = ((double)tasks[i].weight / total_weight) * t;
            double ratio = executed[i] - expected;

            if (tasks[i].remaining_time > 0 && ratio < min_ratio) {
                min_ratio = ratio;
                selected = i;
            }
        }

        if (selected != -1) {
            timeline[t] = tasks[selected].id;
            tasks[selected].remaining_time--;
            executed[selected]++;

            if (tasks[selected].remaining_time == 0) {
                tasks[selected].remaining_time = tasks[selected].execution_time;
            }
        } else {
            timeline[t] = -1;
        }
    }

    print_gantt(timeline);
}

int main() {
    Task original[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        original[i].id = i + 1;

        printf("Execution Time: ");
        scanf("%d", &original[i].execution_time);

        printf("Period: ");
        scanf("%d", &original[i].period);

        printf("Deadline: ");
        scanf("%d", &original[i].deadline);

        printf("Weight: ");
        scanf("%d", &original[i].weight);
    }

    rate_monotonic(original);
    earliest_deadline_first(original);
    proportional_scheduling(original);

    return 0;
}
