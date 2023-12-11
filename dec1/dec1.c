#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

int main(int argc, char** argv){
    char buf[256]; 
    int first = 0;
    int last = 0;
    int sum = 0;
    const char* word_list[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    FILE* fp = fopen("dec1_input.txt", "r");
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        int counter = 0;
        char c = 0;

        while ((c = buf[counter]) != '\0') {
            // first, check if the character is a number
            if (isdigit(c)) {
                if (first == 0) {
                    first = atoi(&c);
                }
                last = atoi(&c);
            }
            else if (c == '\n')
            {
                // then, check if it is a newline
                sum += 10 * first + last; // concatenate digits, add to sum
                // reset digits
                first = 0;
                last = 0;
            }
            else {
                // otherwise, check if there is a substring at the position where we are in the string
                for (int i = 0; i < 10; i++) {
                    if (strncmp(buf + counter, word_list[i], strlen(word_list[i])) == 0) { // we have at most 5 characters to compare
                        if (first == 0) {
                            first = i;
                        }
                        last = i;
                        break;
                    }
                }
            }
       
            counter++;
        }
        if (first != 0) {
            // contingency in case text files don't end with a trailing newline
            sum += 10 * first + last;
        }
    }

    fclose(fp);
    printf("%d\n", sum);

    return EXIT_SUCCESS;
}