#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

int main() {
    char buf[LINE_LENGTH];
    
    FILE *fp;
    fp = fopen("test11.txt", "r");
    fgets(buf, LINE_LENGTH, fp);
    int cols = strlen(buf);
    fseek(fp, 0L, SEEK_END);
    int file_length = ftell(fp);
    rewind(fp);
    int rows = file_length / cols;
    char space[rows][--cols];
    // cbf'd dealing with a 2d array so here's a 1d array
    // row coordinate is stored within the upper 16 bits of each element,
    // column coordinate within the lower 16 bits
    int *galaxy_locations = (int *)malloc(sizeof(int));
    //int galaxy_length = 1;
    //int galaxy_counter = 0;
    int sum = 0;
    int counter = 0;

    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        strncpy(space[counter], buf, cols);
        // for (int i = 0; i < cols; i++) {
        //     if (buf[i] == '#') {
        //         if (galaxy_counter == galaxy_length) {
        //             galaxy_length *= 2;
        //             galaxy_locations = realloc(galaxy_locations, galaxy_length * sizeof(int));
        //         }
        //         int num = 0;
        //         num |= (counter << 16); // store row coordinate within upper 16 bits of num
        //         num |= i; // store i (assumed to be <= 65535) within lower 16 bits
        //         galaxy_counter++;
        //     }
        // }
        counter++;
    }
    
    int *no_row_galaxies = (int *)malloc(sizeof(int));
    int nrg_length = 1;
    int nrg_counter = 0;
    int *no_column_galaxies = (int *)malloc(sizeof(int));
    int ncg_length = 1;
    int ncg_counter = 0;

    // find out rows where no galaxies exist
    for (int i = 0; i < rows; i++) {
        int no_galaxies = 1;
        for (int j = 0; j < cols; j++) {
            if (space[i][j] == '#') {
                no_galaxies = 0;
            }
        }
        if (no_galaxies) {
            if (nrg_counter == nrg_length) {
                nrg_length *= 2;
                no_row_galaxies = (int *)realloc(no_row_galaxies, nrg_length * sizeof(int));
            }
            no_row_galaxies[nrg_counter] = i;
            nrg_counter++;
        }
    }

    // find out columns where no galaxies exist
    for (int j = 0; j < cols; j++) {
        int no_galaxies = 1;
        for (int i = 0; i < rows; i++) {
            if (space[i][j] == '#') {
                no_galaxies = 0;
            }
        }
        if (no_galaxies) {
            if (ncg_counter == ncg_length) {
                ncg_length *= 2;
                no_column_galaxies = (int *)realloc(no_column_galaxies, ncg_length * sizeof(int));
            }
            no_column_galaxies[ncg_counter] = j;
            ncg_counter++;
        }
    }

    char expanded_space[rows + nrg_counter][cols + ncg_counter];
    int offset = 0;
    // expand space in the rows direction
    for (int i = 0; i < rows; i++) {
        if (i == no_row_galaxies[offset]) {
            memset(expanded_space[i + offset], '.', cols);
            offset++;
        }
        strncpy(expanded_space[i + offset], space[i], cols);
    }

    offset = 0;
    // expand space in the cols direction
    for (int j = 0; j < cols; j++) {
        if (j == no_column_galaxies[offset]) {
            // set entire column to dot
            for (int k = 0; k < rows + nrg_counter; k++) {
                expanded_space[k][j + offset] = '.';
            }
            offset++;
        }
        // copy string vertically
        // find out why expanded_space[0][12] is '\0'
        int row_offset = 0;
        for (int k = 0; k < rows + nrg_counter; k++) {
            // padding
            if (k == no_row_galaxies[row_offset]) {
                expanded_space[k + row_offset][j + offset] = '.';
                row_offset++;
            }
            expanded_space[k + row_offset][j + offset] = space[k][j];
        }
    }
    free(galaxy_locations);
    free(no_row_galaxies);
    free(no_column_galaxies);
    fclose(fp);

    printf("%d\n", sum);

    return EXIT_SUCCESS;
}