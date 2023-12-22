#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

int part_one() {
    char buf[LINE_LENGTH];
    int counter = 0;
    int file_length = 0;
    int sum = 0;
    
    FILE* fp = fopen("input.txt", "r");
    // allocate 2d array of our input
    fgets(buf, LINE_LENGTH, fp);
    int cols = strlen(buf);
    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    rewind(fp);
    int rows = file_length / cols--;
    char schematic_array[rows][cols];
    
    // copy entire text file to schematic array
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        strncpy(schematic_array[counter], buf, cols);     
        counter += 1;
    }

    int start = -1;
    int end = -1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            if (isdigit(schematic_array[i][j])) {
                if (start == -1) {
                    start = j;
                }
                end = j;
            }
            if ((!isdigit(schematic_array[i][j]) || j == cols - 1) && start != -1) {
                if (j == cols - 1 && isdigit(schematic_array[i][j])) {
                    // digit at the end of a line, there will be no symbols after this so we need to account for it
                    end = j;
                }
                else {
                    // symbol, may or may not be at the end of a line
                    end = j-1;
                }
                
                int length = end - start + 1;
                int found = 0;

                // search for special chars
                // first in the top
                if (i > 0) {
                    for (int k = start - 1; k <= end + 1; k++) {
                        if (k >= 0 && k < cols && !isdigit(schematic_array[i-1][k]) && schematic_array[i-1][k] != '.') {
                            found = 1;
                            break;
                        }
                    }
                }
                // then to the left
                if (start > 0 && schematic_array[i][start-1] != '.') {
                    found = 1;
                }
                // then to the right
                if (end < cols - 1 && schematic_array[i][end+1] != '.') {
                    found = 1;
                }
                // then in the bottom
                if (i < rows - 1) {
                    for (int k = start - 1; k <= end + 1; k++) {
                        if (k >= 0 && k < cols && !isdigit(schematic_array[i+1][k]) && schematic_array[i+1][k] != '.') {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found) {
                    char number[length + 1];
                    strncpy(number, schematic_array[i] + start, length);
                    number[length] = '\0'; // null-terminate so we don't read extra digits by accident
                    sum += atoi(number);
                }
                start = -1;
            }
        }
    }

    fclose(fp);

    return sum;
}

int get_number(int nums_counter, int start, int end, char schem_row[]) {
    char *num = malloc(LINE_LENGTH * sizeof(char));
    strncpy(num, schem_row + start, end - start + 1);
    int number = atoi(num);
    free(num);
    return number;
}

int part_two() {
    char buf[LINE_LENGTH];
    int counter = 0;
    int file_length = 0;
    int sum = 0;
    
    FILE* fp = fopen("input.txt", "r");
    // allocate 2d array of our input
    fgets(buf, LINE_LENGTH, fp);
    int cols = strlen(buf);
    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    rewind(fp);
    int rows = file_length / cols--;
    char schematic_array[rows][cols];
    
    // copy entire text file to schematic array
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        strncpy(schematic_array[counter], buf, cols);     
        counter += 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (schematic_array[i][j] == '*') {
                // get surrounding numbers, first from the left + right since those are simpler
                int nums[2] = {-1, -1};
                int nums_counter = 0;
                int start = j;
                int end = j;
                // left
                while (start-1 >= 0 && isdigit(schematic_array[i][start-1])) {
                    if (start == j) {
                        end--;
                    }
                    start--;
                }
                if (start != j) {
                    if (nums_counter == 2)
                        break;
                    int num = get_number(nums_counter, start, end, schematic_array[i]);
                    nums[nums_counter++] = num;
                }
                // right
                start = end = j;
                while (end + 1 <= cols - 1 && isdigit(schematic_array[i][end+1])) {
                    if (start == j) {
                        start++;
                    }
                    end++;
                }
                if (start != j) {
                    if (nums_counter == 2)
                        break;
                    int num = get_number(nums_counter, start, end, schematic_array[i]);
                    nums[nums_counter++] = num;
                }
                // top
                start = end = -1;
                if (i > 0) {
                    // top-left
                    if (j > 0 && isdigit(schematic_array[i-1][j-1])) {
                        start = end = j-1;
                        while (start-1 >= 0 && isdigit(schematic_array[i-1][start-1])) {
                            start--;
                        }
                        while (end+1 <= cols-1 && isdigit(schematic_array[i-1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i-1]);
                        nums[nums_counter++] = num;
                    }
                    // top-middle
                    if (!(start <= j && j <= end) && isdigit(schematic_array[i-1][j])) {
                        // only parse top-middle if it's not part of a top-left number
                        start = end = j;
                        while (end+1 <= cols-1 && isdigit(schematic_array[i-1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i-1]);
                        nums[nums_counter++] = num;
                    }
                    // top-right
                    if (j < cols - 1 && !(start <= j+1 && j+1 <= end) && isdigit(schematic_array[i-1][j+1])) {
                        // similar thought process to top-middle for top-right
                        start = end = j+1;
                        while (end+1 <= cols-1 && isdigit(schematic_array[i-1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i-1]);
                        nums[nums_counter++] = num;
                    }
                }
                // bottom
                start = end = -1;
                if (i < rows - 1) {
                    // bottom-left
                    if (j > 0 && isdigit(schematic_array[i+1][j-1])) {
                        start = end = j-1;
                        while (start-1 >= 0 && isdigit(schematic_array[i+1][start-1])) {
                            start--;
                        }
                        while (end+1 <= cols - 1 && isdigit(schematic_array[i+1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i+1]);
                        nums[nums_counter++] = num;
                    }
                    // bottom-middle
                    if (!(start <= j && j <= end) && isdigit(schematic_array[i+1][j])) {
                        // see: top-middle
                        start = end = j;
                        while (end+1 <= cols - 1 && isdigit(schematic_array[i+1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i+1]);
                        nums[nums_counter++] = num;
                    }
                    // bottom-right
                    if (j < cols - 1 && !(start <= j+1 && j+1 <= end) && isdigit(schematic_array[i+1][j+1])) {
                        // see: top-right
                        start = end = j+1;
                        while (end+1 <= cols - 1 && isdigit(schematic_array[i+1][end+1])) {
                            end++;
                        }
                        if (nums_counter == 2)
                            break;
                        int num = get_number(nums_counter, start, end, schematic_array[i+1]);
                        nums[nums_counter++] = num;
                    }
                }
                if (nums_counter == 2) {
                    sum += nums[0] * nums[1];
                }
            }
        }
    }
    
    fclose(fp);

    return sum;
}

int main(int argc, char** argv){
    //int sum = part_one();
    int sum = part_two();
    printf("%d\n", sum);

    return EXIT_SUCCESS;
}