#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 256

enum hand_type {
    high_card,
    one_pair,
    two_pair,
    three_kind,
    full_house,
    four_kind,
    five_kind,
};

struct hand { 
    enum hand_type type;
    char cards[5];
    int bid;
};

enum hand_type parse_hand(char buf[5]);
struct hand construct_hand(char buf[LINE_LENGTH]);
int compare_hands(const void *h1, const void *h2);
int get_value(char card);