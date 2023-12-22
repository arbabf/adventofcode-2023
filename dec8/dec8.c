#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 512
#define NODE_LENGTH 3

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];
    char instructions[LINE_LENGTH];
    int steps = 0;

    fp = fopen("input.txt", "rb");

    fgets(instructions, LINE_LENGTH, fp);
    instructions[strlen(instructions) - 1] = '\0'; // remove newline

    // make my life easier by fully allocating a 2d string array here and now
    fgets(buf, LINE_LENGTH, fp); // skip newline
    long old_loc = ftell(fp);

    fgets(buf, LINE_LENGTH, fp);
    long length = strlen(buf);

    fseek(fp, 0L, SEEK_END);
    long file_length = ftell(fp);

    fseek(fp, old_loc, SEEK_SET);
    
    int rows = (file_length - old_loc) / length;

    int nodes[rows][3][NODE_LENGTH]; // you're gonna see a lot of stupid char * conversion here, because i cbf'd refactoring this code to make it safe

    int row_counter = 0;

    // parse lines
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        char *node = strtok(buf, " ");
        strtok(NULL, " ");
        strncpy((char *)nodes[row_counter][0], node, NODE_LENGTH);

        // remove ( and ,
        char *left = strtok(NULL, " ") + 1;
        left[strlen(left) - 1] = '\0';
        strncpy((char *)nodes[row_counter][1], left, NODE_LENGTH);

        // remove ) and newline
        char *right = strtok(NULL, " ");
        right[strlen(right) - 2] = '\0';
        strncpy((char *)nodes[row_counter][2], right, NODE_LENGTH);
        
        row_counter++;
    }
    fclose(fp);

    int a_node = 0;
    for (int i = 0; i < row_counter; i++) {
        if (strncmp("AAA", (char *)nodes[i][0], 3) == 0) {
            a_node = i;
            break;
        }
    }
    int z_node = 0;
    for (int i = 0; i < row_counter; i++) {
        if (strncmp("ZZZ", (char *)nodes[i][0], 3) == 0) {
            z_node = i;
            break;
        }
    }

    // preprocess the node table for faster searching
    for (int i = 0; i < rows; i++) {
        for (int j = 1; j < 3; j++) {
            char *cur_str = (char *)nodes[i][j];
            for (int k = 0; k < rows; k++) {
                if (strncmp(cur_str, (char *)nodes[k][0], NODE_LENGTH) == 0) {
                    nodes[i][j][0] = k;
                    break;
                }
            }
        }
    }

    // traverse to the ZZZ node
    int cur_node = a_node;
    int instructions_counter = 0;
    while (cur_node != z_node) { // we assume here that the ZZZ node is the final row
        if (instructions[instructions_counter] == 'L')
            cur_node = nodes[cur_node][1][0];
        else
            cur_node = nodes[cur_node][2][0];

        instructions_counter++;
        if (instructions_counter >= strlen(instructions))
            instructions_counter = 0;

        steps++;
    }

    printf("%d\n", steps);

    return EXIT_SUCCESS;
}