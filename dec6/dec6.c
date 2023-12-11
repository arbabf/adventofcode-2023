#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
//#define PART_ONE

int main() {
    FILE *fp;
    
    char buf_time[LINE_LENGTH];
    char buf_dist[LINE_LENGTH];
    
    int sum = 1;
    
    fp = fopen("input.txt", "r");
    
    fgets(buf_time, LINE_LENGTH, fp);
    fgets(buf_dist, LINE_LENGTH, fp);
    
    fclose(fp);

#ifdef PART_ONE
    char *next_time;
    char *next_dist;
    char *saveptr_time;
    char *saveptr_dist;

    // skip the first words of both lines
    strtok_r(buf_time, " ", &saveptr_time);
    strtok_r(buf_dist, " ", &saveptr_dist);


    while ((next_time = strtok_r(NULL, " ", &saveptr_time)) != NULL) {
        next_dist = strtok_r(NULL, " ", &saveptr_dist);
        int max_time = atoi(next_time);
        int min_dist = atoi(next_dist);
        
        // keep ticking down cur_time till we get below min_dist
        int cur_time = max_time / 2;
        while ((cur_time) * (max_time - (cur_time)) > min_dist)
            cur_time--;
            
        cur_time++; // offset the final decrement
        
        // get the number of possible 2-number combinations, that, when multiplied, are larger than min_dist
        sum *= (max_time - cur_time - cur_time + 1);
    }
#else
    char *next_token;
    // combine times into one number
    char *time = (char *)malloc(sizeof(char));
    int time_length = 0;
    
    strtok(buf_time, " "); // skip first word
    while ((next_token = strtok(NULL, " ")) != NULL) {
        int len = strlen(next_token);
        time = (char *)realloc(time, (time_length + len) * sizeof(char));
        memcpy(time + time_length, next_token, len);
        time_length += len;
    }

    long long time_int = atoll(time);

    // combine dists into one number
    char *dist = (char *)malloc(sizeof(char));
    int dist_length = 0;
    strtok(buf_dist, " "); // skip first word
    while ((next_token = strtok(NULL, " ")) != NULL) {
        int len = strlen(next_token);
        dist = (char *)realloc(dist, (dist_length + len) * sizeof(char));
        memcpy(dist + dist_length, next_token, len);
        dist_length += len;
    }

    long long dist_int = atoll(dist);

    // keep ticking down cur_time till we get below dist
    int cur_time = time_int / 2;
    while ((cur_time) * (time_int - (cur_time)) > dist_int)
        cur_time--;
            
    cur_time++; // offset the final decrement
    sum = (time_int - cur_time - cur_time + 1);
#endif
    printf("%d\n", sum);
    
    return EXIT_SUCCESS;
}