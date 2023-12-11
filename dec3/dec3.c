#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

struct schematic_number
{
    int start;
    int end;
};

int get_surrounding_numbers(char ***buf, int x, int y) {
    if (y > 0) {
        // top left
        if (x > 0) {

        }
        // top middle
    
        // top right
    }
    

    // middle left

    // middle right

    // bottom left

    // bottom middle

    // bottom right
    
    return 0;
}

int main(int argc, char** argv){
    char buf[LINE_LENGTH];// *next_token;
    int counter = 0;
    //int num = 0;
    int sum = 0;
    int file_length = 0;

    
    FILE* fp = fopen("test1.txt", "r");
    // allocate 2d array of our input
    fgets(buf, LINE_LENGTH, fp);
    int cols = strlen(buf);
    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    rewind(fp);
    int rows = file_length / cols--;
    char schematic_array[rows][cols];
    
    /*schematic_array[0][0] = 'a';
    schematic_array[0][1] = 'b';
    schematic_array[1][0] = 'c';*/
    //int (*array) [cols] = malloc( sizeof(int[rows][cols]) );
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {

        strncpy(schematic_array[counter], buf, cols);
        
        counter += 1;

        // while ((next_token = strtok(NULL, " ")) != NULL) {
            
        // }
        //sum += num;
    }

    int start = -1;
    int end = -1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            if (!isdigit(schematic_array[i][j]) && start != -1) {
                end = j-1;
                int length = end - start + 1;
                int found = 0;
                // search for special chars
                // first in the top
                if (i > 0) {
                    for (int k = start - 1; k <= end + 1; k++) {
                        if (k >= 0 && k < cols - 1 && !isdigit(schematic_array[i-1][k]) && schematic_array[i-1][k] != '.') {
                            // special char
                            found = 1;
                        }
                    }
                }
                // then to the left
                if (start > 0 && !isdigit(schematic_array[i][start-1]) && schematic_array[i][start-1] != '.') {
                    found = 1;
                }
                // then to the right
                if (end < cols - 1 && !isdigit(schematic_array[i][end+1]) && schematic_array[i][end+1] != '.') {
                    found = 1;
                }
                // then in the bottom
                if (i < rows - 1) {
                    printf("%s\n", schematic_array[i+1]);
                    for (int k = start - 1; k <= end + 1; k++) {
                        if (k >= 0 && k < cols - 1 && !isdigit(schematic_array[i+1][k]) && schematic_array[i+1][k] != '.') {
                            // special char
                            found = 1;
                        }
                    }
                }
                if (found) {
                    char number[length];
                    strncpy(number, schematic_array[i] + start, length);
                    sum += atoi(number);
                }
                start = -1;
            }
            else if (isdigit(schematic_array[i][j])) {
                if (start == -1) {
                    start = j;
                }
                end = j;
            }
        //printf("%d %d\n", start, end);
        // if (!isdigit(schematic_array[counter][i]) && schematic_array[counter][i] != '.') {
        //     // it's a special character
        //     sum += get_surrounding_numbers(&buf, counter, i);
        // }
        }
    }
    //free(schematic_array);
    fclose(fp);
    printf("%d\n", sum);

    return EXIT_SUCCESS;
}