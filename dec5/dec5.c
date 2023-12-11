#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 64
#define ARR_LENGTH 256

int main() {
    FILE *fp;
    fp = fopen("input.txt", "w");
    
    fprintf(fp, "seeds: 79 14 55 13\n"
    "\n"
    "seed-to-soil map:\n"
    "50 98 2\n"
    "52 50 48\n"
    "\n"
    "soil-to-fertilizer map:\n"
    "0 15 37\n"
    "37 52 2\n"
    "39 0 15\n"
    "\n"
    "fertilizer-to-water map:\n"
    "49 53 8\n"
    "0 11 42\n"
    "42 0 7\n"
    "57 7 4\n"
    "\n"
    "water-to-light map:\n"
    "88 18 7\n"
    "18 25 70\n"
    "\n"
    "light-to-temperature map:\n"
    "45 77 23\n"
    "81 45 19\n"
    "68 64 13\n"
    "\n"
    "temperature-to-humidity map:\n"
    "0 69 1\n"
    "1 0 69\n"
    "\n"
    "humidity-to-location map:\n"
    "60 56 37\n"
    "56 93 4\n");
    
    fclose(fp);
    
    char buf[LINE_LENGTH];
    char *next_token;
    int *seeds = (int *)malloc(sizeof(int));
    int seeds_length = 1;
    int seeds_counter = 0;
    // init 2d array of seed mappings
    // table 0 is seeds
    // table 1 is soil
    // table 2 is fertiliser
    // table 3 is water
    // table 4 is light
    // table 5 is temperature
    // table 6 is humidity
    // table 7 is location
    int seed_table[8][ARR_LENGTH];
    for (int i = 0; i < ARR_LENGTH; i++) {
        seed_table[0][i] = i;
    }
    // copy default values to all tables
    for (int i = 1; i < 8; i++) {
        memcpy(seed_table[i], seed_table[0], ARR_LENGTH * sizeof(int));
    }
    int table_counter = 0;
    int min_location = -1;
    
    fp = fopen("input.txt", "r");
    
    // get seeds
    fgets(buf, LINE_LENGTH, fp);
    strtok(buf, " ");
    while ((next_token = strtok(NULL, " ")) != NULL) {
        if (seeds_counter == seeds_length) {
            seeds_length *= 2;
            seeds = (int *)realloc(seeds, seeds_length * sizeof(int));
        }
        seeds[seeds_counter] = atoi(next_token);
        seeds_counter += 1;
    }

    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        if (isalpha(buf[0])) {
            table_counter += 1;
            // if (table_counter == 3) {
            //     for (int i = 0; i < ARR_LENGTH; i++) {
            //         printf("%d: %d\n", i, seed_table[1][i]);
            //     }
            //     break;
            // }
        }
        else if (isdigit(buf[0])) {
            buf[strlen(buf)-1] = '\0';
            // get the mapping values
            //next_token = strtok(buf, " ");
            int dest = atoi(strtok(buf, " "));
            int src = atoi(strtok(NULL, " "));
            int len = atoi(strtok(NULL, " "));
            //printf("%d\n", table_counter);
            printf("%d, %d, %d\n", dest, src, len);
            for (int i = 0; i < len; i++) {
                seed_table[table_counter][src + i] = seed_table[table_counter - 1][dest + i];
                if (table_counter == 2) {
                    //printf("%d %d\n", seed_table[table_counter][src + i], seed_table[table_counter - 1][dest + i]);
                    printf("%d %d\n", src + i, dest + i);
                    break;
                }
                
            }
            
        }
    }
    
    fclose(fp);
    printf("%d\n", seed_table[3][79]);
    printf("%d\n", min_location);
    return EXIT_SUCCESS;
}