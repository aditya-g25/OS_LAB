#include <stdio.h>

// Function for FIFO Page Replacement
void fifo(int pages[], int n, int f) {
    int frame[10], i, j, k = 0, faults = 0, found;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frame[k] = pages[i];
            k = (k + 1) % f;
            faults++;
        }

        printf("\nPage %d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

// Function for LRU Page Replacement
void lru(int pages[], int n, int f) {
    int frame[10], time[10];
    int i, j, pos, faults = 0, counter = 0;
    int flag1, flag2, minimum;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\n--- LRU Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0) {
            for(j = 0; j < f; j++) {
                if(frame[j] == -1) {
                    counter++;
                    faults++;
                    frame[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0) {
            minimum = time[0];
            pos = 0;

            for(j = 1; j < f; j++) {
                if(time[j] < minimum) {
                    minimum = time[j];
                    pos = j;
                }
            }

            counter++;
            faults++;
            frame[pos] = pages[i];
            time[pos] = counter;
        }

        printf("\nPage %d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

// Function for Optimal Page Replacement
void optimal(int pages[], int n, int f) {
    int frame[10];
    int i, j, k, faults = 0;
    int found, pos, farthest;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            pos = -1;
            farthest = i + 1;

            for(j = 0; j < f; j++) {
                int nextUse = -1;

                for(k = i + 1; k < n; k++) {
                    if(frame[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if(nextUse == -1) {
                    pos = j;
                    break;
                }

                if(nextUse > farthest) {
                    farthest = nextUse;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = pages[i];
            faults++;
        }

        printf("\nPage %d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

// Main Function
int main() {
    int pages[50], n, f, choice, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    do {
        printf("\n\n===== PAGE REPLACEMENT ALGORITHMS =====");
        printf("\n1. FIFO");
        printf("\n2. LRU");
        printf("\n3. Optimal");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                fifo(pages, n, f);
                break;

            case 2:
                lru(pages, n, f);
                break;

            case 3:
                optimal(pages, n, f);
                break;

            case 4:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 4);

    return 0;
}