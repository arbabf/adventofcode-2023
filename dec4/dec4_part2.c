#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];
    char *next_token;
    int *winning_numbers = (int *)malloc(sizeof(int));
    int wn_length = 1;
    int wn_counter = 0;
    int *number_list = (int *)malloc(sizeof(int));
    int nl_length = 1;
    int nl_counter = 0;
    int *win_tally = (int *)malloc(sizeof(int));
    int wt_length = 1;
    int wt_counter = 0;
    int pipe_found = 0;
    int sum = 0;
    
    fp = fopen("input.txt", "r");
    
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        // skip first 2 tokens, these are useless
        strtok(buf, " ");
        strtok(NULL, " ");
        
        // reset arrays
        wn_length = nl_length = 1;
        wn_counter = nl_counter = 0;
        pipe_found = 0;
        
        if (wt_counter == wt_length) {
            wt_length *= 2;
            win_tally = (int *)realloc(win_tally, wt_length * sizeof(int));
        }
        win_tally[wt_counter] = 0;
        
        while ((next_token = strtok(NULL, " ")) != NULL) {
            if (next_token[0] == '|')
                pipe_found = 1;
            else if (!pipe_found) {
                // resize array if needed, add number to array
                if (wn_counter == wn_length) {
                    wn_length *= 2;
                    winning_numbers = (int *)realloc(winning_numbers, wn_length * sizeof(int));
                }
                winning_numbers[wn_counter] = atoi(next_token);
                wn_counter += 1;
            }
            else {
                // resize array if needed, add number to array
                if (nl_counter == nl_length) {
                    nl_length *= 2;
                    number_list = (int *)realloc(number_list, nl_length * sizeof(int));
                }
                number_list[nl_counter] = atoi(next_token);
                nl_counter += 1;
            }
        }
        
        // tally up winning numbers on the cards
        for (int i = 0; i < nl_counter; i++) {
            for (int j = 0; j < wn_counter; j++) {
                if (number_list[i] == winning_numbers[j]) {
                    win_tally[wt_counter] += 1;
                }
            }
        }
        
        wt_counter += 1;
    }
    fclose(fp);
    
    // initialise array
    int *card_count = (int *)malloc(wt_counter * sizeof(int));
    for (int i = 0; i < wt_counter; i++) {
        card_count[i] = 1;
    }
    
    // tally up extra scratchcards
    for (int i = 0; i < wt_counter; i++) {
        sum += card_count[i];
        for (int j = i + 1; j <= i + win_tally[i]; j++) {
            if (i < wt_counter) {
                card_count[j] += card_count[i];
            }
        }
    }
    
    free(winning_numbers);
    free(number_list);
    free(win_tally);
    free(card_count);
    
    printf("%d\n", sum);
    
    return EXIT_SUCCESS;
}