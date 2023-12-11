#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

int main(int argc, char** argv){
    char buf[LINE_LENGTH], *next_token;
    //int id = 0;
    int num = 0;
    int max_red = 0;
    int max_blue = 0;
    int max_green = 0;
    int sum = 0;

    FILE* fp = fopen("input.txt", "r");
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        //printf("%s\n", buf);

        strtok(buf, " "); // skip first token
        next_token = strtok(NULL, ":"); // this token contains game id, remove the colon
        //id = atoi(next_token);

        while ((next_token = strtok(NULL, " ")) != NULL) {
            if (isdigit(next_token[0])) {
                // it's a number
                num = atoi(next_token);
            }
            else {
                // it's a word
                int len = strlen(next_token);
                if (!isalnum(next_token[len-1])) {
                    len -= 1;
                }
                switch (len)
                {
                // check if the number of cubes is ok, if not, then set the id to 0 (essentially wiping it from the id sum)
                // we can check colour by length of string since we only have 3 colours: red, green, blue
                case 3:
                    // red
                    if (num > max_red) {
                        max_red = num;
                    }
                    break;
                
                case 4:
                    // blue
                    if (num > max_blue) {
                        max_blue = num;
                    }
                    break;
                
                case 5:
                    // green
                    if (num > max_green) {
                        max_green = num;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        sum += (max_red * max_blue * max_green);
        max_red = 0;
        max_blue = 0;
        max_green = 0;
    }

    fclose(fp);
    printf("%d\n", sum);

    return EXIT_SUCCESS;
}