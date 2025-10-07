#include "card.h"

// Default constructor.
Card::Card() {
    rank = '6';
    suit = 'S';
}

// Constructor with rank and suit
Card::Card(char r, char s) {
    rank = r;
    suit = s;
}

// Display the card (e.g., AC, 10S, KD)
void Card::display() {
    if (rank == '1') {
        cout << "10" << suit;  // In my program, 10 is represented as '1' (first char of "10")
    } else {
        cout << rank << suit;
    }
}

// Compare this card with another card
// Returns: 1 if this card wins, 0 for tie, -1 if this card loses
int Card::compare(Card c) {
    // Get value for this card
    int yourValue;
    switch(rank) {
        case 'A': yourValue = 1; break;   // Ace is low in this game
        case '2': yourValue = 2; break;
        case '3': yourValue = 3; break;
        case '4': yourValue = 4; break;
        case '5': yourValue = 5; break;
        case '6': yourValue = 6; break;
        case '7': yourValue = 7; break;
        case '8': yourValue = 8; break;
        case '9': yourValue = 9; break;
        case '1': yourValue = 10; break;  // 10 is represented as '1' (first char of "10")
        case 'J': yourValue = 11; break;
        case 'Q': yourValue = 12; break;
        case 'K': yourValue = 13; break;
        default: yourValue = 0; break;
    }
    
    // Get value for other card
    int otherValue;
    switch(c.rank) {
        case 'A': otherValue = 1; break;   // Ace is low in this game
        case '2': otherValue = 2; break;
        case '3': otherValue = 3; break;
        case '4': otherValue = 4; break;
        case '5': otherValue = 5; break;
        case '6': otherValue = 6; break;
        case '7': otherValue = 7; break;
        case '8': otherValue = 8; break;
        case '9': otherValue = 9; break;
        case '1': otherValue = 10; break;  // 10 is represented as '1' (first char of "10")
        case 'J': otherValue = 11; break;
        case 'Q': otherValue = 12; break;
        case 'K': otherValue = 13; break;
        default: otherValue = 0; break;
    }
    
    // First compare by rank
    if (yourValue > otherValue) return 1;
    else if (yourValue < otherValue) return -1;

    // Ranks are equal, compare by suit: C < S < D < H
    else {
        int yourSuitValue;
        switch(suit) {
            case 'C': yourSuitValue = 1; break;  // Clubs lowest
            case 'S': yourSuitValue = 2; break;  // Spades
            case 'D': yourSuitValue = 3; break;  // Diamonds  
            case 'H': yourSuitValue = 4; break;  // Hearts highest
            default: yourSuitValue = 0; break;
        }
        
        int otherSuitValue;
        switch(c.suit) {
            case 'C': otherSuitValue = 1; break;  // Clubs lowest
            case 'S': otherSuitValue = 2; break;  // Spades
            case 'D': otherSuitValue = 3; break;  // Diamonds
            case 'H': otherSuitValue = 4; break;  // Hearts highest
            default: otherSuitValue = 0; break;
        }
        
        if (yourSuitValue > otherSuitValue) return 1;
        else if (yourSuitValue < otherSuitValue) return -1;
        else return 0;
    }
}
