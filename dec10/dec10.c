#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

int start_coords[2] = {-1, -1};

void set_prev(int *prev, int i, int j) {
    prev[0] = i;
    prev[1] = j;
}

void calc_dists(int *dists, char *pipes, int i, int j, int rows, int cols, int cur_step, int prev[2]) {
    if (cur_step < dists[i*rows + j]) {
        dists[i*rows + j] = cur_step;
    }
    if (pipes[i*rows + j] == 'S' && cur_step == 0) {
        if (j > 0 && (pipes[i*rows + j-1] == 'L' || pipes[i*rows + j-1] == '-' || pipes[i*rows + j-1] == 'F'))
            calc_dists(dists, pipes, i, j-1, rows, cols, cur_step+1, prev);
        if (j < cols - 1 && (pipes[i*rows + j+1] == 'J' || pipes[i*rows + j+1] == '-' || pipes[i*rows + j+1] == '7'))
            calc_dists(dists, pipes, i, j+1, rows, cols, cur_step+1, prev);
        if (i > 0 && (pipes[(i-1)*rows + j] == '7' || pipes[(i-1)*rows + j] == '|' || pipes[(i-1)*rows + j] == 'F'))
            calc_dists(dists, pipes, i-1, j, rows, cols, cur_step+1, prev);
        if (i < rows - 1 && (pipes[(i+1)*rows + j] == 'L' || pipes[(i+1)*rows + j] == '|' || pipes[(i+1)*rows + j] == 'J'))
            calc_dists(dists, pipes, i+1, j, rows, cols, cur_step+1, prev);
    }
    switch (pipes[i*rows + j])
    {
        case 'F':
            if (i+1 == prev[0] && j == prev[1] && j < cols - 1) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j+1, rows, cols, cur_step+1, prev);
            }
            else if (i < rows - 1) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i+1, j, rows, cols, cur_step+1, prev);
            }
            break;
        case 'L':
            if (i-1 == prev[0] && j == prev[1] && j < cols - 1) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j+1, rows, cols, cur_step+1, prev);
            }
            else if (i > 0) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i-1, j, rows, cols, cur_step+1, prev);
            }
            break;
        case '7':
            if (i+1 == prev[0] && j == prev[1] && j > 0) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j-1, rows, cols, cur_step+1, prev);
            }
            else if (i < rows - 1) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i+1, j, rows, cols, cur_step+1, prev);
            }
            break;
        case 'J':
            if (i-1 == prev[0] && j == prev[1] && j > 0) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j-1, rows, cols, cur_step+1, prev);
            }
            else if (i > 0) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i-1, j, rows, cols, cur_step+1, prev);
            }
            break;
        case '-':
            if (i == prev[0] && j+1 == prev[1] && j > 0) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j-1, rows, cols, cur_step+1, prev);
            }
            else if (j < cols - 1) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i, j+1, rows, cols, cur_step+1, prev);
            }
            break;
        case '|':
            if (i+1 == prev[0] && i > 0 && j == prev[1]) {
                // go to the not previous coordinate
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i-1, j, rows, cols, cur_step+1, prev);
            }
            else if (i < rows - 1) {
                // we only have 2 dests so if one is not the previous then the other 100% is
                set_prev(prev, i, j);
                calc_dists(dists, pipes, i+1, j, rows, cols, cur_step+1, prev);
            }
            break;
        default:
            break;
    }
}

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];

    fp = fopen("input.txt", "r");

    fgets(buf, LINE_LENGTH, fp);
    int cols = strlen(buf);
    fseek(fp, 0L, SEEK_END);
    int file_length = ftell(fp);
    rewind(fp);
    int rows = file_length / cols;
    char pipe_system[rows][--cols];

    int counter = 0;

    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        strncpy(pipe_system[counter], buf, cols);
        if (start_coords[0] == -1) {
            for (int i = 0; i < cols; i++) {
                if (buf[i] == 'S') {
                    start_coords[0] = counter;
                    start_coords[1] = i;
                }
            }
        }       
        counter += 1;
    }
    
    fclose(fp);

    int dists[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dists[i][j] = INT_MAX;
        }
    }

    int prev[2] = {start_coords[0], start_coords[1]};

    // first, populate the distance table
    calc_dists(&dists[0][0], &pipe_system[0][0], start_coords[0], start_coords[1], rows, cols, 0, prev);
    // then, find the max distance
    int max_dist = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dists[i][j] != INT_MAX && dists[i][j] > max_dist) {
                max_dist = dists[i][j];
            }
        }
    }

    printf("%d\n", max_dist);

    return EXIT_SUCCESS;
}