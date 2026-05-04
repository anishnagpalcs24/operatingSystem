#include <stdio.h>
#include <stdlib.h>

int is_adjacent(int a, int b, int n) {
    if (abs(a - b) == 1) return 1;
    if ((a == 1 && b == n) || (a == n && b == 1)) return 1;
    return 0;
}

int main() {
    int n, h;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    printf("How many are hungry: ");
    scanf("%d", &h);

    int pos[20];

    for (int i = 0; i < h; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    int choice;

    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;


        if (choice == 1) {
            printf("\nAllow one philosopher to eat at any time\n");

            for (int i = 0; i < h; i++) {

                for (int j = 0; j < h; j++) {
                    printf("P%d is waiting\n", pos[j]);
                }

                printf("P%d is granted to eat\n", pos[i]);
                printf("P%d has finished eating\n\n", pos[i]);
            }
        }


        else if (choice == 2) {
            printf("\nAllow two philosophers to eat at a time\n");

            int eaten[20] = {0};

            for (int i = 0; i < h; i++) {

                if (eaten[i]) continue;

                int first = pos[i];
                int second_index = -1;

                for (int j = i + 1; j < h; j++) {
                    if (!is_adjacent(first, pos[j], n)) {
                        second_index = j;
                        break;
                    }
                }

                for (int j = 0; j < h; j++) {
                    printf("P%d is waiting\n", pos[j]);
                }

                printf("P%d is granted to eat\n", first);
                eaten[i] = 1;

                if (second_index != -1) {
                    printf("P%d is granted to eat\n", pos[second_index]);
                    eaten[second_index] = 1;
                }

                printf("Finished eating cycle\n\n");
            }
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
