#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];
    char *next_token;
    int sum = 0;

    fp = fopen("input.txt", "r");

    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        int **full_history = (int **)malloc(sizeof(int *));
        int history_counter = 1; // the history always starts off with an entry
        // get line in our history
        full_history[0] = (int *)malloc(2 * sizeof(int));
        int top_length = 2;
        int top_counter = 1;
        full_history[0][0] = atoi(strtok(buf, " "));
        while ((next_token = strtok(NULL, " ")) != NULL) {
            if (top_counter == top_length) {
                top_length *= 2;
                full_history[0] = (int *)realloc(full_history[0], top_length * sizeof(int));
            }
            full_history[0][top_counter] = atoi(next_token);
            top_counter++;
        }

        // get differences in our history
        int all_zeroes = 0;
        int cur_counter = top_counter - 1;
        while (!all_zeroes) {
            all_zeroes = 1;
            full_history = (int **)realloc(full_history, (history_counter + 1) * sizeof (int *));
            full_history[history_counter] = (int *)malloc(cur_counter * sizeof(int));

            for (int i = 0; i < cur_counter; i++) {
                int diff = full_history[history_counter - 1][i + 1] -
                            full_history[history_counter - 1][i];
                if (diff != 0) {
                    all_zeroes = 0;
                }
                full_history[history_counter][i] = diff; 
            }
            cur_counter--;
            history_counter++;
        }

        // extrapolate
        int next_val = 0;
        int last_index = top_counter - history_counter;
        for (int i = history_counter - 2; i >= 0; i--) {
            // start from 2nd-to-last index
            next_val += full_history[i][++last_index];
        }

        for (int i = 0; i < history_counter; i++) {
            free(full_history[i]);
        }
        free(full_history);

        sum += next_val;
    }
    
    fclose(fp);

    printf("%d\n", sum);

    return EXIT_SUCCESS;
}