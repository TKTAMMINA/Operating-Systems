#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int isPageInFrames(int frames[], int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void fifo(int pages[], int num_pages, int num_frames) {
    int frames[MAX_FRAMES], faults = 0, index = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("FIFO Page Replacement:\n");
    for (int i = 0; i < num_pages; i++) {
        if (!isPageInFrames(frames, num_frames, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % num_frames;
            faults++;
            printFrames(frames, num_frames);
        }
    }
    printf("Total Page Faults: %d\n\n", faults);
}

void lru(int pages[], int num_pages, int num_frames) {
    int frames[MAX_FRAMES], faults = 0, time[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("LRU Page Replacement:\n");
    for (int i = 0; i < num_pages; i++) {
        int found = 0, lru = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if (!found) {
            for (int j = 1; j < num_frames; j++) {
                if (time[j] < time[lru])
                    lru = j;
            }
            frames[lru] = pages[i];
            time[lru] = i;
            faults++;
            printFrames(frames, num_frames);
        }
    }
    printf("Total Page Faults: %d\n\n", faults);
}

void optimal(int pages[], int num_pages, int num_frames) {
    int frames[MAX_FRAMES], faults = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("Optimal Page Replacement:\n");
    for (int i = 0; i < num_pages; i++) {
        if (!isPageInFrames(frames, num_frames, pages[i])) {
            int replace = 0, farthest = i + 1;
            for (int j = 0; j < num_frames; j++) {
                int k;
                for (k = i + 1; k < num_pages; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace = j;
                        }
                        break;
                    }
                }
                if (k == num_pages) {
                    replace = j;
                    break;
                }
            }
            frames[replace] = pages[i];
            faults++;
            printFrames(frames, num_frames);
        }
    }
    printf("Total Page Faults: %d\n\n", faults);
}

int main() {
    int num_pages, num_frames, pages[MAX_PAGES];

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);
    printf("Enter the pages: ");
    for (int i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    fifo(pages, num_pages, num_frames);
    lru(pages, num_pages, num_frames);
    optimal(pages, num_pages, num_frames);

    return 0;
}
