#include "dec7.h"

int main() {
    FILE *fp;
    
    char buf[LINE_LENGTH];
    struct hand *hands = (struct hand *)malloc(sizeof(struct hand));
    int hands_length = 1;
    int hands_counter = 0;
    int sum = 0;
    
    fp = fopen("input.txt", "r");
    
    while (fgets(buf, LINE_LENGTH, fp) != NULL) {
        struct hand h = construct_hand(buf);
        if (hands_counter == hands_length) {
            hands_length *= 2;
            hands = (struct hand *)realloc(hands, hands_length * sizeof(struct hand));
        }
        hands[hands_counter] = h;
        hands_counter += 1;
    }
    
    fclose(fp);
    
    qsort(hands, hands_counter, sizeof(struct hand), compare_hands);

    // total up the bids
    for (int i = 0; i < hands_counter; i++) {
        sum += hands[i].bid * (i + 1);
    }

    printf("%d\n", sum);
    
    return EXIT_SUCCESS;
}

enum hand_type parse_hand(char buf[5]) {
    int highest_count = 0;
    int second_highest_count = 0;
    int card_tally[13] = {0};

    // tally up repeated cards
    for (int i = 0; i < 5; i++) {
        // 2 maps to array index 0, up to ace which maps to array index 12
        int index = get_value(buf[i]) - 2;

        card_tally[index] += 1;

        if (card_tally[index] > highest_count) {
            highest_count = card_tally[index];
        }
        else if (card_tally[index] > second_highest_count) {
            second_highest_count = card_tally[index];
        }
    }

    // determine type of hand
    switch (highest_count)
    {
    case 5:
        return five_kind;
        break;
    
    case 4:
        return four_kind;
        break;

    case 3:
        if (second_highest_count == 2)
            return full_house;
        return three_kind;
        break;

    case 2:
        if (second_highest_count == 2)
            return two_pair;
        return one_pair;
        break;

    case 1:
        return high_card;
        break;
    
    default:
        return high_card;
        break;
    }
}

struct hand construct_hand(char buf[LINE_LENGTH]) {
    enum hand_type htype = parse_hand(strtok(buf, " "));
    int bid = atoi(strtok(NULL, " "));

    struct hand h = { htype, "", bid };
    strncpy(h.cards, buf, 5);

    return h;
}

int compare_hands(const void *h1, const void *h2) {
    struct hand hand1 = *(struct hand *)h1;
    struct hand hand2 = *(struct hand *)h2;

    if (hand1.type > hand2.type) {
        return 1;
    }
    else if (hand1.type < hand2.type) {
        return -1;
    }
    else {
        // compare chars
        for (int i = 0; i < 5; i++) {
            int val1 = get_value(hand1.cards[i]);
            int val2 = get_value(hand2.cards[i]);
            if (val1 > val2) {
                return 1;
            }
            else if (val1 < val2) {
                return -1;
            }
        }
    }
    return 0; // both cards are completely equal
}

int get_value(char card) {
    switch (card)
        {
        case 'A':
            return 14;
            break;
        
        case 'K':
            return 13;
            break;

        case 'Q':
            return 12;
            break;

        case 'J':
            return 11;
            break;

        case 'T':
            return 10;
            break;
        
        default:
            return card - '0'; // char to int conversion
            break;
        }
}