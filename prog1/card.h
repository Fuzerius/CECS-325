#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
    private:
        char suit;
        char rank;
    
    public:
        Card();  // default constructor
        Card(char r, char s);  // constructor with rank and suit
        void display();  // display the card
        int compare(Card c);  // compare cards: 1=win, 0=tie, -1=lose
};

#endif
