#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256
#define ARR_LENGTH 256

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];
    char *next_token;
    long long *seeds = (long long *)malloc(sizeof(long long));
    int seeds_length = 1;
    int seeds_counter = 0;
    // 3d array of seed mappings
    // table 0 is soil
    // table 1 is fertiliser
    // table 2 is water
    // table 3 is light
    // table 4 is temperature
    // table 5 is humidity
    // table 6 is location
    // for each table, there is a 2d array of variable rows + 3 columns
    // column 1 = dest, column 2 = src, column 3 = len
    long long **mapping_table[7];
    int mapping_length[7];
    for (int i = 0; i < 7; i++) {
        mapping_table[i] = (long long **)malloc(3 * sizeof(long long *));
        mapping_length[i] = 1;
    }
    int mapping_counter[7] = {0};

    int table_counter = -1; // starts at 0 when we start parsing the mapping table
    long long min_location = LONG_LONG_MAX;
    
    fp = fopen("input.txt", "r");
    
    // get seeds
    fgets(buf, LINE_LENGTH, fp);
    strtok(buf, " ");
    while ((next_token = strtok(NULL, " ")) != NULL) {
        if (seeds_counter == seeds_length) {
            seeds_length *= 2;
            seeds = (long long *)realloc(seeds, seeds_length * sizeof(long long));
        }
        seeds[seeds_counter] = atoi(next_token);
        seeds_counter += 1;
    }

    // populate mapping table
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        if (isalpha(buf[0])) {
            // new seed mapping entry
            table_counter += 1;
        }
        else if (isdigit(buf[0])) {
            buf[strlen(buf)-1] = '\0';

            // get the mapping values
            long long dest = atoll(strtok(buf, " "));
            long long src = atoll(strtok(NULL, " "));
            long long len = atoll(strtok(NULL, " "));

            if (mapping_counter[table_counter] == mapping_length[table_counter]) {
                mapping_length[table_counter] *= 2;
                mapping_table[table_counter] = (long long **)realloc(mapping_table[table_counter], 
                                    mapping_length[table_counter] * 3 * sizeof(long long *));
            }

            long long *mapping_values;
            mapping_values = (long long *)malloc(3 * sizeof(long long));
            mapping_values[0] = dest;
            mapping_values[1] = src;
            mapping_values[2] = len;
            mapping_table[table_counter][mapping_counter[table_counter]] = mapping_values;
            mapping_counter[table_counter]++;
        }
    }
    
    fclose(fp);

    // find minimum location by traversing the mapping table
    for (int i = 0; i < seeds_counter; i++) {
        long long next_val = seeds[i];
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < mapping_counter[j]; k++) {
                if (next_val >= mapping_table[j][k][1] && 
                    next_val <= mapping_table[j][k][1] + mapping_table[j][k][2] - 1) {
                        next_val = mapping_table[j][k][0] + next_val - mapping_table[j][k][1];
                        break;
                    }
            }
        }
        if (next_val < min_location) {
            min_location = next_val;
        }
    }
    
    free(seeds);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < mapping_counter[i]; j++) {
            free(mapping_table[i][j]);
        }
        free(mapping_table[i]);
    }

    printf("%lld\n", min_location);

    return EXIT_SUCCESS;
}