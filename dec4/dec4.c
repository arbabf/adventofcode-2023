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
    int pipe_found = 0;
    int sum = 0;
    
    fp = fopen("input.txt", "r");
    
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        // skip first 2 tokens, these are useless
        strtok(buf, " ");
        strtok(NULL, " ");
        
        // reset array
        wn_length = nl_length = 1;
        wn_counter = nl_counter = 0;
        pipe_found = 0;
        
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
        
        // tally up points
        int points = 0;
        for (int i = 0; i < nl_counter; i++) {
            for (int j = 0; j < wn_counter; j++) {
                if (number_list[i] == winning_numbers[j]) {
                    if (points == 0) 
                        points = 1;
                    else
                        points *= 2;
                    break;
                }
            }
        }
        sum += points;
    }
    
    free(winning_numbers);
    free(number_list);
    fclose(fp);
    
    printf("%d\n", sum);
    
    return EXIT_SUCCESS;
}